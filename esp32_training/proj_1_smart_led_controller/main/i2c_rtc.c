// // #include <stdio.h>
// // #include "freertos/FreeRTOS.h"
// // #include "freertos/task.h"
// // #include "driver/i2c.h"
// // #include "esp_log.h"
// // #include "rtc.h"

// // #define I2C_MASTER_SCL_IO 22      // GPIO number for I2C SCL pin
// // #define I2C_MASTER_SDA_IO 21      // GPIO number for I2C SDA pin
// // #define I2C_MASTER_NUM I2C_NUM_0  // I2C port number
// // #define I2C_MASTER_FREQ_HZ 100000 // I2C master clock frequency
// // #define RTC_ADDRESS 0x68          // I2C address of RTC
// // volatile int i = 0;
// // static const char *TAG = "RTC";

// // void i2c_master_init()
// // {
// //     i2c_config_t conf = {
// //         .mode = I2C_MODE_MASTER,//i2c master
// //         .sda_io_num = I2C_MASTER_SDA_IO,//sda pin specifies
// //         .sda_pullup_en = GPIO_PULLUP_ENABLE,//
// //         .scl_io_num = I2C_MASTER_SCL_IO,//scl pin specifies
// //         .scl_pullup_en = GPIO_PULLUP_ENABLE,
// //         .master.clk_speed = I2C_MASTER_FREQ_HZ};//frequency set
// //     i2c_param_config(I2C_MASTER_NUM, &conf);//it config the structure to given port
// //     i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
// // }

// // void set_rtc_time()
// // {
// //     uint8_t data[7];
// //     data[0] = 0;    // Start from register 0 sec
// //     data[1] = 0x19; // Minutes
// //     data[2] = 0x10; // Hours
// //     // Set date to 07/07/2024
// //     data[3] = 0x02; // Day of the week (Sunday)
// //     data[4] = 0x21; // Date
// //     data[5] = 0x05; // Month
// //     data[6] = 0x24; // Year (Assuming it's 2024)

// //    // Write data to RTC
// //     i2c_cmd_handle_t cmd = i2c_cmd_link_create();//build for i2c
// //     i2c_master_start(cmd);//start of i2c
// //     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);
// //     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds) here true for ack
// //     i2c_master_write(cmd, data, 7, true);   // Write 7 bytes (seconds, minutes, hours, day, date, month, year)
// //     i2c_master_stop(cmd);
// //     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);//wait for specific timeperiod
// //     i2c_cmd_link_delete(cmd);//after complete
// // }

// // void get_rtc_time()
// // {
// //     uint8_t data[7];
// //     i2c_cmd_handle_t cmd = i2c_cmd_link_create();//create command handdle
// //     i2c_master_start(cmd);//start
// //     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);//write data from master to slave here true is for ack
// //     i2c_master_write_byte(cmd, 0x00, true);//write a byte from starting address
// //     i2c_master_start(cmd);//start
// //     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_READ, true);//
// //     i2c_master_read(cmd, data, 7, I2C_MASTER_LAST_NACK);//read from master
// //     i2c_master_stop(cmd);//stop
// //     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);//execute 1 sec
// //     i2c_cmd_link_delete(cmd);//clean up

// //     // Convert BCD to decimal
// //     int seconds = ((data[0] & 0xF0) >> 4) * 10 + (data[0] & 0x0F);
// //     int minutes = ((data[1] & 0xF0) >> 4) * 10 + (data[1] & 0x0F);
// //     int hours = ((data[2] & 0x30) >> 4) * 10 + (data[2] & 0x0F);
// //     int date = ((data[4] & 0x30) >> 4) * 10 + (data[4] & 0x0F);
// //     int month = ((data[5] & 0x10) >> 4) * 10 + (data[5] & 0x0F);
// //     int year = ((data[6] & 0xF0) >> 4) * 10 + (data[6] & 0x0F);

// //     ESP_LOGI(TAG, "RTC Time: %02d:%02d:%02d, Date: %02d/%02d/20%02d", hours, minutes, seconds, date, month, year);
// // }

// // void app_main()
// // {

