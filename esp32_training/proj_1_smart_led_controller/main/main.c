#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_https_server.h"
#include "sdkconfig.h"
#include "max7219.h"
#include "rtc.h"
#include "driver/gpio.h"
#include <esp_timer.h>
#include <time.h>
#include "esp_intr_types.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_adc/adc_continuous.h"
#include "freertos/semphr.h"

#define ALARM_PIN 14
#define DOWN_PIN 25
#define UP_PIN 26
#define SET_PIN 27

#define ESP_INTR_FLAG_DEFAULT 1
#define DEFAULT_VREF 1100               // Default ADC reference voltage in mV
#define ADC_WIDTH_BIT ADC_WIDTH_BIT_12  // ADC bit width (9, 10, 11, or 12)
#define ADC_ATTENUATION ADC_ATTEN_DB_12 // ADC attenuation (0db, 2.5db, 6db, 11db)
#define PORT_TICK_PERIOD_MS 1000        // Tick period in milliseconds
#define ADC_GPIO ADC1_CHANNEL_5         // ADC channel for GPIO33
#define DEBOUNCE_TIME_MS 300

static esp_adc_cal_characteristics_t *adc_chars; // struct
static const char *TAG = "main";

SemaphoreHandle_t semaphore1, semaphore2, semaphore3;
volatile uint32_t last_interrupt_time_1 = 0;
volatile uint32_t last_interrupt_time_2 = 0;
volatile uint32_t last_interrupt_time_3 = 0;

#ifndef IRAM_ATTR
#define IRAM_ATTR __attribute__((section(".iram1")))
#endif
#define MAX_STA_CONN 4

volatile int alarm_hour = -1;
volatile int alarm_minute = -1;
volatile int current_hour;
volatile int current_minute;
volatile bool i = true;
volatile int set = 0;
volatile int hours, minutes, seconds, day, date, month, year;
volatile int *day_print;

volatile int day_set[4];

struct async_resp_arg
{
    httpd_handle_t hd;
    int fd;
};

static esp_err_t ws_handler(httpd_req_t *req)
{
    if (req->method == HTTP_GET)
    {
        ESP_LOGI(TAG, "Handshake done, the new connection was opened");
        return ESP_OK;
    }

    httpd_ws_frame_t ws_pkt;
    uint8_t *buf = NULL;
    memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
    esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
        return ret;
    }

    if (ws_pkt.len)
    {
        buf = calloc(1, ws_pkt.len + 1);
        if (buf == NULL)
        {
            ESP_LOGE(TAG, "Failed to calloc memory for buf");
            return ESP_ERR_NO_MEM;
        }
        ws_pkt.payload = buf;
        ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);

        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
            free(buf);
            return ret;
        }
    }

    if (ws_pkt.type == HTTPD_WS_TYPE_TEXT)
    {
        ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload);

        if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %1d %2d/%2d/%4d", &hours, &minutes, &seconds, &day, &date, &month, &year) == 7)
        {
            current_hour = hours;
            current_minute = minutes;
            set_rtc_time(seconds, minutes, hours, day, date, month, year);
            ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d day:%d", hours, minutes, seconds, date, month, year, day);
            const char *ack = "Time set successfully";
            ws_pkt.payload = (uint8_t *)ack;
            ws_pkt.len = strlen(ack);
            ret = httpd_ws_send_frame(req, &ws_pkt);

            if (ret != ESP_OK)
            {
                ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
            }
        }

        if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d", &hours, &minutes) == 2)
        {
            alarm_hour = hours;
            alarm_minute = minutes;
            ESP_LOGI(TAG, "Alarm time set to %02d:%02d", alarm_hour, alarm_minute);
            const char *ack = "Alarm set successfully";
            ws_pkt.payload = (uint8_t *)ack;
            ws_pkt.len = strlen(ack);
            ret = httpd_ws_send_frame(req, &ws_pkt);

            if (ret != ESP_OK)
            {
                ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
            }
        }
        free(buf);
        return ESP_OK;
    }
    return ESP_FAIL;
}

static esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd)
{
    ESP_LOGI(TAG, "New client connected %d", sockfd);
    return ESP_OK;
}

static void wss_close_fd(httpd_handle_t hd, int sockfd)
{
    ESP_LOGI(TAG, "Client disconnected %d", sockfd);
}

static httpd_handle_t start_wss_echo_server(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.open_fn = wss_open_fd;
    config.close_fn = wss_close_fd;
    esp_err_t ret = httpd_start(&server, &config);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
        return NULL;
    }
    httpd_uri_t ws = {
        .uri = "/ws",
        .method = HTTP_GET,
        .handler = ws_handler,
        .is_websocket = true,
        .supported_subprotocol = NULL,
    };
    ret = httpd_register_uri_handler(server, &ws);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
        httpd_stop(server);
        return NULL;
    }
    return server;
}

