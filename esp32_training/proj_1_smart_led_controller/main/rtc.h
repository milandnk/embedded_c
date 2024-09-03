// #ifndef _RTC_H_
// #define _RTC_H_

// #include <stdint.h>

// void i2c_master_init(void);
// void set_rtc_time(int seconds, int minutes, int hours, int date, int month, int year);
// void get_rtc_time(int *hours, int *minutes);
// void alarm_task(void);
// void set_rtc_alarm(int alarm_hour, int alarm_minute);

// #endif // _RTC_H_
#ifndef _RTC_H_
#define _RTC_H_

#include <stdint.h>
#include "esp_err.h"

esp_err_t i2c_master_init(void);
esp_err_t set_rtc_time(int sec, int min, int hour, int day, int date, int month, int year);
// esp_err_t set_rtc_time(int sec, int min, int hour, int date, int month, int year);
// esp_err_t get_rtc_time(int *hour, int *minute);
void get_rtc_time(int *hours, int *minutes, int *day, int *date, int *month, int *year);
esp_err_t set_rtc_alarm(int hour, int minute);
void set_rtc_time_interrupt(int minutes, int hours);
// esp_err_t ds3231_write_register(uint8_t reg_addr, uint8_t *data, size_t len);

// esp_err_t set_rtc_time_interrupt(int min, int hour);

#endif // _RTC_H_
