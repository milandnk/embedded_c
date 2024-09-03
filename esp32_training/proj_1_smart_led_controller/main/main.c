// // #include <stdio.h>
// // #include <stdio.h>
// // #include <string.h>
// // #include "freertos/FreeRTOS.h"
// // #include "freertos/task.h"
// // #include "esp_log.h"
// // #include "esp_event.h"
// // #include "nvs_flash.h"
// // #include "esp_netif.h"
// // #include "esp_wifi.h"
// // #include "esp_https_server.h"
// // #include "sdkconfig.h"
// // #include "max7219.h"
// // #include "rtc.h" //rtc

// // static const char *TAG = "main"; // A constant character pointer used for logging.

// // struct async_resp_arg // structure for asynchronous responce arg
// // {
// //     httpd_handle_t hd;
// //     int fd;
// // };
// // // Define the maximum number of clients that can connect to the AP
// // #define MAX_STA_CONN 4 // A macro defining the maximum number of client connections allowed to the Wi-Fi access point (AP).

// // static esp_err_t ws_handler(httpd_req_t *req)
// // {
// //     if (req->method == HTTP_GET) // Checks if the request method is a GET request.
// //     {
// //         ESP_LOGI(TAG, "Handshake done, the new connection was opened"); // Logs a message indicating that the WebSocket handshake is complete.
// //         return ESP_OK;                                                  // Returns an OK status, ending the function if it was a GET request.
// //     }
// //     httpd_ws_frame_t ws_pkt;                      // Declares a variable to hold the WebSocket frame.
// //     uint8_t *buf = NULL;                          // Declares a buffer pointer and initializes it to NULL.
// //     memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t)); // Initializes the ws_pkt structure to zero.

// //     esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0); // Receives the WebSocket frame and gets its length.
// //     if (ret != ESP_OK)                                    // Checks if the frame reception failed.
// //     {
// //         ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
// //         return ret;
// //     }
// //     ESP_LOGI(TAG, "frame len is %d", ws_pkt.len); // Logs the frame length.
// //     if (ws_pkt.len)                               // Logs the frame length.
// //     {
// //         buf = calloc(1, ws_pkt.len + 1); // Logs the frame length.
// //         if (buf == NULL)                 // Checks if memory allocation failed.
// //         {
// //             ESP_LOGE(TAG, "Failed to calloc memory for buf");
// //             return ESP_ERR_NO_MEM; // Returns a memory allocation error
// //         }
// //         ws_pkt.payload = buf;                                // Assigns the buffer to the payload
// //         ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len); // Receives the WebSocket frame with the actual payload.
// //         if (ret != ESP_OK)                                   // Checks if receiving the frame failed.
// //         {
// //             ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
// //             free(buf);  // free buffer
// //             return ret; // Returns the error code.
// //         }
// //     }

// //     if (ws_pkt.type == HTTPD_WS_TYPE_TEXT) // Checks if the frame type is text.
// //     {
// //         ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload); // logs

// //         // Assuming the message format is "SET_TIME hh:mm:ss dd/mm/yyyy"
// //         int hours, minutes, seconds, day, month, year;
// //         if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %2d/%2d/%4d", &hours, &minutes, &seconds, &day, &month, &year) == 6) // where to string read ,formate ,where store
// //         {
// //             // Set the new time to the RTC module
// //             set_rtc_time(seconds, minutes, hours, day, day, month, year - 2000);                                            // set rtc time
// //             ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d", hours, minutes, seconds, day, month, year); // logs

// //             // Send an acknowledgment back to the client
// //             const char *ack = "Time set successfully"; // ack
// //             ws_pkt.payload = (uint8_t *)ack;           // ack of payload(data)
// //             ws_pkt.len = strlen(ack);                  // ack payload len
// //             ret = httpd_ws_send_frame(req, &ws_pkt);   // Sends the WebSocket frame with the acknowledgment.
// //             if (ret != ESP_OK)                         // Checks if sending the frame failed.
// //             {
// //                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
// //             }
// //         }
// //         //     if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d:%2d %2d/%2d/%4d", &hours, &minutes, &seconds, &day, &month, &year) == 6) // where to string read ,formate ,where store
// //         //     {
// //         //         // Set the new time to the RTC module
// //         //         set_rtc_alarm(seconds, minutes, hours, day, day, month, year - 2000);                                            // set rtc time
// //         //         ESP_LOGI(TAG, "RTC alarm set to %02d:%02d:%02d, Date: %02d/%02d/%d", hours, minutes, seconds, day, month, year); // logs

// //         //         // Send an acknowledgment back to the client
// //         //         const char *ack = "Alarm set successfully"; // ack
// //         //         ws_pkt.payload = (uint8_t *)ack;           // ack of payload(data)
// //         //         ws_pkt.len = strlen(ack);                  // ack payload len
// //         //         ret = httpd_ws_send_frame(req, &ws_pkt);   // Sends the WebSocket frame with the acknowledgment.
// //         //         if (ret != ESP_OK)                         // Checks if sending the frame failed.
// //         //         {
// //         //             ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
// //         //         }
// //         //     }
// //         //     else
// //         //     {
// //         //         ESP_LOGE(TAG, "Failed to parse time string: %s", ws_pkt.payload); // if failed parsing
// //         //     }
// //         // }
// //         // free(buf); // free buffer
// //         // return ESP_OK;
// //     }

// //     esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd) // ws open when new client connected logs
// //     {
// //         ESP_LOGI(TAG, "New client connected %d", sockfd);
// //         return ESP_OK;
// //     }

// //     void wss_close_fd(httpd_handle_t hd, int sockfd) /// ws open when new client disconnected logs
// //     {
// //         ESP_LOGI(TAG, "Client disconnected %d", sockfd);
// //     }

// //     httpd_uri_t ws = {
// //         // uri  that allows the ESP32 to respond to HTTP requests
// //         .uri = "/ws",          // end point ws
// //         .method = HTTP_GET,    // constatnt get from http
// //         .handler = ws_handler, // func name
// //         .is_websocket = true,
// //         .supported_subprotocol = NULL,
// //     };

// //     static httpd_handle_t start_wss_echo_server(void) // start web socket server
// //     {
// //         httpd_handle_t server = NULL;                   // Declares a variable for the server handle, initializing it to NULL.
// //         httpd_config_t config = HTTPD_DEFAULT_CONFIG(); // Declares and initializes a configuration structure.
// //         config.open_fn = wss_open_fd;                   // Sets the function to be called when a new connection is opened.
// //         config.close_fn = wss_close_fd;                 // closed

// //         esp_err_t ret = httpd_start(&server, &config); // Starts the HTTP server with the given configuration.
// //         if (ret != ESP_OK)
// //         {
// //             ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
// //             return NULL; // Logs an error message if the server fails to start.
// //         }

// //         ret = httpd_register_uri_handler(server, &ws); // Registers the URI handler.
// //         if (ret != ESP_OK)
// //         {
// //             ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
// //             httpd_stop(server); // Logs an error message if registration fails
// //             return NULL;
// //         }

// //         return server;
// //     }

// //     static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) // Function definition for handling disconnect events.
// //     {
// //         httpd_handle_t *server = (httpd_handle_t *)arg;
// //         if (*server)
// //         {
// //             httpd_stop(*server);
// //             *server = NULL;
// //         }
// //     }

// //     static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) //  Function definition for handling connect events.
// //     {
// //         httpd_handle_t *server = (httpd_handle_t *)arg;
// //         if (*server == NULL)
// //         {
// //             *server = start_wss_echo_server();
// //         }
// //     }

