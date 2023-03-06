# 陀螺仪

from machine import I2C, Pin
from mpu6050 import MPU6050
from time import sleep, ticks_us, ticks_diff
from math import sqrt, asin

imu = MPU6050(I2C(0, sda=Pin(19), scl=Pin(18), freq=400000))
imu.sample_rate = 39 # g: 8000Hz / (1 + 39) = 200Hz  a: 1000Hz / (1 + 39) = 25Hz
# imu.accel_range = 0 # ±2g 16bit
# imu.accel_range = 1 # ±4g 16bit 
imu.gyro_range = 0 # 250°/s 16bit

gx = 0
gy = 0
gz = 0
while True:
    # TODO 计算位移和转向
    ax = imu.accel.x
    ay = imu.accel.y
    az = imu.accel.z
    
    vx = ax
    vy = ay
    vz = az
    
    # 静止时 a 约等于 1 ， 1 代表 1g 正好是重力加速度。
    a = sqrt(ax * ax + ay * ay + az * az)
    
    gx += imu.gyro.x
    gy += imu.gyro.y
    gz += imu.gyro.z
    tem = round(imu.temperature, 2)
    
    gdim = sqrt(gx*gx + gy*gy + gz*gz)
    gax = asin(gx / gdim)
    gay = asin(gy / gdim)
    gaz = asin(gz / gdim)
    g = sqrt(gax * gax + gay * gay + gz * gz)
    
    
    print(f'a: {a} g: {g} v:({vx},{vy},{vz}) g:({gax},{gay},{gaz}) t: {tem}')
    sleep(0.2)
    