// //     ESP_LOGI(TAG, "Initializing I2C master...");
// //     i2c_master_init();

// //     ESP_LOGI(TAG, "Setting RTC time...");
// //         set_rtc_time();

// //     while (1)
// //     {
// //         get_rtc_time();
// //         vTaskDelay(pdMS_TO_TICKS(1000)); // Update to use pdMS_TO_TICKS for clarity
// //     }
// // }
//  #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/i2c.h"
// #include "esp_log.h"
// #include "rtc.h"

// #define I2C_MASTER_SCL_IO 22      // GPIO number for I2C SCL pin
// #define I2C_MASTER_SDA_IO 21      // GPIO number for I2C SDA pin
// #define I2C_MASTER_NUM I2C_NUM_0  // I2C port number
// #define I2C_MASTER_FREQ_HZ 100000 // I2C master clock frequency
// #define RTC_ADDRESS 0x68          // I2C address of RTC

// static const char *TAG = "RTC";

// void i2c_master_init()
// {
//     i2c_config_t conf = {
//         .mode = I2C_MODE_MASTER,
//         .sda_io_num = I2C_MASTER_SDA_IO,
//         .sda_pullup_en = GPIO_PULLUP_ENABLE,
//         .scl_io_num = I2C_MASTER_SCL_IO,
//         .scl_pullup_en = GPIO_PULLUP_ENABLE,
//         .master.clk_speed = I2C_MASTER_FREQ_HZ
//     };
//     i2c_param_config(I2C_MASTER_NUM, &conf);
//     i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
// }

// void set_rtc_time(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
// {
//     uint8_t data[7];
//     data[0] = seconds; // Seconds
//     data[1] = minutes; // Minutes
//     data[2] = hours;   // Hours
//     data[3] = day;     // Day of the week
//     data[4] = date;    // Date
//     data[5] = month;   // Month
//     data[6] = year;    // Year

//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds)
//     i2c_master_write(cmd, data, 7, true);   // Write 7 bytes (seconds, minutes, hours, day, date, month, year)
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
// }

// void get_rtc_time()
// {
//     uint8_t data[7];
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds)
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_READ, true);
//     i2c_master_read(cmd, data, 7, I2C_MASTER_LAST_NACK);
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);

//     // Convert BCD to decimal
//     int seconds = ((data[0] & 0xF0) >> 4) * 10 + (data[0] & 0x0F);
//     int minutes = ((data[1] & 0xF0) >> 4) * 10 + (data[1] & 0x0F);
//     int hours = ((data[2] & 0x30) >> 4) * 10 + (data[2] & 0x0F);
//     int date = ((data[4] & 0x30) >> 4) * 10 + (data[4] & 0x0F);
//     int month = ((data[5] & 0x10) >> 4) * 10 + (data[5] & 0x0F);
//     int year = ((data[6] & 0xF0) >> 4) * 10 + (data[6] & 0x0F);

//     ESP_LOGI(TAG, "RTC Time: %02d:%02d:%02d, Date: %02d/%02d/20%02d", hours, minutes, seconds, date, month, year);
// }

// #include "rtc.h"
// #include "driver/i2c.h"
// #include "esp_log.h"

// #define I2C_MASTER_SCL_IO 22      // GPIO number for I2C SCL pin
// #define I2C_MASTER_SDA_IO 21      // GPIO number for I2C SDA pin
// #define I2C_MASTER_NUM I2C_NUM_0  // I2C port number
// #define I2C_MASTER_FREQ_HZ 100000 // I2C master clock frequency
// #define RTC_ADDRESS 0x68          // I2C address of RTC
// #define ALARM_PIN 14              // SET ALARM PIN

// static const char *TAG = "RTC";

// void i2c_master_init()
// {
//     i2c_config_t conf = {
//         .mode = I2C_MODE_MASTER,
//         .sda_io_num = I2C_MASTER_SDA_IO,
//         .sda_pullup_en = GPIO_PULLUP_ENABLE,
//         .scl_io_num = I2C_MASTER_SCL_IO,
//         .scl_pullup_en = GPIO_PULLUP_ENABLE,
//         .master.clk_speed = I2C_MASTER_FREQ_HZ};
//     i2c_param_config(I2C_MASTER_NUM, &conf);
//     i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
// }