// //     void app_main(void)
// //     {

// //         // // minutes[2];
// //         // // seconds[2];
// //         static httpd_handle_t server = NULL; // server var as null
// //         esp_err_t ret = nvs_flash_init();    // The type of the variable, which will hold the return code from the nvs_flash_init function.
// //         if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
// //         {
// //             ESP_ERROR_CHECK(nvs_flash_erase()); // Erase the NVS flash and check for errors.
// //             ret = nvs_flash_init();
// //         }
// //         ESP_ERROR_CHECK(ret);

// //         ESP_ERROR_CHECK(esp_netif_init());
// //         ESP_ERROR_CHECK(esp_event_loop_create_default()); // Create the default event loop and check for errors.
// //         esp_netif_create_default_wifi_ap();               // create a default WiFi access point interface.

// //         wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
// //         ESP_ERROR_CHECK(esp_wifi_init(&cfg));

// //         esp_event_handler_instance_t instance_any_id;
// //         esp_event_handler_instance_t instance_got_ip;
// //         ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &disconnect_handler, &server, &instance_any_id));
// //         ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server, &instance_got_ip));

// //         wifi_config_t wifi_config = {
// //             .ap = {
// //                 .ssid = "ESP32-Access-Point",
// //                 .ssid_len = strlen("ESP32-Access-Point"),
// //                 .password = "password",
// //                 .max_connection = MAX_STA_CONN,
// //                 .authmode = WIFI_AUTH_WPA_WPA2_PSK,
// //             },
// //         };
// //         if (strlen("password") == 0)
// //         {
// //             wifi_config.ap.authmode = WIFI_AUTH_OPEN;
// //         }

// //         ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
// //         ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
// //         ESP_ERROR_CHECK(esp_wifi_start());

// //         ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", "ESP32-Access-Point", "password");

// //         i2c_master_init();
// //         // Set initial RTC time (Example: 12:30:45 on 21st May 2024)
// //         // set_rtc_time(45, 30, 12, 3, 21, 5, 24);
// //         // get_rtc_time();
// //         server = start_wss_echo_server();
// //         // int i =0;
// //         // while (1)
// //         // {
// //         //     get_rtc_time();
// //         //     display_number(2000);
// //         //     vTaskDelay(pdMS_TO_TICKS(1000));
// //         //     //    i++;
// //         // }
// //         spi_init();
// //         max7219_init_all();
// //         for (int i = 0; i < 10000; i++)
// //         {
// //             int hour, minute;
// //             get_rtc_time(&hour, &minute);
// //             display_number(hour, minute);
// //             vTaskDelay(1000 / portTICK_PERIOD_MS); // Adjust delay as needed
// //             alarm_task();
// //         }
// //     }
// // }

// /////////////////////////only for web,clock,rtc

// // #include <stdio.h>
// // #include <stdio.h>
// // #include <string.h>
// // #include "freertos/FreeRTOS.h"
// // #include "freertos/task.h"
// // #include "esp_log.h"
// // #include "esp_event.h"
// // #include "nvs_flash.h"
// // #include "esp_netif.h"
// // #include "esp_wifi.h"
// // #include "esp_https_server.h"
// // #include "sdkconfig.h"
// // #include "max7219.h"
// // #include "rtc.h" //rtc

// // static const char *TAG = "main"; // A constant character pointer used for logging.

// // struct async_resp_arg // structure for asynchronous responce arg
// // {
// //     httpd_handle_t hd;
// //     int fd;
// // };
// // // Define the maximum number of clients that can connect to the AP
// // #define MAX_STA_CONN 4 // A macro defining the maximum number of client connections allowed to the Wi-Fi access point (AP).

// // static esp_err_t ws_handler(httpd_req_t *req)
// // {
// //     if (req->method == HTTP_GET) // Checks if the request method is a GET request.
// //     {
// //         ESP_LOGI(TAG, "Handshake done, the new connection was opened"); // Logs a message indicating that the WebSocket handshake is complete.
// //         return ESP_OK;                                                  // Returns an OK status, ending the function if it was a GET request.
// //     }
// //     httpd_ws_frame_t ws_pkt;                      // Declares a variable to hold the WebSocket frame.
// //     uint8_t *buf = NULL;                          // Declares a buffer pointer and initializes it to NULL.
// //     memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t)); // Initializes the ws_pkt structure to zero.

// //     esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0); // Receives the WebSocket frame and gets its length.
// //     if (ret != ESP_OK)                                    // Checks if the frame reception failed.
// //     {
// //         ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
// //         return ret;
// //     }
// //     ESP_LOGI(TAG, "frame len is %d", ws_pkt.len); // Logs the frame length.
// //     if (ws_pkt.len)                               // Logs the frame length.
// //     {
// //         buf = calloc(1, ws_pkt.len + 1); // Logs the frame length.
// //         if (buf == NULL)                 // Checks if memory allocation failed.
// //         {
// //             ESP_LOGE(TAG, "Failed to calloc memory for buf");
// //             return ESP_ERR_NO_MEM; // Returns a memory allocation error
// //         }
// //         ws_pkt.payload = buf;                                // Assigns the buffer to the payload
// //         ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len); // Receives the WebSocket frame with the actual payload.
// //         if (ret != ESP_OK)                                   // Checks if receiving the frame failed.
// //         {
// //             ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
// //             free(buf);  // free buffer
// //             return ret; // Returns the error code.
// //         }
// //     }

// //     if (ws_pkt.type == HTTPD_WS_TYPE_TEXT) // Checks if the frame type is text.
// //     {
// //         ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload); // logs

// //         // Assuming the message format is "SET_TIME hh:mm:ss dd/mm/yyyy"
// //         int hours, minutes, seconds, day, month, year;
// //         if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %2d/%2d/%4d", &hours, &minutes, &seconds, &day, &month, &year) == 6) // where to string read ,formate ,where store
// //         {
// //             // Set the new time to the RTC module
// //             set_rtc_time(seconds, minutes, hours, day, day, month, year - 2000);                                            // set rtc time
// //             ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d", hours, minutes, seconds, day, month, year); // logs

// //             // Send an acknowledgment back to the client
// //             const char *ack = "Time set successfully"; // ack
// //             ws_pkt.payload = (uint8_t *)ack;           // ack of payload(data)
// //             ws_pkt.len = strlen(ack);                  // ack payload len
// //             ret = httpd_ws_send_frame(req, &ws_pkt);   // Sends the WebSocket frame with the acknowledgment.
// //             if (ret != ESP_OK)                         // Checks if sending the frame failed.
// //             {
// //                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
// //             }
// //         }
// //         int alarm_hours, alarm_minutes, alarm_seconds;
// //         if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d:%2d", &alarm_hours, &alarm_minutes, &alarm_seconds) == 3)
// //         {
// //             set_rtc_alarm(alarm_seconds, alarm_minutes, alarm_hours, 0, 0, 0);
// //             const char *ack = "Alarm set successfully";
// //             ws_pkt.payload = (uint8_t *)ack;
// //             ws_pkt.len = strlen(ack);
// //             ret = httpd_ws_send_frame(req, &ws_pkt);
// //             if (ret != ESP_OK)
// //             {
// //                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
// //             }
// //             else
// //             {
// //                 ESP_LOGE(TAG, "Failed to parse time string: %s", ws_pkt.payload); // if failed parsing
// //             }
// //             free(buf); // free buffer
// //             return ESP_OK;
// //         }
// //         return ESP_FAIL; // Return failure if packet type is not text
// //     }
// // }
// // static esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd) // ws open when new client connected logs
// // {
// //     ESP_LOGI(TAG, "New client connected %d", sockfd);
// //     return ESP_OK;
// // }

