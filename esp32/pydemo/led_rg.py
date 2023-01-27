# 双色 LED 红绿

from machine import Pin
from time import sleep

rpin = Pin(2, Pin.OUT)
gpin = Pin(4, Pin.OUT)

while True:
    rpin.value(1)
    gpin.value(0)
    sleep(1)
    rpin.value(0)
    gpin.value(1)
    sleep(1)
     