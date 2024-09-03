// #include <stdio.h>
// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/spi_master.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "esp_err.h"
// #include "rtc.h"
// #include "max7219.h"
// #include "driver/adc.h"
// #include "esp_adc_cal.h"
// #include "esp_adc/adc_continuous.h"

// #define PIN_NUM_MOSI 23
// #define PIN_NUM_CLK 18
// #define PIN_NUM_CS 5

// #define DEFAULT_VREF 1100               // Default ADC reference voltage in mV
// #define ADC_WIDTH_BIT ADC_WIDTH_BIT_12  // ADC bit width (9, 10, 11, or 12)
// #define ADC_ATTENUATION ADC_ATTEN_DB_12 // ADC attenuation (0db, 2.5db, 6db, 11db)
// #define PORT_TICK_PERIOD_MS 1000        // Tick period in milliseconds
// #define ADC_GPIO ADC1_CHANNEL_5         // ADC channel for GPIO33

// volatile bool blink = 0;
// bool update_time_flag = false;
// bool update_time_flag_1 = false;
// bool time_flag_minute = false;
// bool time_flag_hour = false;
// int adc;
// static spi_device_handle_t spi;

// // Function to initialize the SPI bus
// void spi_init()
// {
//     spi_bus_config_t buscfg = {
//         .miso_io_num = -1,
//         .mosi_io_num = PIN_NUM_MOSI,
//         .sclk_io_num = PIN_NUM_CLK,
//         .quadwp_io_num = -1,
//         .quadhd_io_num = -1,
//         .max_transfer_sz = 32 * 4};

//     spi_device_interface_config_t devcfg = {
//         .clock_speed_hz = 1000000,
//         .mode = 0,
//         .spics_io_num = PIN_NUM_CS,
//         .queue_size = 7,
//         .flags = SPI_DEVICE_HALFDUPLEX};

//     ESP_ERROR_CHECK(spi_bus_initialize(VSPI_HOST, &buscfg, 1));
//     ESP_ERROR_CHECK(spi_bus_add_device(VSPI_HOST, &devcfg, &spi));
// }

// void max7219_send_byte_all(uint8_t address, uint8_t data)
// {
//     spi_transaction_t t;
//     memset(&t, 0, sizeof(t));
//     uint8_t buffer[4 * 2];

//     for (int i = 0; i < 4; i++)
//     {
//         buffer[i * 2] = address;
//         buffer[i * 2 + 1] = data;
//     }

//     t.length = 8 * sizeof(buffer);
//     t.tx_buffer = buffer;
//     spi_device_transmit(spi, &t);
// }

// void max7219_init_all()
// {
//     max7219_send_byte_all(0x0C, 0x01); // Normal operation mode
//     max7219_send_byte_all(0x09, 0x00); // No decode mode for digits
//     max7219_send_byte_all(0x0B, 0x07); // Display digits 0-7
//     max7219_send_byte_all(0x0A, 0x0F); // Maximum intensity
//     max7219_send_byte_all(0x0F, 0x00); // Normal display test mode
// }

// // Bit patterns for numbers 0-9 and dot
// const uint8_t number_font[14][8] = {
//     {0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c}, // 0
//     {0x08, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7e, 0x7e}, // 1
//     {0x3c, 0x7e, 0x46, 0x0c, 0x18, 0x30, 0x7e, 0x7e}, // 2
//     {0x7e, 0x7e, 0x04, 0x18, 0x1c, 0x06, 0x7e, 0x7c}, // 3
//     {0x04, 0x0c, 0x1c, 0x2c, 0x4c, 0x7e, 0x0c, 0x0c}, // 4
//     {0x7e, 0x7e, 0x40, 0x7c, 0x06, 0x06, 0x66, 0x3c}, // 5
//     {0x3c, 0x7e, 0x40, 0x7c, 0x66, 0x66, 0x66, 0x3c}, // 6
//     {0x7e, 0x7e, 0x46, 0x0c, 0x18, 0x18, 0x18, 0x18}, // 7
//     {0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x66, 0x3c}, // 8
//     {0x3c, 0x66, 0x66, 0x7e, 0x06, 0x06, 0x46, 0x3c}, // 9
//     {0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00}, // dot1
//     {0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00},
//     {0x06, 0x06, 0x0e, 0x1c, 0x38, 0x70, 0x60, 0x60},  // slash
//     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}; // blank

