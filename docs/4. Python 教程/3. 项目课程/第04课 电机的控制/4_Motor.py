'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第04课
电机的控制
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000) #iic0 sda-->20,scl-->21
mecanumCar = mecanumCar_v2.Driver(i2c) #创建麦克纳姆轮小车驱动类实例

# 主循环函数
while True:
  mecanumCar.Advance()
  time.sleep(2)           #等待2秒
  
  mecanumCar.Back()       #后退
  time.sleep(2)
  
  mecanumCar.Turn_Left(); #左转
  time.sleep(2)

  mecanumCar.Turn_Right() #右转
  time.sleep(2)

  mecanumCar.stop();      #停止
  time.sleep(1)