// void set_rtc_time(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
// {
//     uint8_t data[7];
//     data[0] = ((seconds / 10) << 4) | (seconds % 10); // BCD format
//     data[1] = ((minutes / 10) << 4) | (minutes % 10);
//     data[2] = ((hours / 10) << 4) | (hours % 10);
//     data[3] = day;
//     data[4] = ((date / 10) << 4) | (date % 10);
//     data[5] = ((month / 10) << 4) | (month % 10);
//     data[6] = ((year / 10) << 4) | (year % 10);

//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds)
//     i2c_master_write(cmd, data, 7, true);   // Write 7 bytes (seconds, minutes, hours, day, date, month, year)
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
// }
// // void set_rtc_alarm(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
// // {
// //     uint8_t data_alarm[7];
// //     data_alarm[0] = ((seconds / 10) << 4) | (seconds % 10); // BCD format
// //     data_alarm[1] = ((minutes / 10) << 4) | (minutes % 10);
// //     data_alarm[2] = ((hours / 10) << 4) | (hours % 10);
// //     data_alarm[3] = day;
// //     data_alarm[4] = ((date / 10) << 4) | (date % 10);
// //     data_alarm[5] = ((month / 10) << 4) | (month % 10);
// //     data_alarm[6] = ((year / 10) << 4) | (year % 10);

// //     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
// //     i2c_master_start(cmd);
// //     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);
// //     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds)
// //     i2c_master_write(cmd, data_alarm, 7, true);   // Write 7 bytes (seconds, minutes, hours, day, date, month, year)
// //     i2c_master_stop(cmd);
// //     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
// //     i2c_cmd_link_delete(cmd);
// // }

// void get_rtc_time(int *a, int *b)
// {
//     uint8_t data[7];
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds)
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (RTC_ADDRESS << 1) | I2C_MASTER_READ, true);
//     i2c_master_read(cmd, data, 7, I2C_MASTER_LAST_NACK);
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);

//     // Convert BCD to decimal
//     int seconds = ((data[0] & 0xF0) >> 4) * 10 + (data[0] & 0x0F);
//     int minutes = ((data[1] & 0xF0) >> 4) * 10 + (data[1] & 0x0F);
//     int hours =   ((data[2] & 0x30) >> 4) * 10 + (data[2] & 0x0F);
//     int date =    ((data[4] & 0x30) >> 4) * 10 + (data[4] & 0x0F);
//     int month =   ((data[5] & 0x10) >> 4) * 10 + (data[5] & 0x0F);
//     int year = ((data[6] & 0xF0) >> 4) * 10 + (data[6] & 0x0F);

//     *a = hours;
//     *b = minutes;

//     ESP_LOGI(TAG, "RTC Time: %02d:%02d:%02d, Date: %02d/%02d/20%02d", hours, minutes, seconds, date, month, year);
// }

// void alarm_task()
// {
//     int alarm_hours = 11;
//     int alarm_minutes = 50;
//     gpio_set_level(ALARM_PIN, 0);
//     gpio_set_direction(ALARM_PIN, GPIO_MODE_OUTPUT);

//     int current_hours, current_minutes;
//     get_rtc_time(&current_hours, &current_minutes);

//     if (current_hours == alarm_hours && current_minutes == alarm_minutes)
//     {
//         gpio_set_level(ALARM_PIN, 1);
//         vTaskDelay(pdMS_TO_TICKS(10000));
//         gpio_set_level(ALARM_PIN, 0);
//     }
// }
/////////////////////////only for web,clock,rtc
// #include <stdio.h>
// #include <stdio.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_log.h"
// #include "esp_event.h"
// #include "nvs_flash.h"
// #include "esp_netif.h"
// #include "esp_wifi.h"
// #include "esp_https_server.h"
// #include "sdkconfig.h"
// #include "max7219.h"
// #include "rtc.h" //rtc

// static const char *TAG = "main"; // A constant character pointer used for logging.