// const uint8_t letter_font[27][8] = {
//     {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66},  // A1
//     {0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0x7C},  // B2
//     {0x3C, 0x66, 0x60, 0x60, 0x60, 0x60, 0x66, 0x3C},  // C3
//     {0x78, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x6C, 0x78},  // D4
//     {0x7e, 0x60, 0x60, 0x7c, 0x7c, 0x60, 0x60, 0x7e},  // E5
//     {0x7E, 0x60, 0x60, 0x7C, 0x7C, 0x60, 0x60, 0x60},  // F6
//     {0x3C, 0x66, 0x60, 0x60, 0x6E, 0x66, 0x66, 0x3E},  // G7
//     {0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66},  // H8
//     {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C},  // I9
//     {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x6C, 0x6C, 0x38},  // J10
//     {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x66},  // K11
//     {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x7e},  // L2
//     {0x42, 0x66, 0x7e, 0x5a, 0x5a, 0x42, 0x42, 0x42},  // M3
//     {0x46, 0x66, 0x66, 0x76, 0x7e, 0x6e, 0x66, 0x62},  // N4
//     {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C},  // O5
//     {0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60},  // P6
//     {0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x1e},  // Q7
//     {0x7C, 0x66, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66},  // R8
//     {0x3C, 0x66, 0x60, 0x3C, 0x06, 0x06, 0x66, 0x3C},  // S9
//     {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},  // T20
//     {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C},  // U1
//     {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18},  // V2
//     {0x42, 0x42, 0x42, 0x5a, 0x5a, 0x7e, 0x7e, 0x42},  // W3
//     {0x42, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x66, 0x42},  // X4
//     {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18},  // Y5
//     {0x7e, 0x7e, 0x06, 0x0c, 0x18, 0x30, 0x7e, 0x7e},  // Z6
//     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}; // blank

// // sunday 19,21,14,4,1,25
// // monday 13,15,14,4,1,25
// // tuesday 20,21,5,19,4,1,25
// // wednesday 23,5,4,14,5,19,4,1,25
// // thursday 10,8,21,18,19,4,1,25
// // friday 6,18,9,4,1,25
// // saturday 19,1,20,21,18,4,1,25
// void brightness_set(int adc)
// {
//     if (adc <= 273)
//     {
//         max7219_send_byte_all(0x0A, 0x01);
//     }
//     if (adc > 273 && adc <= 546)
//     {
//         max7219_send_byte_all(0x0A, 0x02);
//     }
//     if (adc > 546 && adc <= 819)
//     {
//         max7219_send_byte_all(0x0A, 0x03);
//     }
//     if (adc > 819 && adc <= 1092)
//     {
//         max7219_send_byte_all(0x0A, 0x04);
//     }
//     if (adc > 1092 && adc <= 1365)
//     {
//         max7219_send_byte_all(0x0A, 0x05);
//     }
//     if (adc > 1365 && adc <= 1688)
//     {
//         max7219_send_byte_all(0x0A, 0x06);
//     }
//     if (adc > 1688 && adc <= 1911)
//     {
//         max7219_send_byte_all(0x0A, 0x07);
//     }
//     if (adc > 1911 && adc <= 2184)
//     {
//         max7219_send_byte_all(0x0A, 0x08);
//     }
//     if (adc > 2184 && adc <= 2457)
//     {
//         max7219_send_byte_all(0x0A, 0x09);
//     }
//     if (adc > 2457 && adc <= 2730)
//     {
//         max7219_send_byte_all(0x0A, 0x0A);
//     }
//     if (adc > 2730 && adc <= 3003)
//     {
//         max7219_send_byte_all(0x0A, 0x0B);
//     }
//     if (adc > 3003 && adc <= 3276)
//     {
//         max7219_send_byte_all(0x0A, 0x0C);
//     }
//     if (adc > 3276 && adc <= 3549)
//     {
//         max7219_send_byte_all(0x0A, 0x0D);
//     }
//     if (adc > 3549 && adc <= 3822)
//     {
//         max7219_send_byte_all(0x0A, 0x0E);
//     }
//     if (adc > 3822 && adc <= 4095)
//     {
//         max7219_send_byte_all(0x0A, 0x0F);
//     }
// }

// void set_column_on_display(int display, uint8_t row, uint8_t data)
// {
//     spi_transaction_t t;
//     memset(&t, 0, sizeof(t));
//     uint8_t buffer[4 * 2] = {0};
//     buffer[display * 2] = row + 1;
//     buffer[display * 2 + 1] = data;

//     t.length = 8 * sizeof(buffer);
//     t.tx_buffer = buffer;
//     spi_device_transmit(spi, &t);
// }

// void display_frame(uint8_t frame[4][8])
// {
//     for (int row = 0; row < 8; row++)
//     {
//         for (int display = 0; display < 4; display++)
//         {
//             set_column_on_display(display, row, frame[display][row]);
//         }
//     }
// }

// void scroll_number(int n, int str[n]) 
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][4][8];

//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             if (i == 1 || i == 0)
//             {
//                 frames[i][0][row] = number_font[(uint8_t)str[i]][row] << 1;
//             }

//             if (i == 2 || i == 3)
//             {
//                 frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 1;
//             }
//             else
//             {
//                 frames[i][0][row] = number_font[(uint8_t)str[i]][row];
//             }
//         }
//     }

//     for (int s = 0; s < (num_digits - 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {0};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 if (s >= 8 && s <= 15)
//                 {
//                     for (int i = 0; i < num_digits; i++)
//                     {
//                         for (int row = 0; row < 8; row++)
//                         {
//                             if (i == 1)
//                             {
//                                 frames[i][0][row] = ((number_font[(uint8_t)str[i]][row] << 0x01) | number_font[10][row]);
//                             }
//                             if (i == 0)
//                             {
//                                 frames[i][0][row] = (number_font[(uint8_t)str[i]][row] << 0x01);
//                             }
//                             if (i == 2)
//                             {
//                                 frames[i][0][row] = ((number_font[(uint8_t)str[i]][row] >> 0x01) | number_font[11][row]);
//                             }
//                             if (i == 3)
//                             {
//                                 frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 0x01;
//                             }
//                         }
//                     }
//                 }
//                 int frame_NUM = (s / 8 + mat) % num_digits;
//                 int next_frame = (frame_NUM + 1) % num_digits;
//                 frame[mat][row] = frames[frame_NUM][0][row] << (s % 8);

