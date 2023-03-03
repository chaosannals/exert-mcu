# 操纵杆

from machine import Pin, ADC
from time import sleep

x_adc = ADC(Pin(2))
x_adc.atten(ADC.ATTN_11DB)
y_adc = ADC(Pin(4))
y_adc.atten(ADC.ATTN_11DB)
b_pin = Pin(5, Pin.IN, Pin.PULL_UP)

b = 0
x_tmp = 0
y_tmp = 0
while True:
    x = x_adc.read() >> 8
    y = y_adc.read() >> 8
    
    b_now = b_pin.value()
    if b != b_now:
        b = b_now
        print(f'b: {b} ({x},{y})')
        
    if x_tmp != x or y_tmp != y:
        x_tmp = x
        y_tmp = y
        print(f'({x},{y})')
    

