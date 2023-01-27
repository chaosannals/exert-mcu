# 开发板上 LM393
# 传感器插槽

from machine import Pin
from time import sleep

pin = Pin(2, Pin.IN)

status = 1
while True:
    now_status = pin.value()
    if status != now_status:
        print(now_status)
        status = now_status
    sleep(0.2)