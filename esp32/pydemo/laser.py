# 激光传感器

from machine import Pin
from time import sleep

pin = Pin(2, Pin.OUT)

while True:
    pin.value(1)
    sleep(1)
    pin.value(0)
    sleep(1)
    