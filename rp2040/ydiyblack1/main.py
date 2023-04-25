from time import sleep
from device.led_rgb import LedRGB

led = LedRGB()
led.on(r=1, g=1,b=1)
sleep(1)
led.off()
