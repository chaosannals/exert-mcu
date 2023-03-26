from machine import Pin, PWM
from time import sleep

class LedRGB:
    def __init__(self, pin_r=5, pin_g=4, pin_b=1):
        '''
        RGB
        '''
        self.pwm_red = PWM(Pin(pin_r))
        self.pwm_green = PWM(Pin(pin_g))
        self.pwm_blue = PWM(Pin(pin_b))
        
        self.pwm_red.freq(2000)
        self.pwm_green.freq(2000)
        self.pwm_blue.freq(5000)
        
    def off(self):
        self.pwm_red.duty_u16(0)
        self.pwm_green.duty_u16(0)
        self.pwm_blue.duty_u16(0)
        
    def on(self, r=0xffff, g=0xffff, b=0xffff):
        self.pwm_red.duty_u16(r)
        self.pwm_green.duty_u16(g)
        self.pwm_blue.duty_u16(b)
        
def test():
    led = LedRGB()
    led.on(g=0,b=0)
    sleep(2)
    led.on(r=0,b=0)
    sleep(2)
    led.on(r=0,g=0)
    sleep(2)
    led.off()
        
if '__main__' == __name__:
    test()
        
        