//                 if ((s % 8) != 0 && next_frame < num_digits)
//                 {
//                     frame[mat][row] |= frames[next_frame][0][row] >> (8 - (s % 8));
//                 }
//             }
//         }

//         if (update_time_flag == true)
//         {
//             update_time_flag = false;
//             return;
//         }
//         adc = adc1_get_raw(ADC_GPIO);
//         printf("ADC  %d\n", adc);
//         brightness_set(adc);
//         display_frame(frame);
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//     }
// }

// void scroll_character(int n, int str[n])
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = letter_font[str[i]][row];
//         }
//     }
//     for (int s = 0; s < (num_digits + 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = s / 8 - 3 + mat;
//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//                 else if (frame_index == -1)
//                 {
//                     frame[mat][row] = 0x00 << (s % 8);
//                     if ((s % 8) != 0 && num_digits > 0)
//                     {
//                         frame[mat][row] |= frames[0][row] >> (8 - (s % 8));
//                     }
//                 }
//             }
//         }
//         if (update_time_flag_1 == true)
//         {
//             update_time_flag_1 = false;
//             return;
//         }
//         display_frame(frame);
//         // push_brightness();
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//     }
// }
// void scroll_character(int n, int str[n])
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = letter_font[str[i]][row];
//         }
//     }
//     for (int s = 0; s < (num_digits + 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = (s / 8 - 3 + mat);

//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//                 else if (frame_index == -1 && s % 8 != 0)
//                 {
//                     frame[mat][row] = frames[0][row] >> (8 - (s % 8));
//                 }
//             }
//         }

//         // if (update_time_flag_1 == true)
//         // {
//         //     update_time_flag_1 = false;
//         //     return;
//         // }

//         display_frame(frame);
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//     }
// }

// void set_digit_on_display(int display, uint8_t address, uint8_t data)
// {
//     spi_transaction_t t;
//     memset(&t, 0, sizeof(t));
//     uint8_t buffer[4 * 2] = {0};
//     buffer[display * 2] = address;
//     buffer[display * 2 + 1] = data;
//     t.length = 8 * sizeof(buffer);
//     t.tx_buffer = buffer;
//     spi_device_transmit(spi, &t);
// }

// void display_number(int hour, int minute)
// {
//     int hr[2] = {0};
//     int min[2] = {0};
//     hour = hour % 100;
//     minute = minute % 100;
//     for (int i = 1; i >= 0; i--)
//     {
//         hr[i] = hour % 10;
//         hour /= 10;
//     }
//     for (int i = 1; i >= 0; i--)
//     {
//         min[i] = minute % 10;
//         minute /= 10;
//     }
//     if (blink == 1)
//     {
//         for (int display = 0; display < 4; display++)
//         {
//             for (int row = 0; row < 8; row++)
//             {
//                 if (display == 0)
//                 {
//                     set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
//                 }
//                 if (display == 1)
//                 {
//                     if (row == 1 || row == 2 || row == 5 || row == 6)
//                     {
//                         set_digit_on_display(display, row + 1, ((number_font[hr[1]][row] << 0x01) | number_font[10][row]));
//                     }
//                     else
//                     {
//                         set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
//                     }
//                 }
//                 if (display == 3)
//                 {
//                     set_digit_on_display(display, row + 1, number_font[min[1]][row]);
//                 }
//                 if (display == 2)
//                 {
//                     if (row == 1 || row == 2 || row == 5 || row == 6)
//                     {
//                         set_digit_on_display(display, row + 1, ((number_font[min[0]][row] >> 0x01) | number_font[11][row])); // Corrected here
//                     }
//                     else
//                     {
//                         set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01); // Corrected here
//                     }
//                 }
//             }
//         }
//     }
//     if (blink == 0)
//     {
//         for (int display = 0; display < 4; display++)
//         {
//             for (int row = 0; row < 8; row++)
//             {
//                 if (display == 0)
//                 {
//                     if (time_flag_hour == true)
//                     {
//                         set_digit_on_display(display, row + 1, number_font[13][row]);
//                     }
//                     else
//                     {
//                         set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
//                     }
//                     // set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
//                 }
//                 if (display == 1)
//                 {
//                     if (time_flag_hour == true)
//                     {
//                         set_digit_on_display(display, row + 1, number_font[13][row] << 0x01);
//                     }
//                     else
//                     {
//                         set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
//                     }
//                     // set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
//                 }
//                 if (display == 3)
//                 {
//                     if (time_flag_minute == true)
//                     {
//                         set_digit_on_display(display, row + 1, number_font[13][row]);
//                     }
//                     else
//                     {
//                         set_digit_on_display(display, row + 1, number_font[min[1]][row]);
//                     }
//                     // set_digit_on_display(display, row + 1, number_font[min[1]][row]);
//                 }
//                 if (display == 2)
//                 {
//                     if (time_flag_minute == true)
//                     {
//                         set_digit_on_display(display, row + 1, number_font[13][row] >> 0x01);
//                     }
//                     else
//                     {
//                         set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01);
//                     }
//                     // set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01);
//                 }
//             }
//         }
//     }
//     adc = adc1_get_raw(ADC_GPIO);
//     printf("ADC  %d\n", adc);
//     brightness_set(adc);
//     blink = !blink;
// }

