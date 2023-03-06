# 传感器
# 倾斜开关  5V
# 震动传感器 5V
# 干簧管 5V
# U型光电传感器
# 触摸开关传感器
# 红外避障传感器 3.3V

from machine import Pin
from time import sleep

pin = Pin(2, Pin.IN)

def on_falling(v):
    print('falling', v)
    
def on_rising(v):
    print('rising', v)

pin.irq(trigger=Pin.IRQ_FALLING, handler=on_falling)
# 中断触发只能一个，下降沿或上升沿触发。
#pin.irq(trigger=Pin.IRQ_RISING, handler=on_rising)

status = 0
while True:
    v = pin.value()
    if v != status:
        print('change', v)
        status = v
    sleep(0.1)