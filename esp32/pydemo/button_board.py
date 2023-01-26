from machine import Pin
from time import sleep

b2 = Pin(2, Pin.IN, Pin.PULL_UP)
b4 = Pin(4, Pin.IN, Pin.PULL_UP)
b5 = Pin(5, Pin.IN, Pin.PULL_UP)
b14 = Pin(14, Pin.IN, Pin.PULL_UP)

print('start')

def on_detect(v):
    print(v)

b2.irq(trigger=Pin.IRQ_FALLING, handler=on_detect)
b4.irq(trigger=Pin.IRQ_FALLING, handler=on_detect)
b5.irq(trigger=Pin.IRQ_FALLING, handler=on_detect)
b14.irq(trigger=Pin.IRQ_FALLING, handler=on_detect)