// // static void wss_close_fd(httpd_handle_t hd, int sockfd) /// ws open when new client disconnected logs
// // {
// //     ESP_LOGI(TAG, "Client disconnected %d", sockfd);
// // }

// // static httpd_handle_t start_wss_echo_server(void) // start web socket server
// // {
// //     httpd_handle_t server = NULL;                   // Declares a variable for the server handle, initializing it to NULL.
// //     httpd_config_t config = HTTPD_DEFAULT_CONFIG(); // Declares and initializes a configuration structure.
// //     config.open_fn = wss_open_fd;                   // Sets the function to be called when a new connection is opened.
// //     config.close_fn = wss_close_fd;                 // closed

// //     esp_err_t ret = httpd_start(&server, &config); // Starts the HTTP server with the given configuration.
// //     if (ret != ESP_OK)
// //     {
// //         ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
// //         return NULL; // Logs an error message if the server fails to start.
// //     }

// //     httpd_uri_t ws = {
// //         .uri = "/ws",          // end point ws
// //         .method = HTTP_GET,    // constatnt get from http
// //         .handler = ws_handler, // func name
// //         .is_websocket = true,
// //         .supported_subprotocol = NULL,
// //     };

// //     ret = httpd_register_uri_handler(server, &ws); // Registers the URI handler.
// //     if (ret != ESP_OK)
// //     {
// //         ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
// //         httpd_stop(server); // Logs an error message if registration fails
// //         return NULL;
// //     }

// //     return server;
// // }

// // static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) // Function definition for handling disconnect events.
// // {
// //     httpd_handle_t *server = (httpd_handle_t *)arg;
// //     if (*server)
// //     {
// //         httpd_stop(*server);
// //         *server = NULL;
// //     }
// // }

// // static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) //  Function definition for handling connect events.
// // {
// //     httpd_handle_t *server = (httpd_handle_t *)arg;
// //     if (*server == NULL)
// //     {
// //         *server = start_wss_echo_server();
// //     }
// // }

// // void app_main(void)
// // {
// //     static httpd_handle_t server = NULL; // server var as null
// //     esp_err_t ret = nvs_flash_init();    // The type of the variable, which will hold the return code from the nvs_flash_init function.
// //     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
// //     {
// //         ESP_ERROR_CHECK(nvs_flash_erase()); // Erase the NVS flash and check for errors.
// //         ret = nvs_flash_init();
// //     }
// //     ESP_ERROR_CHECK(ret);

// //     ESP_ERROR_CHECK(esp_netif_init());
// //     ESP_ERROR_CHECK(esp_event_loop_create_default()); // Create the default event loop and check for errors.
// //     esp_netif_create_default_wifi_ap();               // create a default WiFi access point interface.

// //     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
// //     ESP_ERROR_CHECK(esp_wifi_init(&cfg));

// //     esp_event_handler_instance_t instance_any_id;
// //     esp_event_handler_instance_t instance_got_ip;
// //     ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &disconnect_handler, &server, &instance_any_id));
// //     ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server, &instance_got_ip));

// //     wifi_config_t wifi_config = {
// //         .ap = {
// //             .ssid = "ESP32-Access-Point",
// //             .ssid_len = strlen("ESP32-Access-Point"),
// //             .password = "password",
// //             .max_connection = MAX_STA_CONN,
// //             .authmode = WIFI_AUTH_WPA_WPA2_PSK,
// //         },
// //     };
// //     if (strlen("password") == 0)
// //     {
// //         wifi_config.ap.authmode = WIFI_AUTH_OPEN;
// //     }

// //     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
// //     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
// //     ESP_ERROR_CHECK(esp_wifi_start());

// //     ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", "ESP32-Access-Point", "password");

// //     i2c_master_init();
// //     // Set initial RTC time (Example: 12:30:45 on 21st May 2024)
// //     // set_rtc_time(45, 30, 12, 3, 21, 5, 24);
// //     // get_rtc_time();
// //     server = start_wss_echo_server();
// //     spi_init();
// //     max7219_init_all();
// //     for (int i = 0; i < 10000; i++)
// //     {
// //         int hour, minute;
// //         get_rtc_time(&hour, &minute);
// //         display_number(hour, minute);
// //         alarm_task();
// //         vTaskDelay(1000 / portTICK_PERIOD_MS); // Adjust delay as needed
// //     }
// // }

// // this is code for // ws time and alarm set and display led on//

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
// #include "rtc.h"
// #include "driver/gpio.h"

// #define ALARM_PIN 14
// static const char *TAG = "main";

// struct async_resp_arg
// {
//     httpd_handle_t hd;
//     int fd;
// };

// #define MAX_STA_CONN 4

// volatile int alarm_hour = -1;
// volatile int alarm_minute = -1;
// volatile int current_hour = -1;
// volatile int current_minute = -1;

// static esp_err_t ws_handler(httpd_req_t *req)
// {
//     if (req->method == HTTP_GET)
//     {
//         ESP_LOGI(TAG, "Handshake done, the new connection was opened");
//         return ESP_OK;
//     }

//     httpd_ws_frame_t ws_pkt;
//     uint8_t *buf = NULL;
//     memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
//     esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);

//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
//         return ret;
//     }

//     if (ws_pkt.len)
//     {
//         buf = calloc(1, ws_pkt.len + 1);
//         if (buf == NULL)
//         {
//             ESP_LOGE(TAG, "Failed to calloc memory for buf");
//             return ESP_ERR_NO_MEM;
//         }
//         ws_pkt.payload = buf;
//         ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);

//         if (ret != ESP_OK)
//         {
//             ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
//             free(buf);
//             return ret;
//         }
//     }

//     if (ws_pkt.type == HTTPD_WS_TYPE_TEXT)
//     {
//         ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload);
//         int hours, minutes, seconds, date, month, year;
//         if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %2d/%2d/%4d", &hours, &minutes, &seconds, &date, &month, &year) == 6)
//         {
//             current_hour = hours;
//             current_minute = minutes;
//             set_rtc_time(seconds, minutes, hours, date, month, year);
//             ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d", hours, minutes, seconds, date, month, year);
//             const char *ack = "Time set successfully";
//             ws_pkt.payload = (uint8_t *)ack;
//             ws_pkt.len = strlen(ack);
//             ret = httpd_ws_send_frame(req, &ws_pkt);

//             if (ret != ESP_OK)
//             {
//                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
//             }
//         }

//         if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d", &hours, &minutes) == 2)
//         {
//             alarm_hour = hours;
//             alarm_minute = minutes;
//             set_rtc_alarm(alarm_hour, alarm_minute);
//             const char *ack = "Alarm set successfully";
//             ws_pkt.payload = (uint8_t *)ack;
//             ws_pkt.len = strlen(ack);
//             ret = httpd_ws_send_frame(req, &ws_pkt);

//             if (ret != ESP_OK)
//             {
//                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
//             }
//         }
//         free(buf);
//         return ESP_OK;
//     }
//     return ESP_FAIL;
// }

// static esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd)
// {
//     ESP_LOGI(TAG, "New client connected %d", sockfd);
//     return ESP_OK;
// }
// static void wss_close_fd(httpd_handle_t hd, int sockfd)
// {
//     ESP_LOGI(TAG, "Client disconnected %d", sockfd);
// }

