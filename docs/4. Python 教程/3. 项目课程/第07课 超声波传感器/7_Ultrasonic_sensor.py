'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第07课
超声波传感器
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000)
mecanumCar = mecanumCar_v2.Driver(i2c) 

while True:
    distance = mecanumCar.get_distance()
    print("distance is : {} cm".format(distance))
    time.sleep_ms(100)