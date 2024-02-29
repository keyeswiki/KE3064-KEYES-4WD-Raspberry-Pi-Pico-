'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第06课
循迹智能车
'''

from machine import Pin,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000)
#print("STC8G1K08 address：", machine.I2C.scan(i2c))
mecanumCar = mecanumCar_v2.Driver(i2c)

l_pin = Pin(16, Pin.IN)
m_pin = Pin(17, Pin.IN)
r_pin = Pin(18, Pin.IN)


while True:
    l_val = l_pin.value()
    m_val = m_pin.value()
    r_val = r_pin.value()
    if m_val == 1:
        if l_val == 1 and r_val == 0:
            mecanumCar.Turn_Left()
        elif l_val == 0 and r_val == 1:
            mecanumCar.Turn_Right()
        else:
            mecanumCar.Advance()
    else:
        if l_val == 1 and r_val == 0:
            mecanumCar.Turn_Left()
        elif l_val == 0 and r_val == 1:
            mecanumCar.Turn_Right()
        else:
            mecanumCar.stop()