// struct async_resp_arg // structure for asynchronous response arg
// {
//     httpd_handle_t hd;
//     int fd;
// };

// // Define the maximum number of clients that can connect to the AP
// #define MAX_STA_CONN 4 // A macro defining the maximum number of client connections allowed to the Wi-Fi access point (AP).

// static esp_err_t ws_handler(httpd_req_t *req)
// {
//     if (req->method == HTTP_GET) // Checks if the request method is a GET request.
//     {
//         ESP_LOGI(TAG, "Handshake done, the new connection was opened"); // Logs a message indicating that the WebSocket handshake is complete.
//         return ESP_OK;                                                  // Returns an OK status, ending the function if it was a GET request.
//     }
//     httpd_ws_frame_t ws_pkt;                      // Declares a variable to hold the WebSocket frame.
//     uint8_t *buf = NULL;                          // Declares a buffer pointer and initializes it to NULL.
//     memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t)); // Initializes the ws_pkt structure to zero.

//     esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0); // Receives the WebSocket frame and gets its length.
//     if (ret != ESP_OK)                                    // Checks if the frame reception failed.
//     {
//         ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
//         return ret;
//     }
//     ESP_LOGI(TAG, "frame len is %d", ws_pkt.len); // Logs the frame length.
//     if (ws_pkt.len)                               // Logs the frame length.
//     {
//         buf = calloc(1, ws_pkt.len + 1); // Logs the frame length.
//         if (buf == NULL)                 // Checks if memory allocation failed.
//         {
//             ESP_LOGE(TAG, "Failed to calloc memory for buf");
//             return ESP_ERR_NO_MEM; // Returns a memory allocation error
//         }
//         ws_pkt.payload = buf;                                // Assigns the buffer to the payload
//         ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len); // Receives the WebSocket frame with the actual payload.
//         if (ret != ESP_OK)                                   // Checks if receiving the frame failed.
//         {
//             ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
//             free(buf);  // free buffer
//             return ret; // Returns the error code.
//         }
//     }

//     if (ws_pkt.type == HTTPD_WS_TYPE_TEXT) // Checks if the frame type is text.
//     {
//         ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload); // logs

//         // Assuming the message format is "SET_TIME hh:mm:ss dd/mm/yyyy"
//         int hours, minutes, seconds, day, month, year;
//         if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %2d/%2d/%4d", &hours, &minutes, &seconds, &day, &month, &year) == 6) // where to string read ,format ,where store
//         {
//             // Set the new time to the RTC module
//             set_rtc_time(seconds, minutes, hours, day, day, month, year - 2000);                                            // set rtc time
//             ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d", hours, minutes, seconds, day, month, year); // logs

//             // Send an acknowledgment back to the client
//             const char *ack = "Time set successfully"; // ack
//             ws_pkt.payload = (uint8_t *)ack;           // ack of payload(data)
//             ws_pkt.len = strlen(ack);                  // ack payload len
//             ret = httpd_ws_send_frame(req, &ws_pkt);   // Sends the WebSocket frame with the acknowledgment.
//             if (ret != ESP_OK)                         // Checks if sending the frame failed.
//             {
//                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
//             }
//         }
//         else if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d:%2d", &hours, &minutes, &seconds) == 3) // format to set alarm
//         {
//             // Set the alarm to the RTC module
//             set_rtc_alarm(seconds, minutes, hours, 0, 0, 0); // assuming alarm does not need date
//             ESP_LOGI(TAG, "RTC alarm set to %02d:%02d:%02d", hours, minutes, seconds); // logs

//             // Send an acknowledgment back to the client
//             const char *ack = "Alarm set successfully"; // ack
//             ws_pkt.payload = (uint8_t *)ack;           // ack of payload(data)
//             ws_pkt.len = strlen(ack);                  // ack payload len
//             ret = httpd_ws_send_frame(req, &ws_pkt);   // Sends the WebSocket frame with the acknowledgment.
//             if (ret != ESP_OK)                         // Checks if sending the frame failed.
//             {
//                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
//             }
//         }
//         else
//         {
//             ESP_LOGE(TAG, "Failed to parse time string: %s", ws_pkt.payload); // if failed parsing
//         }
//         free(buf); // free buffer
//         return ESP_OK;
//     }
//     return ESP_FAIL; // Return failure if packet type is not text
// }

