'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第01课
七彩灯闪烁
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000) #iic0 sda-->20,scl-->21
mecanumCar = mecanumCar_v2.Driver(i2c) #创建麦克纳姆轮小车驱动类实例


# 主循环函数
while True:
    mecanumCar.right_led(1) #开启右边七彩灯闪烁
    mecanumCar.left_led(1)  #开启左边七彩灯闪烁
    time.sleep(3)           #延时3秒
    mecanumCar.right_led(0) #关闭右边七彩灯闪烁
    mecanumCar.left_led(0)  #关闭左边七彩灯闪烁
    time.sleep(1)           #延时秒