// void scroll_number(int str[11])
// {
//     int num_digits = 11;
//     uint8_t frames[num_digits][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = number_font[(uint8_t)str[i]][row];
//         }
//     }
//     for (int s = 0; s < (num_digits + 3) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = s / 8 - 3 + mat;
//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//             }
//         }
//         display_frame(frame);
//         vTaskDelay(50 / portTICK_PERIOD_MS);
//     }
// }

// void scroll_number(int str[11])
// {
//     int num_digits = 11;
//     uint8_t frames[num_digits][8];

//     // Load the frames with the font data for each digit
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = number_font[(uint8_t)str[i]][row];
//         }
//     }

//     for (int s = 0; s < (num_digits + 3) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = (s / 8) - 3 + mat;
//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     if (s % 8 == 0 && mat == 3)
//                     {
//                         frame[mat][row] = frames[frame_index][row];
//                     }
//                     else
//                     {
//                         frame[mat][row] = frames[frame_index][row] << (s % 8);
//                         if (frame_index + 1 < num_digits)
//                         {
//                             frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                         }
//                     }
//                 }
//             }
//         }

//         // Display the current frame
//         display_frame(frame);
//         vTaskDelay(50 / portTICK_PERIOD_MS);
//     }
// }
// void scroll_character(int n, int str[n])
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = letter_font[str[i]][row];
//         }
//     }
//     for (int s = 0; s < (num_digits + 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = s / 8 - 3 + mat;
//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//             }
//         }
//         display_frame(frame);
//         vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
// }

// void scroll_number(int number)
// {
//     char str[2];
//     sprintf(str, "%01d", number);
//     int num_digits = strlen(str);
//     uint8_t frames[num_digits][4][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         int digit = str[i] - '0';
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][0][row] = number_font[digit][row];
//         }
//     }

//  // for (int s = 0; s < num_digits * 8; s++) // Adjust the scrolling range
// {
//     uint8_t frame[4][8] = {0};
//     for (int row = 0; row < 8; row++)
//     {
//         for (int mat = 0; mat < 4; mat++)
//         {
//             int frame_NUM = (s / 8 + mat) % num_digits; // Adjust modulo for num_digits
//             int next_frame = (frame_NUM + 1) % num_digits;
//             frame[mat][row] = frames[frame_NUM][0][row] << (s % 8);

//             if ((s % 8) != 0 && next_frame < num_digits) // Check bounds for next_frame
//             {
//                 frame[mat][row] |= frames[next_frame][0][row] >> (8 - (s % 8));
//             }
//         }
//     }
//     display_frame(frame);
//     vTaskDelay(50 / portTICK_PERIOD_MS);
// }
// }
// void scroll_character(int n, int str[n])
// {
//     int num_digits = n;            // Get the number of digits in the number
//     uint8_t frames[num_digits][8]; // Dynamically size the frames array

//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = letter_font[str[i]][row];
//         }
//     }

//     for (int s = 0; s < (num_digits + 3) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = s / 8 - 3 + mat;
//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//             }
//         }
//         display_frame(frame);
//         vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
// }
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "rtc.h"
#include "max7219.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_adc/adc_continuous.h"

#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK 18
#define PIN_NUM_CS 5

#define DEFAULT_VREF 1100               // Default ADC reference voltage in mV
#define ADC_WIDTH_BIT ADC_WIDTH_BIT_12  // ADC bit width (9, 10, 11, or 12)
#define ADC_ATTENUATION ADC_ATTEN_DB_12 // ADC attenuation (0db, 2.5db, 6db, 11db)
#define PORT_TICK_PERIOD_MS 1000        // Tick period in milliseconds
#define ADC_GPIO ADC1_CHANNEL_5         // ADC channel for GPIO33

volatile bool blink = 0;
volatile bool a = 0;
bool update_time_flag = false;
bool update_time_flag_1 = false;
bool time_flag_minute = false;
bool time_flag_hour = false;
bool time_flag_date = false;
bool time_flag_month = false;
bool time_flag_year = false;
bool time_flag_day = false;
int adc;
static spi_device_handle_t spi;

// Function to initialize the SPI bus
void spi_init()
{
    spi_bus_config_t buscfg = {
        .miso_io_num = -1,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32 * 4};

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1000000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 7,
        .flags = SPI_DEVICE_HALFDUPLEX};

    ESP_ERROR_CHECK(spi_bus_initialize(VSPI_HOST, &buscfg, 1));
    ESP_ERROR_CHECK(spi_bus_add_device(VSPI_HOST, &devcfg, &spi));
}

