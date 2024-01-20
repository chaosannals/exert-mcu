#include "esp_event.h"
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

#include "nvs_flash.h"

#include "chip.h"
#include "spiffs_demo.h"

#define DEFAULT_SCAN_LIST_SIZE 10


static void print_auth_mode(int authmode)
{
    switch (authmode) {
    case WIFI_AUTH_OPEN:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OPEN");
        printf("Authmode \tWIFI_AUTH_OPEN\n");
        break;
    case WIFI_AUTH_OWE:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OWE");
        printf("Authmode \tWIFI_AUTH_OWE\n");
        break;
    case WIFI_AUTH_WEP:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WEP");
        printf("Authmode \tWIFI_AUTH_WEP\n");
        break;
    case WIFI_AUTH_WPA_PSK:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_PSK");
        printf("Authmode \tWIFI_AUTH_WPA_PSK\n");
        break;
    case WIFI_AUTH_WPA2_PSK:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_PSK");
        printf("Authmode \tWIFI_AUTH_WPA2_PSK\n");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
        printf("Authmode \tWIFI_AUTH_WPA_WPA2_PSK\n");
        break;
    case WIFI_AUTH_ENTERPRISE:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_ENTERPRISE");
        printf("Authmode \tWIFI_AUTH_ENTERPRISE\n");
        break;
    case WIFI_AUTH_WPA3_PSK:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_PSK");
        printf("Authmode \tWIFI_AUTH_WPA3_PSK\n");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
        printf("Authmode \tWIFI_AUTH_WPA2_WPA3_PSK\n");
        break;
    case WIFI_AUTH_WPA3_ENT_192:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_ENT_192");
        printf( "Authmode \tWIFI_AUTH_WPA3_ENT_192\n");
        break;
    // case WIFI_AUTH_WPA3_EXT_PSK:
    //     // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_EXT_PSK");
    //     printf("Authmode \tWIFI_AUTH_WPA3_EXT_PSK\n");
    //     break;
    default:
        // ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_UNKNOWN");
        printf("Authmode \tWIFI_AUTH_UNKNOWN\n");
        break;
    }
}

static void print_cipher_type(int pairwise_cipher, int group_cipher)
{
    switch (pairwise_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE\n");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40\n");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP\n");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_AES_CMAC128:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_AES_CMAC128");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_AES_CMAC128\n");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_SMS4");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_SMS4\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP256");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP256\n");
        break;
    default:
        // ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        printf("Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN\n");
        break;
    }

    switch (group_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_NONE\n");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_WEP40\n");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_WEP104\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_SMS4");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_SMS4\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_GCMP\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP256");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_GCMP256\n");
        break;
    default:
        // ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        printf("Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN\n");
        break;
    }
}

/* 初始化 Wi-Fi STA 和设置扫描 */
static int wifi_scan(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    
    if (sta_netif == NULL) return -1;

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_scan_start(NULL, true);

    // ESP_LOGI(TAG, "Max AP number ap_info can hold = %u", number);
    printf("Max AP number ap_info can hold = %u\n", number);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    // ESP_LOGI(TAG, "Total APs scanned = %u, actual AP number ap_info holds = %u", ap_count, number);
    printf("Total APs scanned = %u, actual AP number ap_info holds = %u", ap_count, number);
    for (int i = 0; i < number; i++) {
        // ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
        printf("SSID \t\t%s\n", ap_info[i].ssid);
        // ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
        printf("RSSI \t\t%d\n", ap_info[i].rssi);
        print_auth_mode(ap_info[i].authmode);
        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
            print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
        }
        // ESP_LOGI(TAG, "Channel \t\t%d", ap_info[i].primary);
        printf("Channel \t\t%d\n", ap_info[i].primary);
        printf("===================================\n");
    }

    return 0;
}

void app_main(void) {
  printf("wifi scan example app_main start\n");
  // 初始化 NVS（Non-Volatile Storage） 非易失性存储
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
  printf("NVS ok.\n");

  wifi_scan();

  print_chip_info();
  spiffs_action();
  // wait_s_restart(10);
}