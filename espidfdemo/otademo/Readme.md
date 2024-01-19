# spiffs demo

ESP32S

分区文件 partitions.csv （可以通过 sdkconfig 改名）
需要 CONFIG_PARTITION_TABLE_CUSTOM=y 才起效。

OTA 不能在 工厂分区下使用，有工厂分区会直接从工厂分区启动。

## 测试服务器

```bash
# 安装依赖。
pip install pexpect
pip install pytest
pip install pytest-embedded
```