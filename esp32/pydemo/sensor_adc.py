# 电位器传感器
# 霍尔传感器
# 模拟温度传感器 
# 光敏传感器
# 火焰报警器

from machine import Pin, ADC
from time import sleep_ms

adc = ADC(Pin(2))
adc.atten(ADC.ATTN_11DB) # 11dB 衰减

v = adc.read() >> 4

while True:
    now = adc.read() >> 4
    if now != v:
        v = now
        print(v)
    sleep_ms(100)