void max7219_send_byte_all(uint8_t address, uint8_t data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    uint8_t buffer[4 * 2];

    for (int i = 0; i < 4; i++)
    {
        buffer[i * 2] = address;
        buffer[i * 2 + 1] = data;
    }

    t.length = 8 * sizeof(buffer);
    t.tx_buffer = buffer;
    spi_device_transmit(spi, &t);
}

void max7219_init_all()
{
    max7219_send_byte_all(0x0C, 0x01); // Normal operation mode
    max7219_send_byte_all(0x09, 0x00); // No decode mode for digits
    max7219_send_byte_all(0x0B, 0x07); // Display digits 0-7
    max7219_send_byte_all(0x0A, 0x0F); // Maximum intensity
    max7219_send_byte_all(0x0F, 0x00); // Normal display test mode
}

// Bit patterns for numbers 0-9 and dot
const uint8_t number_font[14][8] = {
    {0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c}, // 0
    {0x08, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7e, 0x7e}, // 1
    {0x3c, 0x7e, 0x46, 0x0c, 0x18, 0x30, 0x7e, 0x7e}, // 2
    {0x7e, 0x7e, 0x04, 0x18, 0x1c, 0x06, 0x7e, 0x7c}, // 3
    {0x04, 0x0c, 0x1c, 0x2c, 0x4c, 0x7e, 0x0c, 0x0c}, // 4
    {0x7e, 0x7e, 0x40, 0x7c, 0x06, 0x06, 0x66, 0x3c}, // 5
    {0x3c, 0x7e, 0x40, 0x7c, 0x66, 0x66, 0x66, 0x3c}, // 6
    {0x7e, 0x7e, 0x46, 0x0c, 0x18, 0x18, 0x18, 0x18}, // 7
    {0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x66, 0x3c}, // 8
    {0x3c, 0x66, 0x66, 0x7e, 0x06, 0x06, 0x46, 0x3c}, // 9
    {0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00}, // dot1
    {0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00},
    {0x06, 0x06, 0x0e, 0x1c, 0x38, 0x70, 0x60, 0x60},  // slash
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}; // blank

const uint8_t letter_font[27][8] = {
    {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66},  // A1
    {0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0x7C},  // B2
    {0x3C, 0x66, 0x60, 0x60, 0x60, 0x60, 0x66, 0x3C},  // C3
    {0x78, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x6C, 0x78},  // D4
    {0x7e, 0x60, 0x60, 0x7c, 0x7c, 0x60, 0x60, 0x7e},  // E5
    {0x7E, 0x60, 0x60, 0x7C, 0x7C, 0x60, 0x60, 0x60},  // F6
    {0x3C, 0x66, 0x60, 0x60, 0x6E, 0x66, 0x66, 0x3E},  // G7
    {0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66},  // H8
    {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C},  // I9
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x6C, 0x6C, 0x38},  // J10
    {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x66},  // K11
    {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x7e},  // L2
    {0x42, 0x66, 0x7e, 0x5a, 0x5a, 0x42, 0x42, 0x42},  // M3
    {0x46, 0x66, 0x66, 0x76, 0x7e, 0x6e, 0x66, 0x62},  // N4
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C},  // O5
    {0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60},  // P6
    {0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x1e},  // Q7
    {0x7C, 0x66, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66},  // R8
    {0x3C, 0x66, 0x60, 0x3C, 0x06, 0x06, 0x66, 0x3C},  // S9
    {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},  // T20
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C},  // U1
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18},  // V2
    {0x42, 0x42, 0x42, 0x5a, 0x5a, 0x7e, 0x7e, 0x42},  // W3
    {0x42, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x66, 0x42},  // X4
    {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18},  // Y5
    {0x7e, 0x7e, 0x06, 0x0c, 0x18, 0x30, 0x7e, 0x7e},  // Z6
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}; // blank

// sunday 19,21,14,4,1,25
// monday 13,15,14,4,1,25
// tuesday 20,21,5,19,4,1,25
// wednesday 23,5,4,14,5,19,4,1,25
// thursday 10,8,21,18,19,4,1,25
// friday 6,18,9,4,1,25
// saturday 19,1,20,21,18,4,1,25
void brightness_set(int adc)
{
    if (adc <= 273)
    {
        max7219_send_byte_all(0x0A, 0x01);
    }
    if (adc > 273 && adc <= 546)
    {
        max7219_send_byte_all(0x0A, 0x02);
    }
    if (adc > 546 && adc <= 819)
    {
        max7219_send_byte_all(0x0A, 0x03);
    }
    if (adc > 819 && adc <= 1092)
    {
        max7219_send_byte_all(0x0A, 0x04);
    }
    if (adc > 1092 && adc <= 1365)
    {
        max7219_send_byte_all(0x0A, 0x05);
    }
    if (adc > 1365 && adc <= 1688)
    {
        max7219_send_byte_all(0x0A, 0x06);
    }
    if (adc > 1688 && adc <= 1911)
    {
        max7219_send_byte_all(0x0A, 0x07);
    }
    if (adc > 1911 && adc <= 2184)
    {
        max7219_send_byte_all(0x0A, 0x08);
    }
    if (adc > 2184 && adc <= 2457)
    {
        max7219_send_byte_all(0x0A, 0x09);
    }
    if (adc > 2457 && adc <= 2730)
    {
        max7219_send_byte_all(0x0A, 0x0A);
    }
    if (adc > 2730 && adc <= 3003)
    {
        max7219_send_byte_all(0x0A, 0x0B);
    }
    if (adc > 3003 && adc <= 3276)
    {
        max7219_send_byte_all(0x0A, 0x0C);
    }
    if (adc > 3276 && adc <= 3549)
    {
        max7219_send_byte_all(0x0A, 0x0D);
    }
    if (adc > 3549 && adc <= 3822)
    {
        max7219_send_byte_all(0x0A, 0x0E);
    }
    if (adc > 3822 && adc <= 4095)
    {
        max7219_send_byte_all(0x0A, 0x0F);
    }
}

