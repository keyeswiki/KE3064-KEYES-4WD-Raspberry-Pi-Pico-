'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第02.1课
WS2812
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

#创建一个用于控制小车类,名为mecanumCar
i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000)
mecanumCar = mecanumCar_v2.Driver(i2c)

mecanumCar.pixels_set(0, (255, 0, 0))
mecanumCar.pixels_set(1, (0, 255, 0))
mecanumCar.pixels_set(2, (0, 0, 255))
mecanumCar.pixels_set(3, (255, 255, 255))
mecanumCar.pixels_show()