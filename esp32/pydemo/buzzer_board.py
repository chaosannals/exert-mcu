# 开发板上蜂鸣器

from machine import Pin
from time import sleep

pin = Pin(2, Pin.OUT)
pin.value(1)

for i in range(10):
    pin.value(0)
    sleep(1)
    pin.value(1)