// static esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd) // ws open when new client connected logs
// {
//     ESP_LOGI(TAG, "New client connected %d", sockfd);
//     return ESP_OK;
// }

// static void wss_close_fd(httpd_handle_t hd, int sockfd) /// ws open when new client disconnected logs
// {
//     ESP_LOGI(TAG, "Client disconnected %d", sockfd);
// }

// static httpd_handle_t start_wss_echo_server(void) // start web socket server
// {
//     httpd_handle_t server = NULL;                   // Declares a variable for the server handle, initializing it to NULL.
//     httpd_config_t config = HTTPD_DEFAULT_CONFIG(); // Declares and initializes a configuration structure.
//     config.open_fn = wss_open_fd;                   // Sets the function to be called when a new connection is opened.
//     config.close_fn = wss_close_fd;                 // closed

//     esp_err_t ret = httpd_start(&server, &config); // Starts the HTTP server with the given configuration.
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
//         return NULL; // Logs an error message if the server fails to start.
//     }

//     httpd_uri_t ws = {
//         .uri = "/ws",          // end point ws
//         .method = HTTP_GET,    // constant get from http
//         .handler = ws_handler, // func name
//         .is_websocket = true,
//         .supported_subprotocol = NULL,
//     };

//     ret = httpd_register_uri_handler(server, &ws); // Registers the URI handler.
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
//         httpd_stop(server); // Logs an error message if registration fails
//         return NULL;
//     }

//     return server;
// }

// static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) // Function definition for handling disconnect events.
// {
//     httpd_handle_t *server = (httpd_handle_t *)arg;
//     if (*server)
//     {
//         httpd_stop(*server);
//         *server = NULL;
//     }
// }

// static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) //  Function definition for handling connect events.
// {
//     httpd_handle_t *server = (httpd_handle_t *)arg;
//     if (*server == NULL)
//     {
//         *server = start_wss_echo_server();
//     }
// }

// void app_main(void)
// {
//     static httpd_handle_t server = NULL; // server var as null
//     esp_err_t ret = nvs_flash_init();    // The type of the variable, which will hold the return code from the nvs_flash_init function.
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
//     {
//         ESP_ERROR_CHECK(nvs_flash_erase()); // Erase the NVS flash and check for errors.
//         ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(ret);

//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_ap();

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));

//     wifi_config_t ap_config = {
//         .ap = {
//             .ssid = "my_ap",
//             .ssid_len = strlen("my_ap"),
//             .channel = 1,
//             .password = "password",
//             .max_connection = MAX_STA_CONN,
//             .authmode = WIFI_AUTH_WPA_WPA2_PSK},
//     };

//     if (strlen("password") == 0)
//     {
//         ap_config.ap.authmode = WIFI_AUTH_OPEN;
//     }

//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
//     ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &ap_config));
//     ESP_ERROR_CHECK(esp_wifi_start());

//     ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
//     ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STADISCONNECTED, &disconnect_handler, &server));
// }

// this is code for // ws time and alarm set and display led on//

// #include "rtc.h"
// #include "driver/i2c.h"
// #include "driver/gpio.h"
// #include "esp_log.h"

// #define I2C_MASTER_SCL_IO 22      // GPIO number for I2C SCL
// #define I2C_MASTER_SDA_IO 21      // GPIO number for I2C SDA
// #define I2C_MASTER_NUM I2C_NUM_0  // I2C port number for master
// #define I2C_MASTER_TX_BUF_DISABLE 0
// #define I2C_MASTER_RX_BUF_DISABLE 0
// #define I2C_MASTER_FREQ_HZ 100000

// #define DS3231_ADDR 0x68       // I2C address of DS3231 RTC
// #define DS3231_REG_TIME 0x00   // Address of the time register in DS3231
// #define DS3231_REG_ALARM1 0x07 // Address of the alarm 1 register in DS3231

// static const char *TAG = "rtc";