// static httpd_handle_t start_wss_echo_server(void)
// {
//     httpd_handle_t server = NULL;
//     httpd_config_t config = HTTPD_DEFAULT_CONFIG();
//     config.open_fn = wss_open_fd;
//     config.close_fn = wss_close_fd;
//     esp_err_t ret = httpd_start(&server, &config);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
//         return NULL;
//     }
//     httpd_uri_t ws = {
//         .uri = "/ws",
//         .method = HTTP_GET,
//         .handler = ws_handler,
//         .is_websocket = true,
//         .supported_subprotocol = NULL,
//     };
//     ret = httpd_register_uri_handler(server, &ws);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
//         httpd_stop(server);
//         return NULL;
//     }
//     return server;
// }

// static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// {
//     httpd_handle_t *server = (httpd_handle_t *)arg;
//     if (*server)
//     {
//         httpd_stop(*server);
//         *server = NULL;
//     }
// }

// static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// {
//     httpd_handle_t *server = (httpd_handle_t *)arg;
//     if (*server == NULL)
//     {
//         *server = start_wss_echo_server();
//     }
// }

// void app_main(void)
// {
//     static httpd_handle_t server = NULL;
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
//     {
//         ESP_ERROR_CHECK(nvs_flash_erase());
//         ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(ret);
//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_ap();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
//     ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STADISCONNECTED, &disconnect_handler, &server));
//     wifi_config_t wifi_config = {
//         .ap = {
//             .ssid = "ESP32-Access-Point",
//             .ssid_len = strlen("ESP32-Access-Point"),
//             .password = "password",
//             .max_connection = MAX_STA_CONN,
//             .authmode = WIFI_AUTH_WPA_WPA2_PSK,
//         },
//     };
//     if (strlen("password") == 0)
//     {
//         wifi_config.ap.authmode = WIFI_AUTH_OPEN;
//     }
//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());
//     ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", "ESP32-Access-Point", "password");
//     i2c_master_init();
//     server = start_wss_echo_server();
//     spi_init();
//     max7219_init_all();
//     gpio_config_t io_conf = {
//         .pin_bit_mask = (1ULL << ALARM_PIN),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};
//     gpio_config(&io_conf);

//     gpio_set_direction(ALARM_PIN, GPIO_MODE_OUTPUT);
//     gpio_set_level(ALARM_PIN, 0);
//     while (1)
//     {
//         int current_hour, current_minute;
//         get_rtc_time(&current_hour, &current_minute);
//         display_number(current_hour, current_minute);
//         ESP_LOGI(TAG, "ALARM time  %02d:%02d", alarm_hour, alarm_minute);
//         ESP_LOGI(TAG, "current time  %02d:%02d", current_hour, current_minute);
//         gpio_set_level(ALARM_PIN, 0);
//         if (current_hour == alarm_hour && current_minute == alarm_minute)
//         {
//             gpio_set_level(ALARM_PIN, 1);
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//             gpio_set_level(ALARM_PIN, 0);
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }

// // #include <stdio.h>
// // #include <string.h>
// // #include "freertos/FreeRTOS.h"
// // #include "freertos/task.h"
// // #include "esp_log.h"
// // #include "esp_event.h"
// // #include "nvs_flash.h"
// // #include "esp_netif.h"
// // #include "esp_wifi.h"
// // #include "esp_https_server.h"
// // #include "sdkconfig.h"
// // #include "max7219.h"
// // #include "rtc.h"
// // #include "driver/gpio.h"

// // #define ALARM_PIN 14
// // #define DOWN_PIN 25
// // #define UP_PIN 26
// // #define SET_PIN 27
// // static const char *TAG = "main";

// // struct async_resp_arg
// // {
// //     httpd_handle_t hd;
// //     int fd;
// // };

// // #define MAX_STA_CONN 4

// // volatile int alarm_hour = -1;
// // volatile int alarm_minute = -1;
// // volatile int current_hour = -1;
// // volatile int current_minute = -1;
// // volatile bool i = 0;
// // volatile int set;
// // volatile int data[2];
// // static esp_err_t ws_handler(httpd_req_t *req)
// // {
// //     if (req->method == HTTP_GET)
// //     {
// //         ESP_LOGI(TAG, "Handshake done, the new connection was opened");
// //         return ESP_OK;
// //     }

// //     httpd_ws_frame_t ws_pkt;
// //     uint8_t *buf = NULL;
// //     memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
// //     esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);

// //     if (ret != ESP_OK)
// //     {
// //         ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
// //         return ret;
// //     }

// //     if (ws_pkt.len)
// //     {
// //         buf = calloc(1, ws_pkt.len + 1);
// //         if (buf == NULL)
// //         {
// //             ESP_LOGE(TAG, "Failed to calloc memory for buf");
// //             return ESP_ERR_NO_MEM;
// //         }
// //         ws_pkt.payload = buf;
// //         ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);

// //         if (ret != ESP_OK)
// //         {
// //             ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
// //             free(buf);
// //             return ret;
// //         }
// //     }

// //     if (ws_pkt.type == HTTPD_WS_TYPE_TEXT)
// //     {
// //         ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload);
// //         int hours, minutes, seconds, date, month, year;
// //         if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %2d/%2d/%4d", &hours, &minutes, &seconds, &date, &month, &year) == 6)
// //         {
// //             current_hour = hours;
// //             current_minute = minutes;
// //             set_rtc_time(seconds, minutes, hours, date, month, year);
// //             ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d", hours, minutes, seconds, date, month, year);
// //             const char *ack = "Time set successfully";
// //             ws_pkt.payload = (uint8_t *)ack;
// //             ws_pkt.len = strlen(ack);
// //             ret = httpd_ws_send_frame(req, &ws_pkt);

// //             if (ret != ESP_OK)
// //             {
// //                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
// //             }
// //         }

// //         if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d", &hours, &minutes) == 2)
// //         {
// //             alarm_hour = hours;
// //             alarm_minute = minutes;
// //             set_rtc_alarm(alarm_hour, alarm_minute);
// //             const char *ack = "Alarm set successfully";
// //             ws_pkt.payload = (uint8_t *)ack;
// //             ws_pkt.len = strlen(ack);
// //             ret = httpd_ws_send_frame(req, &ws_pkt);

// //             if (ret != ESP_OK)
// //             {
// //                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
// //             }
// //         }
// //         free(buf);
// //         return ESP_OK;
// //     }
// //     return ESP_FAIL;
// // }

// // static esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd)
// // {
// //     ESP_LOGI(TAG, "New client connected %d", sockfd);
// //     return ESP_OK;
// // }
// // static void wss_close_fd(httpd_handle_t hd, int sockfd)
// // {
// //     ESP_LOGI(TAG, "Client disconnected %d", sockfd);
// // }

// // static httpd_handle_t start_wss_echo_server(void)
// // {
// //     httpd_handle_t server = NULL;
// //     httpd_config_t config = HTTPD_DEFAULT_CONFIG();
// //     config.open_fn = wss_open_fd;
// //     config.close_fn = wss_close_fd;
// //     esp_err_t ret = httpd_start(&server, &config);
// //     if (ret != ESP_OK)
// //     {
// //         ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
// //         return NULL;
// //     }
// //     httpd_uri_t ws = {
// //         .uri = "/ws",
// //         .method = HTTP_GET,
// //         .handler = ws_handler,
// //         .is_websocket = true,
// //         .supported_subprotocol = NULL,
// //     };
// //     ret = httpd_register_uri_handler(server, &ws);
// //     if (ret != ESP_OK)
// //     {
// //         ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
// //         httpd_stop(server);
// //         return NULL;
// //     }
// //     return server;
// // }

