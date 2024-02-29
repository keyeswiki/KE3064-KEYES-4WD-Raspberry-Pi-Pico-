'''
STC8G1K0B PWM OUT
WS2812
colorfur light
ultrasonic
FOR KEYES MECANUMCAR_V2(RASPBERRY PI PICO)
2023/5/15
'''
from machine import Pin, time_pulse_us,PWM
import array, time
import rp2

trigger = Pin(3, Pin.OUT)
echo = Pin(4, Pin.IN)

servo = PWM(Pin(2))#舵机引脚接GP2
servo.freq(50)#20ms的周期，所以频率为50Hz

# 设置伺服马达的转动角度
def setServoCycle (position):
    servo.duty_u16(position)
    #time.sleep(0.01)

# 将转动角度换算成占空比
def convert(x, i_m, i_M, o_m, o_M):
    return max(min(o_M, (x - i_m) * (o_M - o_m) // (i_M - i_m) + o_m), o_m)

@rp2.asm_pio(sideset_init=rp2.PIO.OUT_LOW, out_shiftdir=rp2.PIO.SHIFT_LEFT, autopull=True, pull_thresh=24)
def sk6812():
    T1 = 2
    T2 = 5
    T3 = 3
    wrap_target()
    label("bitloop")
    out(x, 1)               .side(0)    [T3 - 1]
    jmp(not_x, "do_zero")   .side(1)    [T1 - 1]
    jmp("bitloop")          .side(1)    [T2 - 1]
    label("do_zero")
    nop()                   .side(0)    [T2 - 1]
    wrap()
 

# Create the StateMachine with the sk6812 program, outputting on Pin(7).
sm = rp2.StateMachine(0, sk6812, freq=8_000_000, sideset_base=Pin(7))
 
# Start the StateMachine, it will wait for data on its FIFO.
sm.active(1)

# Configure the number of sk6812 LEDs.
NUM_LEDS = 4
# Display a pattern on the LEDs via an array of LED RGB values.
ar = array.array("I", [0 for _ in range(NUM_LEDS)])


class Driver(object):
    """Driver for the STC8G1K08"""
    def __init__(self, i2c, addr=0x30):
        self.i2c = i2c
        self.addr = addr
        self.brightness = 0.1
        self.speed_Upper_L = 80
        self.speed_Lower_L = 80
        self.speed_Upper_R = 80
        self.speed_Lower_R = 80
        #time.sleep(1)
    # 设置舵机角度
    def set_angle(self, angle):
        '''
        角度对应的占空比
        0°----2.5%----1638
        45°----5%----3276
        90°----7.5%----4915
        135°----10%----6553
        180°----12.5%----8192
        将占空比定在1638~8192，这样可以顺利转动0~180度
        '''
        pos = convert(angle, 0, 180, 1638, 8192)
        setServoCycle(pos)
        
    # 设置灯珠亮度
    def set_brightness(self, brightness=None):
        if brightness is None:
            return self.brightness
        self.brightness = brightness
        self.pixels_show()
    # 刷新灯珠显示
    def pixels_show(self):
        dimmer_ar = array.array("I", [0 for _ in range(NUM_LEDS)])
        for i,c in enumerate(ar):
            r = int(((c >> 8) & 0xFF) * self.brightness)
            g = int(((c >> 16) & 0xFF) * self.brightness)
            b = int((c & 0xFF) * self.brightness)
            dimmer_ar[i] = (g<<16) + (r<<8) + b
        sm.put(dimmer_ar, 8)
        time.sleep_ms(10)
    # 设置某颗灯珠
    def pixels_set(self, i, color):
        ar[i] = (color[1]<<16) + (color[0]<<8) + color[2]
    # 设置4颗灯珠
    def pixels_fill(self, color):
        for i in range(len(ar)):
            self.pixels_set(i, color)
    # 设置速度
    def set_speed(self, speed_Upper_L = None, speed_Lower_L = None, speed_Upper_R = None, speed_Lower_R = None):
        if speed_Upper_L is None:
            pass
        else:
            self.speed_Upper_L = speed_Upper_L
        
        if speed_Lower_L is None:
            pass
        else:
            self.speed_Lower_L = speed_Lower_L
        
        if speed_Upper_R is None:
            pass
        else:
            self.speed_Upper_R = speed_Upper_R
        
        if speed_Lower_R is None:
            pass
        else:
            self.speed_Lower_R = speed_Lower_R
    # 停止
    def stop(self):
        self.Motor_Upper_L(1, 0)
        self.Motor_Lower_L(1, 0)
        self.Motor_Upper_R(1, 0)
        self.Motor_Lower_R(1, 0)
    # 前进
    def Advance(self):
        self.Motor_Upper_L(1, self.speed_Upper_L)
        self.Motor_Lower_L(0, self.speed_Lower_L)
        self.Motor_Upper_R(1, self.speed_Upper_R)
        self.Motor_Lower_R(0, self.speed_Lower_R)
    # 后退
    def Back(self):
        self.Motor_Upper_L(0, self.speed_Upper_L)
        self.Motor_Lower_L(1, self.speed_Lower_L)
        self.Motor_Upper_R(0, self.speed_Upper_R)
        self.Motor_Lower_R(1, self.speed_Lower_R)
    # 左旋转
    def Turn_Left(self):
        self.Motor_Upper_L(1, self.speed_Upper_L)
        self.Motor_Lower_L(1, self.speed_Lower_L)
        self.Motor_Upper_R(0, self.speed_Upper_R)
        self.Motor_Lower_R(0, self.speed_Lower_R)
    # 右旋转
    def Turn_Right(self):
        self.Motor_Upper_L(0, self.speed_Upper_L)
        self.Motor_Lower_L(0, self.speed_Lower_L)
        self.Motor_Upper_R(1, self.speed_Upper_R)
        self.Motor_Lower_R(1, self.speed_Lower_R)
    # 左移
    def L_Move(self):
        self.Motor_Upper_L(1, self.speed_Upper_L)
        self.Motor_Lower_L(0, self.speed_Lower_L)
        self.Motor_Upper_R(0, self.speed_Upper_R)
        self.Motor_Lower_R(1, self.speed_Lower_R)
    # 右移
    def R_Move(self):
        self.Motor_Upper_L(0, self.speed_Upper_L)
        self.Motor_Lower_L(1, self.speed_Lower_L)
        self.Motor_Upper_R(1, self.speed_Upper_R)
        self.Motor_Lower_R(0, self.speed_Lower_R)
    # 左上移
    def LU_Move(self):
        self.Motor_Upper_L(1, 0)
        self.Motor_Lower_L(1, self.speed_Lower_L)
        self.Motor_Upper_R(1, self.speed_Upper_R)
        self.Motor_Lower_R(0, 0)
    # 左下移
    def LD_Move(self):
        self.Motor_Upper_L(0, self.speed_Upper_L)
        self.Motor_Lower_L(1, 0)
        self.Motor_Upper_R(1, 0)
        self.Motor_Lower_R(0, self.speed_Lower_R)
    # 右上移
    def RU_Move(self):
        self.Motor_Upper_L(1, self.speed_Upper_L)
        self.Motor_Lower_L(0, 0)
        self.Motor_Upper_R(0, 0)
        self.Motor_Lower_R(1, self.speed_Lower_R)
    # 右下移
    def RD_Move(self):
        self.Motor_Upper_L(0, 0)
        self.Motor_Lower_L(1, self.speed_Lower_L)
        self.Motor_Upper_R(1, self.speed_Upper_R)
        self.Motor_Lower_R(0, 0)
    # 向左漂移
    def drift_left(self):
        self.Motor_Upper_L(0, 0)
        self.Motor_Lower_L(0, self.speed_Lower_L)
        self.Motor_Upper_R(0, 0)
        self.Motor_Lower_R(1, self.speed_Lower_R)
    # 向右漂移
    def drift_right(self):
        self.Motor_Upper_L(0, 0)
        self.Motor_Lower_L(1, self.speed_Lower_L)
        self.Motor_Upper_R(0, 0)
        self.Motor_Lower_R(0, self.speed_Lower_R)
    
    # 七彩灯
    def left_led(self, state):
        self.set_pwm(0x0A, state)

    def right_led(self, state):
        self.set_pwm(0x09, state)
    
    # 左前方电机
    def Motor_Upper_L(self, stateL, left1):
        if (stateL == 1):
            self.set_pwm(1, 0)
            self.set_pwm(2, left1)
        elif (stateL == 0):
            self.set_pwm(1, left1)
            self.set_pwm(2, 0)
    # 左后方电机
    def Motor_Lower_L(self, stateL, left1):
        if (stateL == 1):
            self.set_pwm(8, 0)
            self.set_pwm(7, left1)
        elif (stateL == 0):
            self.set_pwm(8, left1)
            self.set_pwm(7, 0)
    # 右前方电机
    def Motor_Upper_R(self, stateR, right1):
        if (stateR == 1):
            self.set_pwm(3, 0)
            self.set_pwm(4, right1)
        elif (stateR == 0):
            self.set_pwm(3, right1)
            self.set_pwm(4, 0)
    # 右后方电机
    def Motor_Lower_R(self, stateR, right1):
        if (stateR == 1):
            self.set_pwm(6, 0)
            self.set_pwm(5, right1)
        elif (stateR == 0):
            self.set_pwm(6, right1)
            self.set_pwm(5, 0)
    
    def set_pwm(self, channel, value):
        self.i2c.writeto_mem(self.addr, channel, bytearray([value & 0xFF]))
    
    # 超声波
    def get_distance(self):
        trigger.value(0)
        time.sleep_us(2)
        trigger.value(1)
        time.sleep_us(10)
        trigger.value(0)

        t = time_pulse_us(echo,1,35000)
        if (t <= 0 and self.lastEchoDuration >= 0) :
            t = self.lastEchoDuration

        self.lastEchoDuration = t
        return round(t * 0.013)