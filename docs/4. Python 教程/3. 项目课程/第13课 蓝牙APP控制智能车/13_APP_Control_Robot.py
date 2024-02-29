'''
KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
第13课
APP 控制智能车
'''

from machine import Pin,UART,I2C
import mecanumCar_v2
import time

i2c = I2C(0, sda = Pin(20), scl = Pin(21), freq = 400000) #iic0 sda-->20,scl-->21
#print("STC8G1K08 address：", machine.I2C.scan(i2c))
mecanumCar = mecanumCar_v2.Driver(i2c) #创建麦克纳姆轮小车驱动类实例

#设置蓝牙串口波特率为9600，8位数据位，无校验位，1位停止位，tx-->GPIO0,rx-->GPIO1
uart = UART(0,baudrate = 9600,bits = 8,parity = None,stop = 1,tx = machine.Pin(0),rx = machine.Pin(1))
buf=bytearray(6) #定义一个串口接收缓冲区


l_pin = Pin(16, Pin.IN)
m_pin = Pin(17, Pin.IN)
r_pin = Pin(18, Pin.IN)


def map(value, fromLow, fromHigh, toLow, toHigh):
    return (toHigh-toLow)*(value-fromLow) // (fromHigh-fromLow) + toLow


# 循迹
def Line_Tracking():
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
        if uart.any():
            uart.readinto(buf)
            ble_val = chr(buf[0])
            if ble_val == 's':
                mecanumCar.stop()
                break

# 超声波跟随
def ult_following():
    while True:
        distance = mecanumCar.get_distance()
        if distance <= 15:
            mecanumCar.Back()
        elif distance <= 25:
            mecanumCar.stop()
        elif distance <= 45:
            mecanumCar.Advance()
        else:
            mecanumCar.stop()
        if uart.any():
            uart.readinto(buf)
            ble_val = chr(buf[0])
            if ble_val == 's':
                mecanumCar.stop()
                break


# 超声波避障
def ult_avoiding():
    while True:
        distance = mecanumCar.get_distance()
        if distance <= 15:
            mecanumCar.stop()
            time.sleep(0.5)
            mecanumCar.set_angle(180)
            time.sleep(0.5)
            l_distance = mecanumCar.get_distance()
            time.sleep(0.1)
            mecanumCar.set_angle(0)
            time.sleep(0.5)
            r_distance = mecanumCar.get_distance()
            time.sleep(0.1)
            mecanumCar.set_angle(90)
            time.sleep(0.5)
            if l_distance > r_distance:
                mecanumCar.Turn_Left()
                time.sleep(0.3)
            else:
                mecanumCar.Turn_Right()
                time.sleep(0.3)
        else:
            mecanumCar.Advance()
        
        if uart.any():
            uart.readinto(buf)
            ble_val = chr(buf[0])
            if ble_val == 's':
                mecanumCar.stop()
                break

# 2812灯珠显示
color_num = 0
def showColor():
    global color_num
    if color_num > 6:
        color_num = 0
    if color_num < 0:
        color_num = 6
    if color_num == 0:
        mecanumCar.pixels_fill((255, 0, 0))
        #mecanumCar.pixels_show()
    elif color_num == 1:
        mecanumCar.pixels_fill((255, 80, 0))
        #mecanumCar.pixels_show()
    elif color_num == 2:
        mecanumCar.pixels_fill((255, 255, 0))
        #mecanumCar.pixels_show()
    elif color_num == 3:
        mecanumCar.pixels_fill((0, 255, 0))
        #mecanumCar.pixels_show()
    elif color_num == 4:
        mecanumCar.pixels_fill((0, 0, 255))
        #mecanumCar.pixels_show()
    elif color_num == 5:
        mecanumCar.pixels_fill((0, 255, 255))
        #mecanumCar.pixels_show()
    elif color_num == 6:
        mecanumCar.pixels_fill((160, 32, 240))
        #mecanumCar.pixels_show()
    mecanumCar.pixels_show()


