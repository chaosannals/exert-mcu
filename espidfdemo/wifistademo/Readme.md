# spiffs demo

wifi 密码通过定义宏传递给程序。
sdkconfig 的变量会被生成 C 宏

CONFIG_ESP_WIFI_SSID=ssid_name
CONFIG_ESP_WIFI_PASSWORD=wifi_pass


ESP32S

分区文件 partitions.csv （可以通过 sdkconfig 改名）
需要 CONFIG_PARTITION_TABLE_CUSTOM=y 才起效。

OTA 不能在 工厂分区下使用，有工厂分区会直接从工厂分区启动。