// // static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// // {
// //     httpd_handle_t *server = (httpd_handle_t *)arg;
// //     if (*server)
// //     {
// //         httpd_stop(*server);
// //         *server = NULL;
// //     }
// // }

// // static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// // {
// //     httpd_handle_t *server = (httpd_handle_t *)arg;
// //     if (*server == NULL)
// //     {
// //         *server = start_wss_echo_server();
// //     }
// // }
// // static void button_init(int PIN_NUM)
// // {
// //     gpio_config_t io_conf = {
// //         .pin_bit_mask = (1ULL << PIN_NUM),
// //         .mode = GPIO_MODE_INPUT,
// //         .pull_up_en = GPIO_PULLUP_ENABLE,
// //         .pull_down_en = GPIO_PULLDOWN_DISABLE,
// //         .intr_type = GPIO_INTR_NEGEDGE // interrupt generate when botton press on falling edge
// //     };
// //     gpio_config(&io_conf);
// //     gpio_set_direction(PIN_NUM, GPIO_MODE_INPUT);
// // }
// // // ISR Handlers Forward Declarations
// // void IRAM_ATTR button_isr_handler(void *arg);
// // void IRAM_ATTR button_isr_handler_1(void *arg);
// // void IRAM_ATTR button_isr_handler_2(void *arg);

// // // Definitions of ISR Handlers
// // void IRAM_ATTR button_isr_handler(void *arg)
// // {
// //     uint32_t pin = (uint32_t)arg;
// //     printf("DOWN_PIN is pressed\n");
// //     data[set]--;
// //     set_rtc_time_interrupt(data[1], data[0]);
// // }

// // void IRAM_ATTR button_isr_handler_1(void *arg)
// // {
// //     uint32_t pin = (uint32_t)arg;
// //     printf("UP_PIN is pressed\n");
// //     data[set]++;
// //     set_rtc_time_interrupt(data[1], data[0]);
// // }

// // void IRAM_ATTR button_isr_handler_2(void *arg)
// // {
// //     uint32_t pin = (uint32_t)arg;
// //     printf("SET_PIN is pressed\n");
// //     if (i)
// //     {
// //         ESP_LOGI(TAG, "MINUTE MODE");
// //         set = 1;
// //     }
// //     else
// //     {
// //         ESP_LOGI(TAG, "HOUR MODE");
// //         set = 0;
// //     }
// //     i = !i;
// // }

// // static void initialize_isr_service()
// // {
// //     gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
// //     gpio_isr_handler_add(DOWN_PIN, button_isr_handler, (void *)DOWN_PIN);
// // }

// // static void initialize_isr_service1()
// // {
// //     gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
// //     gpio_isr_handler_add(UP_PIN, button_isr_handler_1, (void *)UP_PIN);
// // }

// // static void initialize_isr_service2()
// // {
// //     gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
// //     gpio_isr_handler_add(SET_PIN, button_isr_handler_2, (void *)SET_PIN);
// // }

// void app_main(void)
// {
//     static httpd_handle_t server = NULL;
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
//     {
//         ESP_ERROR_CHECK(nvs_flash_erase());
//         ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(ret);
//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_ap();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
//     ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STADISCONNECTED, &disconnect_handler, &server));
//     wifi_config_t wifi_config = {
//         .ap = {
//             .ssid = "ESP32-Access-Point",
//             .ssid_len = strlen("ESP32-Access-Point"),
//             .password = "password",
//             .max_connection = MAX_STA_CONN,
//             .authmode = WIFI_AUTH_WPA_WPA2_PSK,
//         },
//     };
//     if (strlen("password") == 0)
//     {
//         wifi_config.ap.authmode = WIFI_AUTH_OPEN;
//     }
//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());
//     ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", "ESP32-Access-Point", "password");
//     i2c_master_init();
//     server = start_wss_echo_server();
//     spi_init();
//     max7219_init_all();

//     button_init(DOWN_PIN); // 25
//     button_init(UP_PIN);   // 26
//     button_init(SET_PIN);  // 27

//     initialize_isr_service();
//     initialize_isr_service1();
//     initialize_isr_service2();

//     gpio_config_t io_conf = {
//         .pin_bit_mask = (1ULL << ALARM_PIN),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};
//     gpio_config(&io_conf);
//     gpio_set_direction(ALARM_PIN, GPIO_MODE_OUTPUT);
//     gpio_set_level(ALARM_PIN, 0);

//     while (1)
//     {

//         get_rtc_time(&current_hour, &current_minute);

//         data[0] = current_hour;
//         data[1] = current_minute;

//         display_number(current_hour, current_minute);
//         ESP_LOGI(TAG, "ALARM time  %02d:%02d", alarm_hour, alarm_minute);
//         ESP_LOGI(TAG, "current time  %02d:%02d", current_hour, current_minute);
//         gpio_set_level(ALARM_PIN, 0);
//         if (current_hour == alarm_hour && current_minute == alarm_minute)
//         {
//             gpio_set_level(ALARM_PIN, 1);
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//             gpio_set_level(ALARM_PIN, 0);
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//         }
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }
// all done

// #include <stdio.h>
// #include <string.h>
// #include <math.h>
// #include <stdlib.h>
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
// #include "rtc.h"
// #include "driver/gpio.h"
// #include <esp_timer.h>
// #include <time.h>
// #include "esp_intr_types.h"
// #include "driver/i2c.h"
// #include "driver/spi_master.h"
// #include "driver/adc.h"
// #include "esp_adc_cal.h"
// #include "esp_adc/adc_continuous.h"
// #include "freertos/semphr.h"

// #define ALARM_PIN 14
// #define DOWN_PIN 25
// #define UP_PIN 26
// #define SET_PIN 27

// #define ESP_INTR_FLAG_DEFAULT 1
// #define DEFAULT_VREF 1100               // Default ADC reference voltage in mV
// #define ADC_WIDTH_BIT ADC_WIDTH_BIT_12  // ADC bit width (9, 10, 11, or 12)
// #define ADC_ATTENUATION ADC_ATTEN_DB_12 // ADC attenuation (0db, 2.5db, 6db, 11db)
// #define PORT_TICK_PERIOD_MS 1000        // Tick period in milliseconds
// #define ADC_GPIO ADC1_CHANNEL_5         // ADC channel for GPIO33
// #define DEBOUNCE_TIME_MS 300

// static esp_adc_cal_characteristics_t *adc_chars; // struct
// static const char *TAG = "main";

// SemaphoreHandle_t semaphore1, semaphore2, semaphore3;
// volatile uint32_t last_interrupt_time_1 = 0;
// volatile uint32_t last_interrupt_time_2 = 0;
// volatile uint32_t last_interrupt_time_3 = 0;

// #ifndef IRAM_ATTR
// #define IRAM_ATTR __attribute__((section(".iram1")))
// #endif
// #define MAX_STA_CONN 4

// volatile int alarm_hour = -1;
// volatile int alarm_minute = -1;
// volatile int current_hour;
// volatile int current_minute;
// volatile bool i = true;
// volatile int set = 0;
// volatile int hours, minutes, seconds, day, date, month, year;

// struct async_resp_arg
// {
//     httpd_handle_t hd;
//     int fd;
// };

