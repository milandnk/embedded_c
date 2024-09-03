#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>

#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK 18
#define PIN_NUM_CS 5

extern bool update_time_flag;
extern bool update_time_flag_1;
extern bool update_time_flag_2;
extern bool time_flag_minute;
extern bool time_flag_hour;
extern bool time_flag_date;
extern bool time_flag_month;
extern bool time_flag_year;
extern bool time_flag_day;
extern int adc;

void spi_init(void);
void max7219_init_all(void);
void max7219_send_byte_all(uint8_t address, uint8_t data);
void set_column_on_display(int display, uint8_t row, uint8_t data);
void brightness_set(int adc);
void display_frame(uint8_t frame[4][8]);
void scroll_number(int n, int str[n]);
void scroll_all(int time[16], int n, int str[n]);
void scroll_character(int n, int str[n]);
void set_digit_on_display(int display, uint8_t address, uint8_t data);
void display_number(int hour, int minute);
void number_set_display(int hour, int minute, int n);
void date_set_display(int str[4]);
void day_set_display(int str[4]);
void push_brightness();
#endif // MAX7219_H