// // Function to initialize I2C master
// esp_err_t i2c_master_init(void)
// {
//     i2c_config_t conf = {
//         .mode = I2C_MODE_MASTER,
//         .sda_io_num = I2C_MASTER_SDA_IO,
//         .scl_io_num = I2C_MASTER_SCL_IO,
//         .sda_pullup_en = GPIO_PULLUP_ENABLE,
//         .scl_pullup_en = GPIO_PULLUP_ENABLE,
//         .master.clk_speed = I2C_MASTER_FREQ_HZ,
//     };
//     i2c_param_config(I2C_MASTER_NUM, &conf);
//     return i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
// }

// // Function to write to DS3231 RTC registers
// static esp_err_t ds3231_write_register(uint8_t reg_addr, uint8_t *data, size_t len)
// {
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, reg_addr, true);
//     i2c_master_write(cmd, data, len, true);
//     i2c_master_stop(cmd);
//     esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

// // Function to read from DS3231 RTC registers
// static esp_err_t ds3231_read_register(uint8_t reg_addr, uint8_t *data, size_t len)
// {
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, reg_addr, true);
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_READ, true);
//     i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
//     i2c_master_stop(cmd);
//     esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
//     return ret;
// }

// // Function to set RTC time
// esp_err_t set_rtc_time(int sec, int min, int hour, int date, int month, int year)
// {
//     uint8_t data[7];
//     data[0] = (sec / 10) << 4 | (sec % 10);
//     data[1] = (min / 10) << 4 | (min % 10);
//     data[2] = (hour / 10) << 4 | (hour % 10);
//     data[4] = (date / 10) << 4 | (date % 10);
//     data[5] = (month / 10) << 4 | (month % 10);
//     data[6] = ((year % 100) / 10) << 4 | (year % 10);
//     return ds3231_write_register(DS3231_REG_TIME, data, 7);
// }

// esp_err_t get_rtc_time(int *hour, int *minute)
// {
//     uint8_t data[3];
//     esp_err_t ret = ds3231_read_register(DS3231_REG_TIME, data, 3);
//     if (ret == ESP_OK)
//     {
//         *hour = ((data[2] >> 4) & 0x03) * 10 + (data[2] & 0x0F);
//         *minute = ((data[1] >> 4) & 0x07) * 10 + (data[1] & 0x0F);
//     }
//     return ret;
// }

// esp_err_t set_rtc_alarm(int hour, int minute)
// {
//     uint8_t data[4];
//     data[0] = (minute / 10) << 4 | (minute % 10);
//     data[1] = (hour / 10) << 4 | (hour % 10);
//     data[2] = 0x80;
//     data[3] = 0x80;
//     return ds3231_write_register(DS3231_REG_ALARM1, data, 4);
// }

#include "rtc.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define I2C_MASTER_SCL_IO 22     // GPIO number for I2C SCL
#define I2C_MASTER_SDA_IO 21     // GPIO number for I2C SDA
#define I2C_MASTER_NUM I2C_NUM_0 // I2C port number for master
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0
#define I2C_MASTER_FREQ_HZ 100000

#define DS3231_ADDR 0x68       // I2C address of DS3231 RTC
#define DS3231_REG_TIME 0x00   // Address of the time register in DS3231
#define DS3231_REG_ALARM1 0x07 // Address of the alarm 1 register in DS3231

static const char *TAG = "rtc";

