'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第03课
舵机转动
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000)
#print("STC8G1K08 address：", machine.I2C.scan(i2c))
mecanumCar = mecanumCar_v2.Driver(i2c)

mecanumCar.set_angle(90) #转动到90度
time.sleep(1)

# 主循环函数
while True:
    for i in range(180):
        mecanumCar.set_angle(i) #从0转动到180度
        time.sleep_ms(20) #等待一会儿，不让它转动得那么快
    for i in range(180):
        mecanumCar.set_angle(180-i) #从180转动到0度
        time.sleep_ms(20) #等待一会儿，不让它转动得那么快