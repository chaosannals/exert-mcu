from machine import Pin
from time import sleep

pin_leds = [Pin(gp, Pin.OUT) for gp in [16,17,18,19,23,5, 2, 4]]

#print('start')
for pin in pin_leds:
    pin.value(1)
    sleep(0.4)
    pin.value(0)
    sleep(0.4)
#print('stop')