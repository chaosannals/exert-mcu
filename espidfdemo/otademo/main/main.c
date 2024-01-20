#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_wifi.h"

#include "esp_crt_bundle.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "chip.h"
#include "spiffs_demo.h"
#include "wifi_sta_demo.h"

#include "main.h"

#define HASH_LEN 32

// static const char *TAG = "exert";

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
        // ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        printf("HTTP_EVENT_ERROR\n");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        // ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        printf("===============================\n");
        printf("HTTP_EVENT_ON_CONNECTED\n");
        break;
    case HTTP_EVENT_HEADER_SENT:
        // ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        printf("HTTP_EVENT_HEADER_SENT\n");
        break;
    case HTTP_EVENT_ON_HEADER:
        // ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        printf("HTTP_EVENT_ON_HEADER, key=%s, value=%s\n", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        // ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        printf("HTTP_EVENT_ON_DATA, len=%d\n", evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        // ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        printf("HTTP_EVENT_ON_FINISH\n");
        break;
    case HTTP_EVENT_DISCONNECTED:
        // ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        printf("HTTP_EVENT_DISCONNECTED\n");
        break;
    case HTTP_EVENT_REDIRECT:
        // ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
        printf("HTTP_EVENT_REDIRECT\n");
        break;
    }
    return ESP_OK;
}

void simple_ota_example_task(void *pvParameter)
{
    // ESP_LOGI(TAG, "Starting OTA example task");
    printf("Starting OTA example task\n");
// #ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
    // esp_netif_t *netif = get_example_netif_from_desc(bind_interface_name);
    // if (netif == NULL) {
    //     // ESP_LOGE(TAG, "Can't find netif from interface description");
    //     printf("Can't find netif from interface description\n");
    //     abort();
    // }
    // struct ifreq ifr;
    // esp_netif_get_netif_impl_name(netif, ifr.ifr_name);
    // // ESP_LOGI(TAG, "Bind interface name is %s", ifr.ifr_name);
    // printf("Bind interface name is %s\n", ifr.ifr_name);
// #endif
    esp_http_client_config_t config = {
        .url = CONFIG_EXAMPLE_FIRMWARE_UPGRADE_URL,
// #ifdef CONFIG_EXAMPLE_USE_CERT_BUNDLE
        .crt_bundle_attach = esp_crt_bundle_attach,
// #else
        // .cert_pem = (char *)server_cert_pem_start,
// #endif /* CONFIG_EXAMPLE_USE_CERT_BUNDLE */
        .event_handler = _http_event_handler,
        .keep_alive_enable = true,
// #ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
        // .if_name = &ifr,
// #endif
    };

// 从 STDIN 获取 URL，不使用。
// #ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_URL_FROM_STDIN
//     char url_buf[OTA_URL_SIZE];
//     if (strcmp(config.url, "FROM_STDIN") == 0) {
//         example_configure_stdin_stdout();
//         fgets(url_buf, OTA_URL_SIZE, stdin);
//         int len = strlen(url_buf);
//         url_buf[len - 1] = '\0';
//         config.url = url_buf;
//     } else {
//         ESP_LOGE(TAG, "Configuration mismatch: wrong firmware upgrade image url");
//         abort();
//     }
// #endif

// #ifdef CONFIG_EXAMPLE_SKIP_COMMON_NAME_CHECK
    config.skip_cert_common_name_check = true;
// #endif

    esp_https_ota_config_t ota_config = {
        .http_config = &config,
    };
    // ESP_LOGI(TAG, "Attempting to download update from %s", config.url);
    printf("Attempting to download update from %s\n", config.url);
    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        // ESP_LOGI(TAG, "OTA Succeed, Rebooting...");
        printf("OTA Succeed, Rebooting...\n");
        esp_restart();
    } else {
        // ESP_LOGE(TAG, "Firmware upgrade failed");
        printf("Firmware upgrade failed\n");
    }
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// 打印 SHA256
static void print_sha256(const uint8_t *image_hash, const char *label)
{
    char hash_print[HASH_LEN * 2 + 1];
    hash_print[HASH_LEN * 2] = 0;
    for (int i = 0; i < HASH_LEN; ++i) {
        sprintf(&hash_print[i * 2], "%02x", image_hash[i]);
    }
    // ESP_LOGI(TAG, "%s %s", label, hash_print);
    printf("%s %s\n", label, hash_print);
}

// 获取分区的 sha256
static void get_sha256_of_partitions(void)
{
    uint8_t sha_256[HASH_LEN] = { 0 };
    esp_partition_t partition;

    // 获取 bootloader 的 sha256
    partition.address   = ESP_BOOTLOADER_OFFSET;
    partition.size      = ESP_PARTITION_TABLE_OFFSET;
    partition.type      = ESP_PARTITION_TYPE_APP;
    esp_partition_get_sha256(&partition, sha_256);
    print_sha256(sha_256, "SHA-256 for bootloader: ");

    // 获取当前运行的 应用所在分区的 sha256
    esp_partition_get_sha256(esp_ota_get_running_partition(), sha_256);
    print_sha256(sha_256, "SHA-256 for current firmware: ");
}

void app_main(void)
{
    // ESP_LOGI(TAG, "OTA example app_main start");
    printf("OTA example app_main start\n");
    
    init_nvc_demo();
    printf("NVS ok.\n");

    get_sha256_of_partitions();

    init_wifi_sta_demo();
    printf("wifi connect.\n");

    xTaskCreate(&simple_ota_example_task, "ota_example_task", 8192, NULL, 5, NULL);
    // printf("not update.\n");

    print_chip_info();
    spiffs_action();
    // wait_s_restart(10);
}