static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server)
    {
        httpd_stop(*server);
        *server = NULL;
    }
}

static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server == NULL)
    {
        *server = start_wss_echo_server();
    }
}

static void button_init(int PIN_NUM)
{

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL << PIN_NUM);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to configure GPIO: %s", esp_err_to_name(ret));
        return;
    }
}


void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    uint32_t current_time = xTaskGetTickCountFromISR();
    if (gpio_num == DOWN_PIN && (current_time - last_interrupt_time_1) > pdMS_TO_TICKS(DEBOUNCE_TIME_MS))
    {
        last_interrupt_time_1 = current_time;
        xSemaphoreGiveFromISR(semaphore1, NULL);
    }
}

void IRAM_ATTR gpio_isr_handler1(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    uint32_t current_time = xTaskGetTickCountFromISR();
    if (gpio_num == UP_PIN && (current_time - last_interrupt_time_2) > pdMS_TO_TICKS(DEBOUNCE_TIME_MS))
    {
        last_interrupt_time_2 = current_time;
        xSemaphoreGiveFromISR(semaphore2, NULL);
    }
}

void IRAM_ATTR gpio_isr_handler2(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    uint32_t current_time = xTaskGetTickCountFromISR();
    if (gpio_num == SET_PIN && (current_time - last_interrupt_time_3) > pdMS_TO_TICKS(DEBOUNCE_TIME_MS))
    {
        last_interrupt_time_3 = current_time;
        xSemaphoreGiveFromISR(semaphore3, NULL);
    }
}

void task1(void *pvParameter)
{
    while (1)
    {
        if (xSemaphoreTake(semaphore1, portMAX_DELAY))
        {
            switch (set)
            {
            case 0:
                current_hour--;
                if (current_hour < 0)
                {
                    current_hour = 23;
                }
                ESP_LOGI("Task1", "Interrupt received...1 and hour down");
                time_flag_hour = true;
                time_flag_minute = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
                break;
            case 1:
                current_minute--;
                if (current_minute < 0)
                {
                    current_minute = 59;
                }
                ESP_LOGI("Task1", "Interrupt received...1 and minute down");
                time_flag_minute = true;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
                break;
            case 2:
                date--;
                if (date < 0)
                {
                    date = 31;
                }
                ESP_LOGI("Task1", "Interrupt received...1 and date down");
                time_flag_date = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
                break;

            case 3:
                month--;
                if (month < 0)
                {
                    month = 12;
                }
                ESP_LOGI("Task1", "Interrupt received...1 and month down");
                time_flag_month = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_year = false;
                time_flag_day = false;
                break;
            case 4:
                year--;
                if (year < 0)
                {
                    year = 99;
                }
                ESP_LOGI("Task1", "Interrupt received...1 and year down");
                time_flag_year = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_day = false;
                break;
            case 5:
                day--;
                if (day < 0)
                {
                    day = 7;
                }
                ESP_LOGI("Task1", "Interrupt received...1 and day down");
                time_flag_day = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                break;
            default:
                ESP_LOGE("Task1", "Interrupt received...1 error");
                break;
            }
            set_rtc_time(seconds, current_minute, current_hour, day, date, month, year);
            update_time_flag = true;
            update_time_flag_1 = true;
        }
    }
}