esp_err_t i2c_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t ds3231_write_register(uint8_t reg_addr, uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t ds3231_read_register(uint8_t reg_addr, uint8_t *data, size_t len)

{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t set_rtc_time(int sec, int min, int hour, int day, int date, int month, int year)
{
    uint8_t data[7];
    data[0] = (sec / 10) << 4 | (sec % 10);
    data[1] = (min / 10) << 4 | (min % 10);
    data[2] = (hour / 10) << 4 | (hour % 10);
    data[3] = (day / 10) << 4 | (day % 10);
    data[4] = (date / 10) << 4 | (date % 10);
    data[5] = (month / 10) << 4 | (month % 10);
    data[6] = ((year % 100) / 10) << 4 | (year % 10);
    return ds3231_write_register(DS3231_REG_TIME, data, 7);
}

// esp_err_t get_rtc_time(int *hour, int *minute)
// {
//     uint8_t data[3];
//     esp_err_t ret = ds3231_read_register(DS3231_REG_TIME, data, 3);
//     if (ret == ESP_OK)
//     {
//         *hour = ((data[2] >> 4) & 0x03) * 10 + (data[2] & 0x0F);
//         *minute = ((data[1] >> 4) & 0x07) * 10 + (data[1] & 0x0F);
//     }
//     return ret;
// }
// esp_err_t get_rtc_time(int *hour, int *minute, int *day, int *date, int *month, int *year)
// {
//     // uint8_t data[7];
//     // esp_err_t ret = ds3231_read_register(DS3231_REG_TIME, data, 7);
//     // if (ret == ESP_OK)
//     // {
//     //     *hour = ((data[2] >> 4) & 0x03) * 10 + (data[2] & 0x0F);
//     //     *minute = ((data[1] >> 4) & 0x07) * 10 + (data[1] & 0x0F);
//     //     *day = data[3];
//     //     *date = ((data[4] & 0x30) >> 4) * 10 + (data[4] & 0x0F);
//     //     *month = ((data[5] & 0x10) >> 4) * 10 + (data[5] & 0x0F);
//     //     *year = ((data[6] & 0xF0) >> 4) * 10 + (data[6] & 0x0F);
//     // }
//     // return ret;
//     uint8_t data[7];
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, 0x00, true); // Start from register 0 (seconds)
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, (DS3231_ADDR << 1) | I2C_MASTER_READ, true);
//     i2c_master_read(cmd, data, 7, I2C_MASTER_LAST_NACK);
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
//     // Convert BCD to decimal
//     // *second = ((data[0] & 0xF0) >> 4) * 10 + (data[0] & 0x0F);
//     *minute = ((data[1] & 0xF0) >> 4) * 10 + (data[1] & 0x0F);
//     *hour = ((data[2] & 0x30) >> 4) * 10 + (data[2] & 0x0F);
//     *day = data[3];
//     *date = ((data[4] & 0x30) >> 4) * 10 + (data[4] & 0x0F);
//     *month = ((data[5] & 0x10) >> 4) * 10 + (data[5] & 0x0F);
//     *year = ((data[6] & 0xF0) >> 4) * 10 + (data[6] & 0x0F);
// }
void get_rtc_time(int *hours, int *minutes, int *day, int *date, int *month, int *year)
{
    uint8_t data[7];
    esp_err_t ret;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x68 << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x00, true);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C write failed with error: %s", esp_err_to_name(ret));
        return;
    }

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x68 << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 7, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C read failed with error: %s", esp_err_to_name(ret));
        return;
    }

    // Logging raw data for debugging
    ESP_LOGI("I2C", "Raw RTC data: %02x %02x %02x %02x %02x %02x %02x",
             data[0], data[1], data[2], data[3], data[4], data[5], data[6]);

    *minutes = (data[1] & 0x0F) + ((data[1] >> 4) & 0x07) * 10;
    *hours = (data[2] & 0x0F) + ((data[2] >> 4) & 0x03) * 10;
    *day = data[3] & 0x07;
    *date = (data[4] & 0x0F) + ((data[4] >> 4) & 0x03) * 10;
    *month = (data[5] & 0x0F) + ((data[5] >> 4) & 0x01) * 10;
    *year = (data[6] & 0x0F) + ((data[6] >> 4) & 0x0F) * 10 + 2000;

    // Logging decoded time for debugging
    ESP_LOGI("I2C", "Decoded time: %02d:%02d, Date: %02d/%02d/%04d, Day: %d",
             *hours, *minutes, *date, *month, *year, *day);
}


esp_err_t set_rtc_alarm(int hour, int minute)
{
    uint8_t data[4];
    data[0] = (minute / 10) << 4 | (minute % 10);
    data[1] = (hour / 10) << 4 | (hour % 10);
    data[2] = 0x80;
    data[3] = 0x80;
    return ds3231_write_register(DS3231_REG_ALARM1, data, 4);
}
