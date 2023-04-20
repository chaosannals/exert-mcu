# CH55x

[沁恒](https://www.wch.cn/) msc51 系列单片机。


## [SDCC - Small Device C Compiler](https://sdcc.sourceforge.net/)

编译器。

```bat
@rem ihx 转 hex
packihx out.ihx > out.hex

@rem ihx 转 bin
objcopy -I ihex -O binary out.ihx out.bin
```

## [WCHISPTool](https://www.wch.cn/downloads/WCHISPTool_Setup_exe.html)

烧录工具。 

### USB 烧录（板子必须有支持 5V 的电容）

注：+D 置高插入USB后，会无法识别设备，设备管理器 里禁止再启动就可识别。
