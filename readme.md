# exert mcu

## [意法半导体（ST）](https://st.com)

### STM32

### STM8

## [乐鑫科技（Espressif）](https://www.espressif.com.cn/)

### ESP32 和 ESP8266

这两款可以通过安装 micropython 配合 Thonny 使用，
或者官方的 [Flash 下载工具](https://www.espressif.com.cn/zh-hans/support/download/all) 下载 c 编译的二进制。


## MicroPython

### 启动

micropython 默认执行根目录下 main.py 文件。如果有 boot.py 的板子会先执行 boot.py 再执行 main.py 。

注：一般不要修改 boot.py 的板子的该文件。