void task2(void *pvParameter)
{
    while (1)
    {
        if (xSemaphoreTake(semaphore2, portMAX_DELAY))
        {
            switch (set)
            {
            case 0:
                current_hour++;
                if (current_hour > 23)
                {
                    current_hour = 0;
                }
                ESP_LOGI("Task2", "Interrupt received...2 and hour UP");
                time_flag_hour = true;
                time_flag_minute = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
                break;
            case 1:
                current_minute++;
                if (current_minute > 59)
                {
                    current_minute = 0;
                }
                ESP_LOGI("Task2", "Interrupt received...2 and minute UP");
                time_flag_hour = false;
                time_flag_minute = true;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
                break;
            case 2:
                date++;
                if (date > 31)
                {
                    date = 0;
                }
                ESP_LOGI("Task2", "Interrupt received...2 and date UP");
                time_flag_date = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
                break;

            case 3:
                month++;
                if (month > 12)
                {
                    month = 0;
                }
                ESP_LOGI("Task2", "Interrupt received...2 and month UP");
                time_flag_month = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_year = false;
                time_flag_day = false;
                break;
            case 4:
                year++;
                // if (year > 99)
                // {
                //     year = 0;
                // }
                ESP_LOGI("Task2", "Interrupt received...2 and year UP");
                time_flag_year = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_day = false;
                break;
            case 5:
                day++;
                if (day > 6)
                {
                    day = 0;
                }
                ESP_LOGI("Task1", "Interrupt received...2 and day UP");
                time_flag_day = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                break;
            default:
                ESP_LOGE("Task2", "Interrupt received...2 error");
                break;
            }
            set_rtc_time(seconds, current_minute, current_hour, day, date, month, year);
            update_time_flag = true;
            update_time_flag_1 = true;
        }
    }
}
void task3(void *pvParameter)
{
    while (1)
    {
        if (xSemaphoreTake(semaphore3, portMAX_DELAY))
        {
            set++;
            if (set > 5)
            {
                set = 0;
            }
            if (set == 0)
            {
                ESP_LOGI("Task3", "Interrupt received...3 and hour set");
                time_flag_hour = true;
                time_flag_minute = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
            }
            else if (set == 1)
            {
                ESP_LOGI("Task3", "Interrupt received...3 and minute set");
                time_flag_minute = true;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
            }
            else if (set == 2)
            {
                ESP_LOGI("Task3", "Interrupt received...3 and date set");
                time_flag_date = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_month = false;
                time_flag_year = false;
                time_flag_day = false;
            }
            else if (set == 3)
            {
                ESP_LOGI("Task3", "Interrupt received...3 and month set");
                time_flag_month = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_year = false;
                time_flag_day = false;
            }
            else if (set == 4)
            {
                ESP_LOGI("Task3", "Interrupt received...3 and year set");
                time_flag_year = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_day = false;
            }
            else if (set == 5)
            {
                ESP_LOGI("Task3", "Interrupt received...3 and day set");
                time_flag_day = true;
                time_flag_minute = false;
                time_flag_hour = false;
                time_flag_date = false;
                time_flag_month = false;
                time_flag_year = false;
            }
            update_time_flag = true;
            update_time_flag_1 = true;
        }
    }
}

void initialize_isr_service()
{
    esp_err_t ret = gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to install ISR service: %s", esp_err_to_name(ret));
        return;
    }

    ret = gpio_isr_handler_add(DOWN_PIN, gpio_isr_handler, (void *)DOWN_PIN);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to add ISR handler for DOWN_PIN: %s", esp_err_to_name(ret));
    }

    ret = gpio_isr_handler_add(UP_PIN, gpio_isr_handler1, (void *)UP_PIN);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to add ISR handler for UP_PIN: %s", esp_err_to_name(ret));
    }

    ret = gpio_isr_handler_add(SET_PIN, gpio_isr_handler2, (void *)SET_PIN);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to add ISR handler for SET_PIN: %s", esp_err_to_name(ret));
    }
}

