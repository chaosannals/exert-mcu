#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "chip.h"

// 初始化 NVS（Non-Volatile Storage） 非易失性存储
void init_nvc_demo(void) {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
      err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    // 1.OTA app 分区有个小于 NVS 分区大小的 non-OTA 分区。
    // 报这个错误是因为 NVS 初始化失败。
    // 2.NVS 分区 数据格式太新或者不能被识别
    // 如果发生上面错误， 将擦除 NVS 并重新初始化 NVS
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
    printf("NVS reinit.\n");
  }
  ESP_ERROR_CHECK(err);
}

// 打印芯片信息
int print_chip_info(void) {
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);

    // 支持的功能，支持就会带上相应的信息。
    // wifi
    // BT 蓝牙
    // BLE
    // 
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
            (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
            (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    // 芯片版本
    unsigned major_rev = chip_info.revision / 100; // 主版本
    unsigned minor_rev = chip_info.revision % 100; // 次版本
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return -1;
    }

    // 闪存大小
    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // 堆大小
    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    return 0;
}

// 等待几秒后重启
void wait_s_restart(int s) {
    // 等待 10 秒后重启。
    for (int i = s; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout); // 刷新标准输出
    esp_restart(); // 重启
}