void set_column_on_display(int display, uint8_t row, uint8_t data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    uint8_t buffer[4 * 2] = {0};
    buffer[display * 2] = row + 1;
    buffer[display * 2 + 1] = data;

    t.length = 8 * sizeof(buffer);
    t.tx_buffer = buffer;
    spi_device_transmit(spi, &t);
}

void display_frame(uint8_t frame[4][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int display = 0; display < 4; display++)
        {
            set_column_on_display(display, row, frame[display][row]);
        }
    }
}

// void scroll_number(int n, int str[n])
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][4][8];

//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             if (i == 1 || i == 0)
//             {
//                 frames[i][0][row] = number_font[(uint8_t)str[i]][row] << 1;
//             }

//             if (i == 2 || i == 3)
//             {
//                 frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 1;
//             }
//             else
//             {
//                 frames[i][0][row] = number_font[(uint8_t)str[i]][row];
//             }
//         }
//     }

//     for (int s = 0; s < (num_digits - 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {0};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 if (s >= 8 && s <= 15)
//                 {
//                     for (int i = 0; i < num_digits; i++)
//                     {
//                         for (int row = 0; row < 8; row++)
//                         {
//                             if (i == 1)
//                             {
//                                 frames[i][0][row] = ((number_font[(uint8_t)str[i]][row] << 0x01) | number_font[10][row]);
//                             }
//                             if (i == 0)
//                             {
//                                 frames[i][0][row] = (number_font[(uint8_t)str[i]][row] << 0x01);
//                             }
//                             if (i == 2)
//                             {
//                                 frames[i][0][row] = ((number_font[(uint8_t)str[i]][row] >> 0x01) | number_font[11][row]);
//                             }
//                             if (i == 3)
//                             {
//                                 frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 0x01;
//                             }
//                         }
//                     }
//                 }
//                 int frame_NUM = (s / 8 + mat) % num_digits;
//                 int next_frame = (frame_NUM + 1) % num_digits;
//                 frame[mat][row] = frames[frame_NUM][0][row] << (s % 8);

//                 if ((s % 8) != 0 && next_frame < num_digits)
//                 {
//                     frame[mat][row] |= frames[next_frame][0][row] >> (8 - (s % 8));
//                 }
//             }
//         }

//         if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
//         {
//             update_time_flag = false;
//             return;
//         }
//         adc = adc1_get_raw(ADC_GPIO);
//         printf("ADC  %d\n", adc);
//         brightness_set(adc);
//         display_frame(frame);
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//     }
// }

// void scroll_character(int n, int str[n])
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = letter_font[str[i]][row];
//         }
//     }
//     for (int s = 0; s < (num_digits + 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = (s / 8 - 3 + mat);

//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//                 else if (frame_index == -1 && s % 8 != 0)
//                 {
//                     frame[mat][row] = frames[0][row] >> (8 - (s % 8));
//                 }
//             }
//         }

//         if (update_time_flag_1 == true)
//         {
//             update_time_flag_1 = false;
//             return;
//         }
//         adc = adc1_get_raw(ADC_GPIO);
//         printf("ADC  %d\n", adc);
//         brightness_set(adc);
//         display_frame(frame);
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//     }
// }

void scroll_number(int n, int str[n])
{
    int num_digits = n;
    uint8_t frames[num_digits][4][8];

    for (int i = 0; i < num_digits; i++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (i == 1 || i == 0)
            {
                frames[i][0][row] = number_font[(uint8_t)str[i]][row] << 1;
            }

            if (i == 2 || i == 3)
            {
                frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 1;
            }
            else
            {
                frames[i][0][row] = number_font[(uint8_t)str[i]][row];
            }
        }
    }

    for (int s = 0; s < (num_digits - 4) * 8; s++)
    {
        uint8_t frame[4][8] = {0};
        for (int row = 0; row < 8; row++)
        {
            for (int mat = 0; mat < 4; mat++)
            {
                if (s >= 8 && s <= 15)
                {
                    for (int i = 0; i < num_digits; i++)
                    {
                        for (int row = 0; row < 8; row++)
                        {
                            if (i == 1)
                            {
                                frames[i][0][row] = ((number_font[(uint8_t)str[i]][row] << 0x01) | number_font[10][row]);
                            }
                            if (i == 0)
                            {
                                frames[i][0][row] = (number_font[(uint8_t)str[i]][row] << 0x01);
                            }
                            if (i == 2)
                            {
                                frames[i][0][row] = ((number_font[(uint8_t)str[i]][row] >> 0x01) | number_font[11][row]);
                            }
                            if (i == 3)
                            {
                                frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 0x01;
                            }
                        }
                    }
                }
                int frame_NUM = (s / 8 + mat) % num_digits;
                int next_frame = (frame_NUM + 1) % num_digits;
                frame[mat][row] = frames[frame_NUM][0][row] << (s % 8);

                if ((s % 8) != 0 && next_frame < num_digits)
                {
                    frame[mat][row] |= frames[next_frame][0][row] >> (8 - (s % 8));
                }
            }
        }

        if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
        {
            update_time_flag = false;
            return;
        }
        adc = adc1_get_raw(ADC_GPIO);
        printf("ADC  %d\n", adc);
        brightness_set(adc);
        display_frame(frame);
        vTaskDelay(70 / portTICK_PERIOD_MS);
    }
}

