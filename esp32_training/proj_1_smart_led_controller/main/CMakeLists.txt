idf_component_register(SRCS "adc.c" "main.c" "max7219.c" "i2c_rtc.c" "keep_alive.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES "certs/servercert.pem"
                                   "certs/prvtkey.pem")
