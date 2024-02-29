'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第05课
循迹传感器
'''

from machine import Pin
import time

l_pin = Pin(16, Pin.IN)
m_pin = Pin(17, Pin.IN)
r_pin = Pin(18, Pin.IN)


while True:
    l_val = l_pin.value() #读取左边巡线传感器的值
    m_val = m_pin.value() #读取中间巡线传感器的值
    r_val = r_pin.value() #读取右边巡线传感器的值
    print(l_val, end = ' ')
    print(m_val, end = ' ')
    print(r_val)
    time.sleep_ms(100)