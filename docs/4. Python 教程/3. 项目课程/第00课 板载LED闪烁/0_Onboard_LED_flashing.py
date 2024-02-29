from machine import Pin
import time

led = Pin(25, Pin.OUT)   # 从引脚25创建LED对象，设置引脚25为输出

try:
    while True:
        led.value(1)    # 设置led开启
        time.sleep(0.5) # 延时 0.5s
        led.value(0)    # 设置led 关闭
        time.sleep(0.5) # 延时 0.5s
except:
    pass