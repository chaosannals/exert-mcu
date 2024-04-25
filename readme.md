# exert mcu

## 库

### SEGGER emWin 

UI 图形库。

## 逻辑分析仪

### [PulseView](https://sigrok.org/wiki/Downloads)

开源的逻辑分析仪软件。

## [意法半导体（ST）](https://st.com)

### STM32F0x

Cortex-M0 系列

### STM32F10x

Cortex-M3 系列

### STM8

## [乐鑫科技（Espressif）](https://www.espressif.com.cn/)

Wifi 和 蓝牙芯片不错。

### [ESP IDF](https://idf.espressif.com/)

IDF 是个框架，提供了 vscode 和 eclipse 的插件。

vscode 创建项目居然是让去复制 examples 里面的项目。做个生成项目引导就这么难么，没几个文件阿。

底部栏小图标设置各种配置，操作按钮也在底部栏。左边栏有个 exploder 可查看详细点的信息。

提供了:

- build 构建
- flash 烧录
- monitor 监控，即：串口或者 JTAG 信息。

### ESP32 和 ESP8266

这两款可以通过安装 micropython 配合 Thonny 使用，
或者官方的 [Flash 下载工具](https://www.espressif.com.cn/zh-hans/support/download/all) 下载 c 编译的二进制。


## [沁恒微电子（WCH）](https://www.wch.cn/)

USB 做得不错。

### CH55x

MCS51 系列的单片机，比传统的 51 体积小，外设多，性能强。支持 USB 烧录。

### CH32F10x

Cortex-M3 系列，性价比高，支持 USB 烧录。

## [MicroPython](https://micropython.org)

## [CircuitPython](https://circuitpython.org)

### 启动

micropython 默认执行根目录下 main.py 文件。如果有 boot.py 的板子会先执行 boot.py 再执行 main.py 。

注：一般不要修改 boot.py 的板子的该文件。
