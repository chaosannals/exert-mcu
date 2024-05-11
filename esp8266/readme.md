# ESP8266

## 烧录

ESP8266 默认是通过 UART0 （即 TX0（GPIO1）和 RXD（GPIO3））来下载固件的

硬件接线
需要满足以下接线条件：

VDD     -> 3V3
GND     -> GND   (与供电板“共地”)
EN      -> 拉高   (用于上电启动、不可浮空)
GPIO0   -> 拉低   (进入下载模式)
GPIO15  -> 拉低
TXD0    -> RX
RXD0    -> TX

## 开发板

### 开发板（CH9102X + 25Q32 4M Flash）