void scroll_character(int n, int str[n])
{
    int num_digits = n - 23;
    uint8_t frames[num_digits][8];
    for (int i = 0; i < 23; i++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (i == 1 || i == 0)
            {
                frames[i][0][row] = number_font[(uint8_t)str[i]][row] << 1;
            }

            if (i == 2 || i == 3)
            {
                frames[i][0][row] = number_font[(uint8_t)str[i]][row] >> 1;
            }
            else
            {
                frames[i][0][row] = number_font[(uint8_t)str[i]][row];
            }
        }
    }
    for (int i = 23; i < n; i++)
    {
        for (int row = 0; row < 8; row++)
        {
            frames[i][row] = letter_font[str[i]][row];
        }
    }
    for (int s = 0; s < (n + 4) * 8; s++)
    {
        uint8_t frame[4][8] = {{0}};
        for (int row = 0; row < 8; row++)
        {
            for (int mat = 0; mat < 4; mat++)
            {
                int frame_index = (s / 8 - 3 + mat);

                if (frame_index >= 0 && frame_index < n)
                {
                    frame[mat][row] = frames[frame_index][row] << (s % 8);
                    if ((s % 8) != 0 && frame_index + 1 < n)
                    {
                        frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
                    }
                }
                else if (frame_index == -1 && s % 8 != 0)
                {
                    frame[mat][row] = frames[0][row] >> (8 - (s % 8));
                }
            }
        }

        if (update_time_flag_1 == true)
        {
            update_time_flag_1 = false;
            return;
        }
        adc = adc1_get_raw(ADC_GPIO);
        printf("ADC  %d\n", adc);
        brightness_set(adc);
        display_frame(frame);
        vTaskDelay(70 / portTICK_PERIOD_MS);
    }
}

void set_digit_on_display(int display, uint8_t address, uint8_t data)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    uint8_t buffer[4 * 2] = {0};
    buffer[display * 2] = address;
    buffer[display * 2 + 1] = data;
    t.length = 8 * sizeof(buffer);
    t.tx_buffer = buffer;
    spi_device_transmit(spi, &t);
}

void display_number(int hour, int minute)
{
    int hr[2] = {0};
    int min[2] = {0};
    hour = hour % 100;
    minute = minute % 100;
    for (int i = 1; i >= 0; i--)
    {
        hr[i] = hour % 10;
        hour /= 10;
    }
    for (int i = 1; i >= 0; i--)
    {
        min[i] = minute % 10;
        minute /= 10;
    }
    if (blink == 1)
    {
        for (int display = 0; display < 4; display++)
        {
            for (int row = 0; row < 8; row++)
            {
                if (display == 0)
                {
                    set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
                }
                if (display == 1)
                {
                    if (row == 1 || row == 2 || row == 5 || row == 6)
                    {
                        set_digit_on_display(display, row + 1, ((number_font[hr[1]][row] << 0x01) | number_font[10][row]));
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
                    }
                }
                if (display == 3)
                {
                    set_digit_on_display(display, row + 1, number_font[min[1]][row]);
                }
                if (display == 2)
                {
                    if (row == 1 || row == 2 || row == 5 || row == 6)
                    {
                        set_digit_on_display(display, row + 1, ((number_font[min[0]][row] >> 0x01) | number_font[11][row])); // Corrected here
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01); // Corrected here
                    }
                }
            }
        }
    }
    if (blink == 0)
    {
        for (int display = 0; display < 4; display++)
        {
            for (int row = 0; row < 8; row++)
            {
                if (display == 0)
                {
                    if (time_flag_hour == true)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row]);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
                    }
                    // set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
                }
                if (display == 1)
                {
                    if (time_flag_hour == true)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row] << 0x01);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
                    }
                    // set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
                }
                if (display == 3)
                {
                    if (time_flag_minute == true)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row]);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[min[1]][row]);
                    }
                    // set_digit_on_display(display, row + 1, number_font[min[1]][row]);
                }
                if (display == 2)
                {
                    if (time_flag_minute == true)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row] >> 0x01);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01);
                    }
                    // set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01);
                }
            }
        }
    }
    if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
    {
        return;
    }
    adc = adc1_get_raw(ADC_GPIO);
    printf("ADC  %d\n", adc);
    brightness_set(adc);
    blink = !blink;
    //  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
