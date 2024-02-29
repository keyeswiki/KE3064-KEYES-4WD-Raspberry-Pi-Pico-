'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第12课
APP Test
'''

from machine import Pin,UART,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000) #iic0 sda-->20,scl-->21
mecanumCar = mecanumCar_v2.Driver(i2c) #创建麦克纳姆轮小车驱动类实例

#设置蓝牙串口波特率为9600，8位数据位，无校验位，1位停止位，tx-->GPIO0,rx-->GPIO1
uart = UART(0,baudrate = 9600,bits = 8,parity = None,stop = 1,tx = machine.Pin(0),rx = machine.Pin(1))
buf=bytearray(6) #定义一个串口接收缓冲区


# 主循环函数
while True:
    if uart.any():
        uart.readinto(buf)
        #print(buf.decode())
        ble_val = chr(buf[0]) #打印接收到的第一个字符
        print(ble_val)