# KY-039 手指测试心跳传感
# 没有手指时，数值是个稳定小范围波动值；
# 手指靠近时，会随心率慢慢上下起伏波动。

from machine import ADC
from time import sleep
print('a')

adc = ADC(0)

while True:
    v = adc.read()
    print(f'{v}')
    sleep(0.01)