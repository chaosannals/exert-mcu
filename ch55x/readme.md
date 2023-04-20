# CH55x

沁恒 msc51 系列单片机。


## [SDCC - Small Device C Compiler](https://sdcc.sourceforge.net/)

```bat
@rem ihx 转 hex
packihx out.ihx > out.hex

@rem ihx 转 bin
objcopy -I ihex -O binary out.ihx out.bin
```
