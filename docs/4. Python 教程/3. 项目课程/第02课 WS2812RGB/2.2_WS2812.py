'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第02.2课
WS2812
'''

from machine import Pin,I2C
import mecanumCar_v2
import time
import random

#创建一个用于控制小车类,名为mecanumCar
i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000)
mecanumCar = mecanumCar_v2.Driver(i2c)


# 主循环函数
while True:
    r = random.randint(0, 255) #从0~255直接取随机数
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    for i in range(4):
        mecanumCar.pixels_set(i, (r, g, b)) #第i+1个灯珠颜色为随机(r,g,b)
        mecanumCar.pixels_show() #刷新显示
        time.sleep(0.1) #等待一会儿