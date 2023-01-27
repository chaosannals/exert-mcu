# 雨滴传感器 5V
# LM393

from machine import Pin, ADC
from time import sleep

adc = ADC(Pin(2))
pin = Pin(4, Pin.IN, Pin.PULL_UP)

adc.atten(ADC.ATTN_11DB)

dv = 0
print('start')
while True:
    av = adc.read()
    nv = pin.value()
    if nv != dv:
        print(f'a: {av} d: {dv}')
        dv = nv
    sleep(0.2)