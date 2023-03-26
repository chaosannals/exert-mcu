from time import sleep
from device.led_rgb import LedRGB

led = LedRGB()
led.on(g=0,b=0)
sleep(2)
led.on(r=0,b=0)
sleep(2)
led.on(r=0,g=0)
sleep(2)
led.off()
