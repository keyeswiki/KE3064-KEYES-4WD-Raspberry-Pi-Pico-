'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第08课
超声波跟随车
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000) #iic0 sda-->20,scl-->21
mecanumCar = mecanumCar_v2.Driver(i2c) #创建麦克纳姆轮小车驱动类实例

while True:
    distance = mecanumCar.get_distance()
    if distance < 15:
        mecanumCar.Back()
    elif distance < 25:
        mecanumCar.stop()
    elif distance < 45:
        mecanumCar.Advance()
    else:
        mecanumCar.stop()