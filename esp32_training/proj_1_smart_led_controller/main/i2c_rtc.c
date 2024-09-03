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