void number_set_display(int hour, int minute, int n)
{
    int hr[2] = {0};
    int min[2] = {0};
    hour = hour % 100;
    minute = minute % 100;
    for (int i = 1; i >= 0; i--)
    {
        hr[i] = hour % 10;
        hour /= 10;
    }
    for (int i = 1; i >= 0; i--)
    {
        min[i] = minute % 10;
        minute /= 10;
    }
    if (n == 1)
    {
        for (int display = 0; display < 4; display++)
        {
            for (int row = 0; row < 8; row++)
            {
                if (display == 0)
                {
                    if (a == 1)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row]);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
                    }
                }
                if (display == 1)
                {
                    if (a == 1)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row] << 0x01);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
                    }
                }
                if (display == 3)
                {
                    set_digit_on_display(display, row + 1, number_font[min[1]][row]);
                }
                if (display == 2)
                {
                    set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01);
                }
            }
        }
    }
    if (n == 2)
    {
        for (int display = 0; display < 4; display++)
        {
            for (int row = 0; row < 8; row++)
            {
                if (display == 0)
                {
                    set_digit_on_display(display, row + 1, number_font[hr[0]][row]);
                }
                if (display == 1)
                {
                    set_digit_on_display(display, row + 1, number_font[hr[1]][row] << 0x01);
                }
                if (display == 3)
                {
                    if (a == 1)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row]);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[min[1]][row]);
                    }
                }
                if (display == 2)
                {
                    if (a == 1)
                    {
                        set_digit_on_display(display, row + 1, number_font[13][row] >> 0x01);
                    }
                    else
                    {
                        set_digit_on_display(display, row + 1, number_font[min[0]][row] >> 0x01);
                    }
                }
            }
        }
    }
    a = !a;
    if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
    {
        return;
    }
    adc = adc1_get_raw(ADC_GPIO);
    printf("ADC  %d\n", adc);
    brightness_set(adc);
    blink = !blink;
    //  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
void date_set_display(int str[4])
{

    for (int display = 0; display < 4; display++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (display == 0)
            {
                set_digit_on_display(display, row + 1, letter_font[str[0]][row]);
            }
            if (display == 1)
            {
                set_digit_on_display(display, row + 1, letter_font[str[1]][row]);
            }
            if (display == 2)
            {
                set_digit_on_display(display, row + 1, number_font[str[2]][row]);
            }
            if (display == 3)
            {
                set_digit_on_display(display, row + 1, number_font[str[3]][row]);
            }
        }
    }
    if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
    {
        return;
    }
    adc = adc1_get_raw(ADC_GPIO);
    printf("ADC  %d\n", adc);
    brightness_set(adc);
}
void day_set_display(int str[4])
{

    for (int display = 0; display < 4; display++)
    {
        for (int row = 0; row < 8; row++)
        {
            if (display == 0)
            {
                set_digit_on_display(display, row + 1, letter_font[str[0]][row]);
            }
            if (display == 1)
            {
                set_digit_on_display(display, row + 1, letter_font[str[1]][row]);
            }
            if (display == 2)
            {
                set_digit_on_display(display, row + 1, letter_font[str[2]][row]);
            }
            if (display == 3)
            {
                set_digit_on_display(display, row + 1, letter_font[26][row]);
            }
        }
    }
    if (update_time_flag == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
    {
        return;
    }
    adc = adc1_get_raw(ADC_GPIO);
    printf("ADC  %d\n", adc);
    brightness_set(adc);
}

// void scroll_character(int n, int str[n])
// {
//     int num_digits = n;
//     uint8_t frames[num_digits][8];
//     for (int i = 0; i < num_digits; i++)
//     {
//         for (int row = 0; row < 8; row++)
//         {
//             frames[i][row] = letter_font[str[i]][row];
//         }
//     }
//     for (int s = 0; s < (num_digits + 4) * 8; s++)
//     {
//         uint8_t frame[4][8] = {{0}};
//         for (int row = 0; row < 8; row++)
//         {
//             for (int mat = 0; mat < 4; mat++)
//             {
//                 int frame_index = s / 8 - 3 + mat;
//                 if (frame_index >= 0 && frame_index < num_digits)
//                 {
//                     frame[mat][row] = frames[frame_index][row] << (s % 8);
//                     if ((s % 8) != 0 && frame_index + 1 < num_digits)
//                     {
//                         frame[mat][row] |= frames[frame_index + 1][row] >> (8 - (s % 8));
//                     }
//                 }
//                 else if (frame_index == -1)
//                 {
//                     frame[mat][row] = 0x00 << (s % 8);
//                     if ((s % 8) != 0 && num_digits > 0)
//                     {
//                         frame[mat][row] |= frames[0][row] >> (8 - (s % 8));
//                     }
//                 }
//             }
//         }
//         // if (update_time_flag_1 == true || time_flag_minute == true || time_flag_hour == true || time_flag_date == true || time_flag_month == true || time_flag_year == true || time_flag_day == true)
//         // {
//         //     update_time_flag_1 = false;
//         //     return;
//         // }
//         adc = adc1_get_raw(ADC_GPIO);
//         printf("ADC  %d\n", adc);
//         brightness_set(adc);
//         display_frame(frame);
//         vTaskDelay(70 / portTICK_PERIOD_MS);
//     }
// }