mecanumCar.set_angle(90) #初始舵机角度为90度
time.sleep(1)
# 主循环函数
while True:
    if uart.any(): #判断串口接收是否有数据
        uart.readinto(buf)
        #print(buf.decode())
        ble_val = chr(buf[0])
        print(ble_val)
        if ble_val == 's':
            mecanumCar.stop()
        elif ble_val == 'a':
            mecanumCar.Advance()
        elif ble_val == 'c':
            mecanumCar.Back()
        elif ble_val == 'd':
            mecanumCar.Turn_Right()
        elif ble_val == 'b':
            mecanumCar.Turn_Left()
        elif ble_val == 'k':
            mecanumCar.L_Move()
        elif ble_val == 'h':
            mecanumCar.R_Move()
        elif ble_val == 'l':
            mecanumCar.LU_Move()
        elif ble_val == 'j':
            mecanumCar.LD_Move()
        elif ble_val == 'g':
            mecanumCar.RU_Move()
        elif ble_val == 'i':
            mecanumCar.RD_Move()
        elif ble_val == 'e':
            mecanumCar.drift_left()
        elif ble_val == 'f':
            mecanumCar.drift_right()
        elif ble_val == 't':
            mecanumCar.left_led(1)
            mecanumCar.right_led(1)
        elif ble_val == 'u':
            mecanumCar.left_led(0)
            mecanumCar.right_led(0)
        elif ble_val == 'p':
            Line_Tracking()
        elif ble_val == 'q':
            ult_following()
        elif ble_val == 'r':
            ult_avoiding()
        elif ble_val == 'm':
            color_num += 1
            showColor()
        elif ble_val == 'n':
            color_num -= 1
            showColor()
        elif ble_val == 'o':
            mecanumCar.pixels_fill((0, 0, 0))
            mecanumCar.pixels_show()   
        
        #  下面是速度调节，稍微复杂一点，格式分两次发送 例如为：
        #  v#
        #  50#
        #  所以我们需要先读第一个字符，第二次再读数值

        elif ble_val == 'v': #第一次读到v，是左前方电机
            speed_temp = 0
            flag = 1
            while flag == 1:
                if uart.any(): #再次判断是否有数据
                    uart.readinto(buf) #再次读取到buf
                    for i in buf:
                        if chr(i) == '#': #遇到'#'停止读取
                            flag = 0
                            break
                        else:
                            speed_temp = speed_temp * 10 + (i-48)  #将数字字符转为整数
                    speed_temp = map(speed_temp, 0, 100, 0, 255) #将数值从0~100映射到0~255
                    #print("speed_Upper_L = ", speed_temp) #调试输出
                    mecanumCar.set_speed(speed_Upper_L = speed_temp) #更新左前方电机速度
        
        elif ble_val == 'x':
            speed_temp = 0
            flag = 1
            while flag == 1:
                if uart.any():
                    uart.readinto(buf)
                    for i in buf:
                        if chr(i) == '#':
                            flag = 0
                            break
                        else:
                            speed_temp = speed_temp * 10 + (i-48)
                    speed_temp = map(speed_temp, 0, 100, 0, 255)
                    #print("speed_Upper_R = ", speed_temp)
                    mecanumCar.set_speed(speed_Upper_R = speed_temp)
                
        elif ble_val == 'w':
            speed_temp = 0
            flag = 1
            while flag == 1:
                if uart.any():
                    uart.readinto(buf)
                    for i in buf:
                        if chr(i) == '#':
                            flag = 0
                            break
                        else:
                            speed_temp = speed_temp * 10 + (i-48)
                    speed_temp = map(speed_temp, 0, 100, 0, 255)
                    #print("speed_Lower_L = ", speed_temp)
                    mecanumCar.set_speed(speed_Lower_L = speed_temp)
        
        elif ble_val == 'y':
            speed_temp = 0
            flag = 1
            while flag == 1:
                if uart.any():
                    uart.readinto(buf)
                    for i in buf:
                        if chr(i) == '#':
                            flag = 0
                            break
                        else:
                            speed_temp = speed_temp * 10 + (i-48)
                    speed_temp = map(speed_temp, 0, 100, 0, 255)
                    #print("speed_Lower_R = ", speed_temp)
                    mecanumCar.set_speed(speed_Lower_R = speed_temp)
                    