// static esp_err_t ws_handler(httpd_req_t *req)
// {
//     if (req->method == HTTP_GET)
//     {
//         ESP_LOGI(TAG, "Handshake done, the new connection was opened");
//         return ESP_OK;
//     }

//     httpd_ws_frame_t ws_pkt;
//     uint8_t *buf = NULL;
//     memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
//     esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);

//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", ret);
//         return ret;
//     }

//     if (ws_pkt.len)
//     {
//         buf = calloc(1, ws_pkt.len + 1);
//         if (buf == NULL)
//         {
//             ESP_LOGE(TAG, "Failed to calloc memory for buf");
//             return ESP_ERR_NO_MEM;
//         }
//         ws_pkt.payload = buf;
//         ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);

//         if (ret != ESP_OK)
//         {
//             ESP_LOGE(TAG, "httpd_ws_recv_frame failed with %d", ret);
//             free(buf);
//             return ret;
//         }
//     }

//     if (ws_pkt.type == HTTPD_WS_TYPE_TEXT)
//     {
//         ESP_LOGI(TAG, "Received packet with message: %s", ws_pkt.payload);

//         if (sscanf((char *)ws_pkt.payload, "SET_TIME %2d:%2d:%2d %1d %2d/%2d/%4d", &hours, &minutes, &seconds, &day, &date, &month, &year) == 7)
//         {
//             current_hour = hours;
//             current_minute = minutes;
//             set_rtc_time(seconds, minutes, hours, day, date, month, year);
//             ESP_LOGI(TAG, "RTC time set to %02d:%02d:%02d, Date: %02d/%02d/%d day:%d", hours, minutes, seconds, date, month, year, day);
//             const char *ack = "Time set successfully";
//             ws_pkt.payload = (uint8_t *)ack;
//             ws_pkt.len = strlen(ack);
//             ret = httpd_ws_send_frame(req, &ws_pkt);

//             if (ret != ESP_OK)
//             {
//                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
//             }
//         }

//         if (sscanf((char *)ws_pkt.payload, "SET_ALARM %2d:%2d", &hours, &minutes) == 2)
//         {
//             alarm_hour = hours;
//             alarm_minute = minutes;
//             ESP_LOGI(TAG, "Alarm time set to %02d:%02d", alarm_hour, alarm_minute);
//             const char *ack = "Alarm set successfully";
//             ws_pkt.payload = (uint8_t *)ack;
//             ws_pkt.len = strlen(ack);
//             ret = httpd_ws_send_frame(req, &ws_pkt);

//             if (ret != ESP_OK)
//             {
//                 ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", ret);
//             }
//         }
//         free(buf);
//         return ESP_OK;
//     }
//     return ESP_FAIL;
// }

// static esp_err_t wss_open_fd(httpd_handle_t hd, int sockfd)
// {
//     ESP_LOGI(TAG, "New client connected %d", sockfd);
//     return ESP_OK;
// }

// static void wss_close_fd(httpd_handle_t hd, int sockfd)
// {
//     ESP_LOGI(TAG, "Client disconnected %d", sockfd);
// }

// static httpd_handle_t start_wss_echo_server(void)
// {
//     httpd_handle_t server = NULL;
//     httpd_config_t config = HTTPD_DEFAULT_CONFIG();
//     config.open_fn = wss_open_fd;
//     config.close_fn = wss_close_fd;
//     esp_err_t ret = httpd_start(&server, &config);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to start HTTP server: %s", esp_err_to_name(ret));
//         return NULL;
//     }
//     httpd_uri_t ws = {
//         .uri = "/ws",
//         .method = HTTP_GET,
//         .handler = ws_handler,
//         .is_websocket = true,
//         .supported_subprotocol = NULL,
//     };
//     ret = httpd_register_uri_handler(server, &ws);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to register URI handler: %s", esp_err_to_name(ret));
//         httpd_stop(server);
//         return NULL;
//     }
//     return server;
// }

// static void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// {
//     httpd_handle_t *server = (httpd_handle_t *)arg;
//     if (*server)
//     {
//         httpd_stop(*server);
//         *server = NULL;
//     }
// }

// static void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
// {
//     httpd_handle_t *server = (httpd_handle_t *)arg;
//     if (*server == NULL)
//     {
//         *server = start_wss_echo_server();
//     }
// }

// static void button_init(int PIN_NUM)
// {

//     gpio_config_t io_conf;
//     io_conf.intr_type = GPIO_INTR_NEGEDGE;
//     io_conf.pin_bit_mask = (1ULL << PIN_NUM);
//     io_conf.mode = GPIO_MODE_INPUT;
//     io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
//     io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
//     esp_err_t ret = gpio_config(&io_conf);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to configure GPIO: %s", esp_err_to_name(ret));
//         return;
//     }
// }

// // volatile bool update_time_flag_minute_down, update_time_flag_hour_down, update_time_flag_minute_up, update_time_flag_hour_up;
// // #define DOWN_PIN 25
// // #define UP_PIN 26
// // #define SET_PIN 27

// void IRAM_ATTR gpio_isr_handler(void *arg)
// {
//     uint32_t gpio_num = (uint32_t)arg;
//     uint32_t current_time = xTaskGetTickCountFromISR();
//     if (gpio_num == DOWN_PIN && (current_time - last_interrupt_time_1) > pdMS_TO_TICKS(DEBOUNCE_TIME_MS))
//     {
//         last_interrupt_time_1 = current_time;
//         xSemaphoreGiveFromISR(semaphore1, NULL);
//     }
// }

// void IRAM_ATTR gpio_isr_handler1(void *arg)
// {
//     uint32_t gpio_num = (uint32_t)arg;
//     uint32_t current_time = xTaskGetTickCountFromISR();
//     if (gpio_num == UP_PIN && (current_time - last_interrupt_time_2) > pdMS_TO_TICKS(DEBOUNCE_TIME_MS))
//     {
//         last_interrupt_time_2 = current_time;
//         xSemaphoreGiveFromISR(semaphore2, NULL);
//     }
// }

// void IRAM_ATTR gpio_isr_handler2(void *arg)
// {
//     uint32_t gpio_num = (uint32_t)arg;
//     uint32_t current_time = xTaskGetTickCountFromISR();
//     if (gpio_num == SET_PIN && (current_time - last_interrupt_time_3) > pdMS_TO_TICKS(DEBOUNCE_TIME_MS))
//     {
//         last_interrupt_time_3 = current_time;
//         xSemaphoreGiveFromISR(semaphore3, NULL);
//     }
// }

