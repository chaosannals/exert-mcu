# LED RGB 灯 PWM

from machine import Pin, PWM
from time import sleep

rpin = PWM(Pin(2))
gpin = PWM(Pin(4))
bpin = PWM(Pin(5))

rpin.freq(2000)
gpin.freq(1999)
bpin.freq(5000)

def from_ff_to_3ff(v):
    return int(v * 0x3ff / 0xff)

colors = [
    0x000000,
    0xff0000,
    0x00ff00,
    0x0000ff,
    0xffff00,
    0xff00ff,
    0x00ffff,
    0xffffff,
]

while True:
    for c in colors:
        r = from_ff_to_3ff((c & 0xff0000) >> 16)
        g = from_ff_to_3ff((c & 0x00ff00) >> 8)
        b = from_ff_to_3ff(c & 0x0000ff)
        rpin.duty(r)
        gpin.duty(g)
        bpin.duty(b)
        sleep(1)