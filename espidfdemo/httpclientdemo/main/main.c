#include "esp_flash.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// #include "lwip/err.h"
// #include "lwip/sys.h"

#include "chip.h"
#include "spiffs_demo.h"
#include "wifi_sta_demo.h"

#include "main.h"

void app_main(void) {
  printf("http client example app_main start\n");
  init_nvc_demo();
  printf("NVS ok.\n");

  init_wifi_sta_demo();
  printf("Wifi Connect.");

  print_chip_info();
  spiffs_action();
  // wait_s_restart(10);
}