// void task1(void *pvParameter)
// {
//     while (1)
//     {
//         if (xSemaphoreTake(semaphore1, portMAX_DELAY))
//         {
//             if (set == 1)
//             {
//                 current_minute--;
//                 if (current_minute < 0)
//                 {
//                     current_minute = 59;
//                 }
//                 uint8_t data[3];
//                 data[1] = ((current_minute / 10) << 4) | (current_minute % 10);
//                 data[2] = ((current_hour / 10) << 4) | (current_hour % 10);
//                 i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//                 i2c_master_start(cmd);
//                 i2c_master_write_byte(cmd, (0x68 << 1) | I2C_MASTER_WRITE, true);
//                 i2c_master_write_byte(cmd, 0x00, true);
//                 i2c_master_write(cmd, data, 3, true);
//                 i2c_master_stop(cmd);
//                 i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
//                 i2c_cmd_link_delete(cmd);
//                 ESP_LOGI("Task1", "Interrupt received...1 and minute down");
//                 time_flag_minute = true;
//                 // time_flag_hour = false;
//             }
//             else
//             {
//                 current_hour--;
//                 if (current_hour < 0)
//                 {
//                     current_hour = 23;
//                 }
//                 uint8_t data[3];
//                 data[1] = ((current_minute / 10) << 4) | (current_minute % 10);
//                 data[2] = ((current_hour / 10) << 4) | (current_hour % 10);
//                 i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//                 i2c_master_start(cmd);
//                 i2c_master_write_byte(cmd, (0x68 << 1) | I2C_MASTER_WRITE, true);
//                 i2c_master_write_byte(cmd, 0x00, true);
//                 i2c_master_write(cmd, data, 3, true);
//                 i2c_master_stop(cmd);
//                 i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
//                 i2c_cmd_link_delete(cmd);
//                 ESP_LOGI("Task1", "Interrupt received...1 and hour down");
//                 time_flag_hour = true;
//                 // time_flag_minute = false;
//             }
//             // display_number(current_hour, current_minute);
//             // vTaskDelay(2000 / portTICK_PERIOD_MS);
//             update_time_flag = true;
//             update_time_flag_1 = true;
//         }
//     }
// }

// void task2(void *pvParameter)
// {
//     while (1)
//     {
//         if (xSemaphoreTake(semaphore2, portMAX_DELAY))
//         {
//             if (set == 1)
//             {
//                 current_minute++;
//                 if (current_minute > 59)
//                 {
//                     current_minute = 0;
//                 }
//                 uint8_t data[3];
//                 data[1] = ((current_minute / 10) << 4) | (current_minute % 10);
//                 data[2] = ((current_hour / 10) << 4) | (current_hour % 10);
//                 i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//                 i2c_master_start(cmd);
//                 i2c_master_write_byte(cmd, (0x68 << 1) | I2C_MASTER_WRITE, true);
//                 i2c_master_write_byte(cmd, 0x00, true);
//                 i2c_master_write(cmd, data, 3, true);
//                 i2c_master_stop(cmd);
//                 i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
//                 i2c_cmd_link_delete(cmd);
//                 ESP_LOGI("Task2", "Interrupt received...2 and minute up");
//                 time_flag_minute = true;
//                 time_flag_hour = false;
//             }
//             else
//             {
//                 current_hour++;
//                 if (current_hour > 23)
//                 {
//                     current_hour = 0;
//                 }
//                 uint8_t data[3];
//                 data[1] = ((current_minute / 10) << 4) | (current_minute % 10);
//                 data[2] = ((current_hour / 10) << 4) | (current_hour % 10);
//                 i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//                 i2c_master_start(cmd);
//                 i2c_master_write_byte(cmd, (0x68 << 1) | I2C_MASTER_WRITE, true);
//                 i2c_master_write_byte(cmd, 0x00, true);
//                 i2c_master_write(cmd, data, 3, true);
//                 i2c_master_stop(cmd);
//                 i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
//                 i2c_cmd_link_delete(cmd);
//                 ESP_LOGI("Task2", "Interrupt received...2 and hour up");
//                 time_flag_hour = true;
//                 time_flag_minute = false;
//             }
//             // display_number(current_hour, current_minute);
//             // vTaskDelay(2000 / portTICK_PERIOD_MS);
//             update_time_flag = true;
//             update_time_flag_1 = true;
//         }
//     }
// }

// void task3(void *pvParameter)
// {
//     while (1)
//     {
//         if (xSemaphoreTake(semaphore3, portMAX_DELAY))
//         {
//             set = !set;
//             if (set)
//             {
//                 ESP_LOGI("Task3", "Interrupt received...3 and minute set");
//             }
//             else if (set == 0)
//             {
//                 ESP_LOGI("Task3", "Interrupt received...3 and hour set");
//             }
//             update_time_flag = true;
//         }
//     }
// }

// void initialize_isr_service()
// {
//     esp_err_t ret = gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to install ISR service: %s", esp_err_to_name(ret));
//         return;
//     }

//     ret = gpio_isr_handler_add(DOWN_PIN, gpio_isr_handler, (void *)DOWN_PIN);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to add ISR handler for DOWN_PIN: %s", esp_err_to_name(ret));
//     }

//     ret = gpio_isr_handler_add(UP_PIN, gpio_isr_handler1, (void *)UP_PIN);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to add ISR handler for UP_PIN: %s", esp_err_to_name(ret));
//     }

//     ret = gpio_isr_handler_add(SET_PIN, gpio_isr_handler2, (void *)SET_PIN);
//     if (ret != ESP_OK)
//     {
//         ESP_LOGE(TAG, "Failed to add ISR handler for SET_PIN: %s", esp_err_to_name(ret));
//     }
// }
// // void brightness_set(int adc)
// // {
// //     if (adc <= 273)
// //     {
// //         max7219_send_byte_all(0x0A, 0x01);
// //     }
// //     if (adc > 273 && adc <= 546)
// //     {
// //         max7219_send_byte_all(0x0A, 0x02);
// //     }
// //     if (adc > 546 && adc <= 819)
// //     {
// //         max7219_send_byte_all(0x0A, 0x03);
// //     }
// //     if (adc > 819 && adc <= 1092)
// //     {
// //         max7219_send_byte_all(0x0A, 0x04);
// //     }
// //     if (adc > 1092 && adc <= 1365)
// //     {
// //         max7219_send_byte_all(0x0A, 0x05);
// //     }
// //     if (adc > 1365 && adc <= 1688)
// //     {
// //         max7219_send_byte_all(0x0A, 0x06);
// //     }
// //     if (adc > 1688 && adc <= 1911)
// //     {
// //         max7219_send_byte_all(0x0A, 0x07);
// //     }
// //     if (adc > 1911 && adc <= 2184)
// //     {
// //         max7219_send_byte_all(0x0A, 0x08);
// //     }
// //     if (adc > 2184 && adc <= 2457)
// //     {
// //         max7219_send_byte_all(0x0A, 0x09);
// //     }
// //     if (adc > 2457 && adc <= 2730)
// //     {
// //         max7219_send_byte_all(0x0A, 0x0A);
// //     }
// //     if (adc > 2730 && adc <= 3003)
// //     {
// //         max7219_send_byte_all(0x0A, 0x0B);
// //     }
// //     if (adc > 3003 && adc <= 3276)
// //     {
// //         max7219_send_byte_all(0x0A, 0x0C);
// //     }
// //     if (adc > 3276 && adc <= 3549)
// //     {
// //         max7219_send_byte_all(0x0A, 0x0D);
// //     }
// //     if (adc > 3549 && adc <= 3822)
// //     {
// //         max7219_send_byte_all(0x0A, 0x0E);
// //     }
// //     if (adc > 3822 && adc <= 4095)
// //     {
// //         max7219_send_byte_all(0x0A, 0x0F);
// //     }
// // }

