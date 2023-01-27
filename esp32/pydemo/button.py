# 微动开关 5V
# 倾斜开关  5V
# 震动传感器 5V

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