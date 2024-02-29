# 第13课 蓝牙APP控制智能车
![Img](./media/813bf5af11dc62c669956b79c020dfe2.png)

## 1. 实验说明：                                                                                
在上一课程中，我们已经介绍了蓝牙APP的使用和各按钮的功能，并且通过蓝牙APP连接蓝牙来读取了APP界面上各按钮发送的控制字符，在本课程中，主要是通过蓝牙APP连接蓝牙实现APP控制4WD智能车的多种功能。

## 2. 添加库文件：
首先我们先确保安装了库文件，不然代码会编译出错，这里我们用到库文件“<span style="color: rgb(255, 76, 65);">mecanumCar_v2.py</span>”，如何添加库文件请参考“<span style="color: rgb(0, 209, 0);">开发环境配置</span>”文件。如果库文件已经添加好了，就跳过这一步骤。
![Img](./media/4718fb48b0169a0e4958c2e4aed013df.png)

## 3. 实验代码：
本教程中使用的代码保存在：“**..\4. Python 教程\3. 项目课程**” 的路径中。你可以把代码移到任何地方。例如，我们将代码保存在**D盘**中，<span style="color: rgb(0, 209, 0);">路径为D:\3. 项目课程</span>。
![Img](./media/92103adf9654c97f49aea829c933d86f.png)

打开“**Thonny**”软件，点击“**此电脑**”→“**D:**”→“**3. 项目课程**”→“**第13课 蓝牙APP控制智能车**”，然后鼠标左键双击“**11_IRremote_Control_Robot.py**”。
![Img](./media/bbc57ba9c6f0454936c220cc64757e0e.png)

```
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
                    
```
<span style="color: rgb(255, 76, 65);">上传代码之前，确保蓝牙模块已经从扩展板上拔下来，否则会导致代码上传不成功。</span>

## 5. 实验结果：                                                                                
确保Raspberry Pi Pico主板已经连接到电脑上，单击“![Img](./media/555a25f055ba1b4c56ee4c3a28ffe5af.png)”。
![Img](./media/41ca97271673e1163db3a5a08916b7bb.png)

安上电池，将电机驱动底板上的电源拨码开关拨到ON一端，开启电源。单击“![Img](./media/5c05febdb56bb5ef370e897c012c1b91.png)”，代码开始执行。
![Img](./media/481210d88392548239367d7cdc673419.png)
插上蓝牙，注意蓝牙不要插反了。就可以使用手机APP来控制如下玩法。（<span style="color: rgb(255, 76, 65);">有关APP具体的下载安装方法及使用方法，请参考**第12课 读取蓝牙数据** </span>）
<span style="color: rgb(255, 76, 65);">注意：</span>当我们断电后重新上电不会继续运行此代码，除非我们把代码以<span style="color: rgb(255, 76, 65);">**main\.py**</span>命名保存在Raspberry Pi Pico主板上！
（1）点击![Img](./media/49fd9134c59222bca61663c5c0044f84.png)开启七彩灯，再次点击这个按钮七彩灯就会关闭。
（2）点击![Img](./media/dc90304902e357572904ce5fc4218cad.png)会进入循迹模式，当想退出该模式时，再次点击该按钮。
（3）点击![Img](./media/fd5794661a1b87dbd39a068f05ca2342.png)会进入跟随模式、当想退出该模式时，再次点击该按钮。
（4）点击![Img](./media/b9521925d663bc37a7534a9e155c3550.png)会进入避障模式，当想退出该模式时，再次点击该按钮。
（5）![Img](./media/01dd10330fbff2f211105024590a3960.png)拉动这两个条幅回改变左边两个电机的速度，右边也是相同的操作方法。
（6）![Img](./media/aa0e44fd88c5480215c77c363e75f61b.png)这几个按钮是用来切换底板下面4个2812灯珠颜色的，中间按钮为关闭功能。
（7）剩下其他的按钮全都是用来操控小车行驶的，跟其他按钮不同的是，这些按钮当我们按下时小车行驶，松开按钮时小车停止。
![Img](./media/92673ed92eba02ed1662b20ab7fc4434.png)

<span style="color: rgb(255, 76, 65);">注意：</span>![Img](./media/e6ef2d7df8bfa993aa70ae3e70434fc9.png)是用来进行调速的，当进行调速时，应该拖动拉条![Img](./media/6063628aa960f2d988c2a6ee4c564397.png)；不能点击![Img](./media/6063628aa960f2d988c2a6ee4c564397.png)，如果点击的话可能调速不成功。

## 6. 代码说明:
|from machine import UART|导入UART串口模块才能使用串口功能 |
| :--: | :--: |
|uart = UART(0,baudrate = 9600,bits = 8,parity = None,stop = 1,tx = machine.Pin(0),rx = machine.Pin(1))|创建一个串口示例，设置串口为0，波特率为9600,8位数据位，一位停止位，无校验位，串口引脚为0和1 |
|buf=bytearray(6)|定义一个串口接收缓冲区，可存放6个字节|
|if uart.any():| 如果接收到数据 |
|uart.readinto(buf)|将数据读到buf中 |
|ble_val = chr(buf[0])|将buf中的第一个字节转成字符格式，赋给ble_val|
|print(ble_val)|打印ble_val这个字符|
|def map(value, fromLow, fromHigh, toLow, toHigh):|定义一个映射函数，用来将APP上的0 ~ 100映射到0 ~ 255的范围|
|mecanumCar.set_speed(speed_Upper_L = speed_temp)|电机速度设置函数，可分别设置4个参数：speed_Upper_L，speed_Lower_L，speed_Upper_R，speed_Lower_R|