// // sunday 19,21,14,4,1,25
// // monday 13,15,14,4,1,25
// // tuesday 20,21,5,19,4,1,25
// // wednesday 23,5,4,14,5,19,4,1,25
// // thursday 10,8,21,18,19,4,1,25
// // friday 6,18,9,4,1,25
// // saturday 19,1,20,21,18,4,1,25
// volatile int *day_print;
// void day_time(int day)
// {
//     switch (day+1)
//     {
//     case 1:
//         day_print = (int *)realloc(day_print, 7 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {18, 20, 13, 3, 0, 24, 26};
//             for (int i = 0; i < 7; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(7, day_print);
//         }
//         break;
//     case 2:
//         day_print = (int *)realloc(day_print, 7 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {12, 14, 13, 3, 0, 24, 26};
//             for (int i = 0; i < 7; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(7, day_print);
//         }
//         break;
//     case 3:
//         day_print = (int *)realloc(day_print, 8 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {19, 20, 4, 18, 3, 0, 24, 26};
//             for (int i = 0; i < 8; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(8, day_print);
//         }
//         break;
//     case 4:
//         day_print = (int *)realloc(day_print, 10 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {22, 4, 3, 13, 4, 18, 3, 0, 24, 26};
//             for (int i = 0; i < 10; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(10, day_print);
//         }
//         break;
//     case 5:
//         day_print = (int *)realloc(day_print, 9 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {19, 7, 20, 17, 18, 3, 0, 24, 26};
//             for (int i = 0; i < 9; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(9, day_print);
//         }
//         break;
//     case 6:
//         day_print = (int *)realloc(day_print, 7 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {5, 17, 8, 3, 0, 24, 26};
//             for (int i = 0; i < 7; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(7, day_print);
//         }
//         break;
//     case 7:
//         day_print = (int *)realloc(day_print, 9 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {18, 0, 19, 20, 17, 3, 0, 24, 26};
//             for (int i = 0; i < 9; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             scroll_character(9, day_print);
//         }
//         break;
//     default:
//         ESP_LOGE(TAG, "ERROR_in dayprint");
//         break;
//     }
// }

// void app_main(void)
// {

//     static httpd_handle_t server = NULL;
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
//     {
//         ESP_ERROR_CHECK(nvs_flash_erase());
//         ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(ret);
//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_ap();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
//     ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STADISCONNECTED, &disconnect_handler, &server));

//     adc1_config_width(ADC_WIDTH_BIT);                     // config bit width
//     adc1_config_channel_atten(ADC_GPIO, ADC_ATTENUATION); // config analog attenuation

//     adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));                                  // allocate memory to calloc
//     esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTENUATION, ADC_WIDTH_BIT, DEFAULT_VREF, adc_chars); // initialize calibration

//     ESP_LOGI(TAG, "ADC  %d", adc);
//     wifi_config_t wifi_config = {
//         .ap = {
//             .ssid = "ESP32-Access-Point",
//             .ssid_len = strlen("ESP32-Access-Point"),
//             .password = "password",
//             .max_connection = MAX_STA_CONN,
//             .authmode = WIFI_AUTH_WPA_WPA2_PSK,
//         },
//     };
//     if (strlen("password") == 0)
//     {
//         wifi_config.ap.authmode = WIFI_AUTH_OPEN;
//     }
//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());
//     ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", "ESP32-Access-Point", "password");
//     i2c_master_init();
//     server = start_wss_echo_server();
//     spi_init();
//     max7219_init_all();

//     semaphore1 = xSemaphoreCreateBinary();
//     semaphore2 = xSemaphoreCreateBinary();
//     semaphore3 = xSemaphoreCreateBinary();

//     button_init(DOWN_PIN);
//     button_init(UP_PIN);
//     button_init(SET_PIN);

//     initialize_isr_service();

//     xTaskCreate(&task1, "Task1", 2048, NULL, 5, NULL);
//     xTaskCreate(&task2, "Task2", 2048, NULL, 5, NULL);
//     xTaskCreate(&task3, "Task3", 2048, NULL, 5, NULL);

//     gpio_config_t io_conf = {
//         .pin_bit_mask = (1ULL << ALARM_PIN),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE};
//     gpio_config(&io_conf);
//     gpio_set_direction(ALARM_PIN, GPIO_MODE_OUTPUT);
//     gpio_set_level(ALARM_PIN, 0);

//     while (1)
//     {
//         get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
//         display_number(current_hour, current_minute);
//         ESP_LOGI(TAG, "current time  %02d:%02d", current_hour, current_minute);
//         volatile int time_date[23] = {current_hour / 10, current_hour % 10, current_minute / 10, current_minute % 10, 13, 13, 13, 13, date / 10, date % 10, 12, month / 10, month % 10, 12, 2, 0, ((year % 100) / 10), (year % 10), 13, 13, 13, 13};

//         brightness_set(adc);
//         for (int i = 0; i < 5; i++)
//         {
//             get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
//             display_number(current_hour, current_minute);
//             ESP_LOGI(TAG, "ALARM time  %02d:%02d", alarm_hour, alarm_minute);
//             ESP_LOGI(TAG, "current time  %02d:%02d", current_hour, current_minute);

//             if (current_hour == alarm_hour && current_minute == alarm_minute)
//             {
//                 ESP_LOGI(TAG, "Alarm triggered");
//                 gpio_set_level(ALARM_PIN, 1);
//                 vTaskDelay(1000 / portTICK_PERIOD_MS);
//                 gpio_set_level(ALARM_PIN, 0);
//                 vTaskDelay(1000 / portTICK_PERIOD_MS);
//             }
//             vTaskDelay(1000 / portTICK_PERIOD_MS);
//         }
//         time_flag_hour = false;
//         time_flag_minute = false;
//         get_rtc_time(&current_hour, &current_minute, &day, &date, &month, &year);
//         scroll_number(23, time_date);
//         day_time(day);
//     }
// }

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

// volatile bool update_time_flag_minute_down, update_time_flag_hour_down, update_time_flag_minute_up, update_time_flag_hour_up;
// #define DOWN_PIN 25
// #define UP_PIN 26
// #define SET_PIN 27

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

// true void day_time(int day)
// {
//     switch (day + 1)
//     {
//     case 1:
//         day_print = (int *)realloc(day_print, 7 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {18, 20, 13, 3, 0, 24, 26};
//             for (int i = 0; i < 7; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(7, day_print);
//         }
//         break;
//     case 2:
//         day_print = (int *)realloc(day_print, 7 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {12, 14, 13, 3, 0, 24, 26};
//             for (int i = 0; i < 7; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(7, day_print);
//         }
//         break;
//     case 3:
//         day_print = (int *)realloc(day_print, 8 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {19, 20, 4, 18, 3, 0, 24, 26};
//             for (int i = 0; i < 8; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(8, day_print);
//         }
//         break;
//     case 4:
//         day_print = (int *)realloc(day_print, 10 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {22, 4, 3, 13, 4, 18, 3, 0, 24, 26};
//             for (int i = 0; i < 10; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(10, day_print);
//         }
//         break;
//     case 5:
//         day_print = (int *)realloc(day_print, 9 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {19, 7, 20, 17, 18, 3, 0, 24, 26};
//             for (int i = 0; i < 9; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(9, day_print);
//         }
//         break;
//     case 6:
//         day_print = (int *)realloc(day_print, 7 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {5, 17, 8, 3, 0, 24, 26};
//             for (int i = 0; i < 7; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(7, day_print);
//         }
//         break;
//     case 7:
//         day_print = (int *)realloc(day_print, 9 * sizeof(int));
//         if (day_print != NULL)
//         {
//             int new_values[] = {18, 0, 19, 20, 17, 3, 0, 24, 26};
//             for (int i = 0; i < 9; i++)
//             {
//                 day_print[i] = new_values[i];
//             }
//             if (time_flag_day)
//             {
//                 break;
//             }
//             scroll_character(9, day_print);
//         }
//         break;
//     default:
//         ESP_LOGE(TAG, "ERROR_in dayprint");
//         break;
//     }
//     for (int i = 0; i < 4; i++)
//     {
//         day_set[i] = day_print[i];
//     }
// }
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