void day_time(int time_scroll[40], int day)
{
    int new_values[10]; // Declare array with maximum size needed
    int size =0;           // Variable to store the number of elements in new_values for each case

    switch (day + 1)
    {
    case 1:
        int temp_values1[] = {18, 20, 13, 3, 0, 24, 26};
        size = sizeof(temp_values1) / sizeof(temp_values1[0]);
        memcpy(new_values, temp_values1, sizeof(temp_values1));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(30, time_scroll);
        break;
    case 2:
        int temp_values2[] = {12, 14, 13, 3, 0, 24, 26};
        size = sizeof(temp_values2) / sizeof(temp_values2[0]);
        memcpy(new_values, temp_values2, sizeof(temp_values2));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(30, time_scroll);
        break;
    case 3:
        int temp_values3[] = {19, 20, 4, 18, 3, 0, 24, 26};
        size = sizeof(temp_values3) / sizeof(temp_values3[0]);
        memcpy(new_values, temp_values3, sizeof(temp_values3));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(31, time_scroll);
        break;
    case 4:
        int temp_values4[] = {22, 4, 3, 13, 4, 18, 3, 0, 24, 26};
        size = sizeof(temp_values4) / sizeof(temp_values4[0]);
        memcpy(new_values, temp_values4, sizeof(temp_values4));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(33, time_scroll);
        break;
    case 5:
        int temp_values5[] = {19, 7, 20, 17, 18, 3, 0, 24, 26};
        size = sizeof(temp_values5) / sizeof(temp_values5[0]);
        memcpy(new_values, temp_values5, sizeof(temp_values5));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(32, time_scroll);
        break;
    case 6:
        int temp_values6[] = {5, 17, 8, 3, 0, 24, 26};
        size = sizeof(temp_values6) / sizeof(temp_values6[0]);
        memcpy(new_values, temp_values6, sizeof(temp_values6));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(30, time_scroll);
        break;
    case 7:
        int temp_values7[] = {18, 0, 19, 20, 17, 3, 0, 24, 26};
        size = sizeof(temp_values7) / sizeof(temp_values7[0]);
        memcpy(new_values, temp_values7, sizeof(temp_values7));
        if (time_flag_day)
        {
            break;
        }
        scroll_character(32, time_scroll);
        break;
    default:
        ESP_LOGE(TAG, "ERROR_in dayprint");
        break;
    }

    for (int i = 0; i < size; i++)
    {
        time_scroll[23 + i] = new_values[i];
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "time:-  %02d:%02d:%02d, Date: %02d/%02d/%d day:%d", current_hour, current_minute, seconds, date, month, year, day);

    static httpd_handle_t server = NULL;
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STADISCONNECTED, &disconnect_handler, &server));

    adc1_config_width(ADC_WIDTH_BIT);                     // config bit width
    adc1_config_channel_atten(ADC_GPIO, ADC_ATTENUATION); // config analog attenuation

    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));                                  // allocate memory to calloc
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTENUATION, ADC_WIDTH_BIT, DEFAULT_VREF, adc_chars); // initialize calibration

    ESP_LOGI(TAG, "ADC  %d", adc);
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "ESP32-Access-Point",
            .ssid_len = strlen("ESP32-Access-Point"),
            .password = "password",
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
        },
    };
    if (strlen("password") == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", "ESP32-Access-Point", "password");
    i2c_master_init();
    server = start_wss_echo_server();
    spi_init();
    max7219_init_all();

    semaphore1 = xSemaphoreCreateBinary();
    semaphore2 = xSemaphoreCreateBinary();
    semaphore3 = xSemaphoreCreateBinary();

    button_init(DOWN_PIN);
    button_init(UP_PIN);
    button_init(SET_PIN);

    initialize_isr_service();

    xTaskCreate(&task1, "Task1", 2048, NULL, 5, NULL);
    xTaskCreate(&task2, "Task2", 2048, NULL, 5, NULL);
    xTaskCreate(&task3, "Task3", 2048, NULL, 5, NULL);

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ALARM_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    TickType_t last_wake_time = xTaskGetTickCount();
    gpio_config(&io_conf);
    gpio_set_direction(ALARM_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(ALARM_PIN, 0);
    while (1)
    {
        ESP_LOGI(TAG, "time:-  %02d:%02d:%02d, Date: %02d/%02d/%d day:%d", current_hour, current_minute, seconds, date, month, year, day);
        get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
        ESP_LOGI(TAG, "time:-  %02d:%02d:%02d, Date: %02d/%02d/%d day:%d", current_hour, current_minute, seconds, date, month, year, day);
        display_number(current_hour, current_minute);

        if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
        {
            // update_time_flag = false;
            for (int i = 0; i < 50; i++)
            {
                int date_set[4] = {3, 3, date / 10, date % 10};
                int month_set[4] = {12, 12, month / 10, month % 10};
                int year_set[4] = {24, 24, ((year % 100) / 10), (year % 10)};
                int blank_set[4] = {26, 26, 26, 26};
                get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
                if (time_flag_hour)
                {
                    number_set_display(current_hour, current_minute, 1);
                }
                if (time_flag_minute)
                {
                    number_set_display(current_hour, current_minute, 2);
                }
                if (time_flag_date)
                {
                    date_set_display(date_set);
                }
                if (time_flag_month)
                {
                    date_set_display(month_set);
                }
                if (time_flag_year)
                {
                    date_set_display(year_set);
                }
                if (time_flag_day)
                {
                    volatile int time_scroll[40] = {current_hour / 10, current_hour % 10, current_minute / 10, current_minute % 10, 13, 13, 13, 13, date / 10, date % 10, 12, month / 10, month % 10, 12, 2, 0, ((year % 100) / 10), (year % 10), 13, 13, 13, 13};

                    day_time(time_scroll, day);
                    day_set_display(day_set);
                }

                vTaskDelay(200 / portTICK_PERIOD_MS);
            }
            time_flag_minute = false;
            time_flag_hour = false;
            time_flag_date = false;
            time_flag_month = false;
            time_flag_year = false;
            time_flag_day = false;
            update_time_flag = false;
            update_time_flag_1 = false;
        }

        for (int i = 0; i < 5; i++)
        {
            get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
            display_number(current_hour, current_minute);

            ESP_LOGI(TAG, "ALARM time  %02d:%02d", alarm_hour, alarm_minute);
            ESP_LOGI(TAG, "current time  %02d:%02d", current_hour, current_minute);

            if (current_hour == alarm_hour && current_minute == alarm_minute)
            {
                ESP_LOGI(TAG, "Alarm triggered");
                gpio_set_level(ALARM_PIN, 1);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                gpio_set_level(ALARM_PIN, 0);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            if (update_time_flag == true)
            {
                update_time_flag = false;
                break;
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        volatile int time_scroll[40] = {current_hour / 10, current_hour % 10, current_minute / 10, current_minute % 10, 13, 13, 13, 13, date / 10, date % 10, 12, month / 10, month % 10, 12, 2, 0, ((year % 100) / 10), (year % 10), 13, 13, 13, 13};
        get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
        // scroll_number(23, time_scroll);
        day_time(time_scroll, day);
    }
}
