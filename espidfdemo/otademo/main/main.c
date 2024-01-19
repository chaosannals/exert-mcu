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

#include "nvs.h"
#include "nvs_flash.h"

#include "chip.h"
#include "spiffs_demo.h"

#define HASH_LEN 32

// static const char *TAG = "exert";


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
    // 初始化 NVS（Non-Volatile Storage） 非易失性存储 
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // 1.OTA app 分区有个小于 NVS 分区大小的 non-OTA 分区。
        // 报这个错误是因为 NVS 初始化失败。
        // 2.NVS 分区 数据格式太新或者不能被识别
        // 如果发生上面错误， 将擦除 NVS 并重新初始化 NVS
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
        printf("NVS reinit.\n");
    }
    ESP_ERROR_CHECK(err);
    printf("NVS ok.\n");

    get_sha256_of_partitions();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    print_chip_info();
    spiffs_action();
    // wait_s_restart(10);
}