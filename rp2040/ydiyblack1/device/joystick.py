from machine import Pin, ADC
from time import sleep

x_axis = ADC(0)
y_axis = ADC(3)

while True:
    x = x_axis.read_u16() #/ 0xFFFF * 0xF
    y = y_axis.read_u16() #/ 0xFFFF * 0xF
    print(f' ({x},{y})')
    sleep(1)