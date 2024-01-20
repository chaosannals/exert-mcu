#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "esp_spiffs.h"

#include "spiffs_demo.h"

// spiffs 操作
void spiffs_action() {
    // ESP_LOGI(TAG, "Initializing SPIFFS");
    printf("Initializing SPIFFS\n");
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };

    // 注册
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            // ESP_LOGE(TAG, "Failed to mount or format filesystem");
            printf("Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            // ESP_LOGE(TAG, "Failed to find SPIFFS partition");
            printf("Failed to find SPIFFS partition");
        } else {
            // ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
            printf("Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    // 获取信息
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        // ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        printf("Failed to get SPIFFS partition information (%s). Formatting...\n", esp_err_to_name(ret));
        esp_spiffs_format(conf.partition_label);
        return;
    } else {
        // ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
        printf("Partition size: total: %d, used: %d \n", (int)total, (int)used);
    }

    // 检查分区情况，太小的时候会导致不可用，(比如只分配 1k)
    // 如果分配太大是直接就编译失败，比如 1M
    if (used > total) {
        // ESP_LOGW(TAG, "Number of used bytes cannot be larger than total. Performing SPIFFS_check().");
        printf("Number of used bytes cannot be larger than total. Performing SPIFFS_check().\n");
        
        ret = esp_spiffs_check(conf.partition_label);
        // 校验
        // 更多信息： https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiffs_check
        if (ret != ESP_OK) {
            // ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
            printf("SPIFFS_check() failed (%s)\n", esp_err_to_name(ret));
            return;
        } else {
            // ESP_LOGI(TAG, "SPIFFS_check() successful");
            printf("SPIFFS_check() successful\n");
        }
    }

    // 使用 POSIX 和 C 标准库函数操作
    // 创建并写入文件
    // ESP_LOGI(TAG, "Opening file");
    printf("Opening file\n");
    FILE* f = fopen("/spiffs/hello.txt", "w");
    if (f == NULL) {
        // ESP_LOGE(TAG, "Failed to open file for writing");
        printf("Failed to open file for writing\n");
        return;
    }
    fprintf(f, "Hello World!\n");
    fclose(f);
    // ESP_LOGI(TAG, "File written");
    printf("File written\n");

    // 获取目标文件状态
    // 依赖 #include <sys/stat.h>
    struct stat st;
    if (stat("/spiffs/foo.txt", &st) == 0) {
        // 如果存在就删除。
        // 依赖 #include <sys/unistd.h>
        unlink("/spiffs/foo.txt");
    }

    // 重名文件
    // ESP_LOGI(TAG, "Renaming file");
    printf("Renaming file\n");
    if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0) {
        // ESP_LOGE(TAG, "Rename failed");
        printf("Rename failed\n");
        return;
    }

    // 打开文件并读取
    // ESP_LOGI(TAG, "Reading file");
    printf("Reading file\n");
    f = fopen("/spiffs/foo.txt", "r");
    if (f == NULL) {
        // ESP_LOGE(TAG, "Failed to open file for reading");
        printf("Failed to open file for reading\n");
        return;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // 去掉换行，把换行换成 0 做 c 字符串结束符
    char* pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    // ESP_LOGI(TAG, "Read from file: '%s'", line);
    printf("Read from file: '%s'\n", line);

    // 完成，卸载
    esp_vfs_spiffs_unregister(conf.partition_label);
    // ESP_LOGI(TAG, "SPIFFS unmounted");
    printf( "SPIFFS unmounted\n");
}