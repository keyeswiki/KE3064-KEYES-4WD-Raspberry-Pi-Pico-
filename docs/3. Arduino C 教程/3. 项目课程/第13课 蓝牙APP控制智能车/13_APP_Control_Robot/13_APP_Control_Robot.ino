/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第13课
  蓝牙APP控制智能车
*/

#include "MecanumCar_v2.h"
#include "rgb.h"
#include "ir.h"
#include "Servo.h"

mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21
RGB rgb(7, 4);  //rgb(pin, num);  num = 0-100
Servo myservo;
IR IRreceive(6);//红外接收接GP6

/*******超声波传感器接口*****/
#define EchoPin  4  //ECHO引脚连接到GPIO4
#define TrigPin  3  //TRIG引脚连接到GPIO3

/*******循迹传感器引脚定义**********/
#define SensorLeft    16   //左循迹传感器输入引脚
#define SensorMiddle  17   //中间循迹传感器输入引脚
#define SensorRight   18   //右循迹传感器输入引脚

String speed_str;
int color_num = 0;
char ble_val;

void setup() {
  /*蓝牙串口默认设置为UART0,TX为GPIO0*/
  /*蓝牙串口默认设置为UART0,RX为GPIO1*/
  Serial1.begin(9600);  //设置蓝牙串波特率为9600

  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式

  /****循迹传感器接口全部设置为输入模式***/
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);

  myservo.attach(2);  // 舵机连接到 GPIO2
  myservo.write(90);
  delay(500);

  rgb.setBrightness(100);  //rgb亮度(0-255);
  delay(10);
  rgb.clear();  //关闭所有灯
  delay(10);
  rgb.show();

  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  int key = IRreceive.getKey();
  if (key != -1) {
    //Serial.println(key);
    switch (key)
    {
      case 64: mecanumCar.Stop();       break;  //停止
      case 70: mecanumCar.Advance();    break;  //前进
      case 21: mecanumCar.Back();       break;  //后退
      case 68: mecanumCar.Turn_Left();  break;  //左转
      case 67: mecanumCar.Turn_Right(); break;  //右转
    }
  }
  if (Serial1.available())//如果接收缓冲区非空
  {
    ble_val = Serial1.read();//读取蓝牙数据
    Serial.println(ble_val);//串口打印读取到的数据
    switch (ble_val)
    {
      /*********************小车行驶************************/
      case 's': mecanumCar.Stop();       break;  //停止
      case 'a': mecanumCar.Advance();    break;  //前进
      case 'c': mecanumCar.Back();       break;  //后退
      case 'b': mecanumCar.Turn_Left();  break;  //左转
      case 'd': mecanumCar.Turn_Right(); break;  //右转
      case 'k': mecanumCar.L_Move();     break;  //左移
      case 'h': mecanumCar.R_Move();     break;  //右移
      case 'l': mecanumCar.LU_Move();    break;  //左上移
      case 'j': mecanumCar.LD_Move();    break;  //左下移
      case 'g': mecanumCar.RU_Move();    break;  //右上移
      case 'i': mecanumCar.RD_Move();    break;  //右下移
      case 'e': mecanumCar.drift_left(); break;  //漂移
      case 'f': mecanumCar.drift_right(); break; //漂移

      case 'p': Line_Tracking();   break;  //循迹
      case 'q': ult_following();   break;  //跟随
      case 'r': ult_avoiding();    break;  //避障

      /*********************小车灯光*************************/
      case 't': mecanumCar.right_led(1);  mecanumCar.left_led(1); break;  //开七彩灯
      case 'u': mecanumCar.right_led(0);  mecanumCar.left_led(0); break;  //关七彩灯
      case 'm': color_num++; showColor(); break;  //切换2812灯珠颜色
      case 'o': rgb.clear(); break;  //关闭2812灯珠
      case 'n': color_num--; showColor(); break;  //切换2812灯珠颜色
      /*********************小车调速*************************/
      case 'v':   /*读左前方电机M2的速度*/
        Serial1.readStringUntil('#');  //第一次接收到的速度值为空，先空读
        speed_str = Serial1.readStringUntil('#');  //第二次接收到速度数据，保存
        speed_Upper_L = String(speed_str).toInt();      //速度值为字符串格式，需要转换为整型
        speed_Upper_L = map(speed_Upper_L, 0, 100, 0, 255);  //从0~100映射到0~255
        //Serial.println(speed_Upper_L);  //串口调试
        break;
      case 'w':   /*读左后方电机M3的速度*/
        Serial1.readStringUntil('#');
        speed_str = Serial1.readStringUntil('#');
        speed_Lower_L = String(speed_str).toInt();
        speed_Lower_L = map(speed_Lower_L, 0, 100, 0, 255);
        //Serial.println(speed_Lower_L);
        break;
      case 'x':   /*读右前方电机M1的速度*/
        Serial1.readStringUntil('#');
        speed_str = Serial1.readStringUntil('#');
        speed_Upper_R = String(speed_str).toInt();
        speed_Upper_R = map(speed_Upper_R, 0, 100, 0, 255);
        //Serial.println(speed_Upper_R);
        break;
      case 'y':   /*读右后方电机M4的速度*/
        Serial1.readStringUntil('#');
        speed_str = Serial1.readStringUntil('#');
        speed_Lower_R = String(speed_str).toInt();
        speed_Lower_R = map(speed_Lower_R, 0, 100, 0, 255);
        //Serial.println(speed_Lower_R);
        break;

      default: break;
    }
  }
}


/*********************RGB2812显示*******************************/
void showColor() {
  //  Serial.print("color num:"); //用于USB串口调试
  //  Serial.println(color_num);
  //  这里设置只了7种颜色，可以自己添加
  if (color_num > 6)color_num = 0;
  if (color_num < 0)color_num = 6;
  switch (color_num) {
    case  0:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 255, 0, 0);  //第i个灯珠亮红色
      }
      rgb.show();                        //显示
      break;
    case  1:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 255, 80, 0); //第i个灯珠亮橙色
      }
      rgb.show();                        //显示
      break;
    case  2:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 255, 255, 0); //第i个灯珠亮黄色
      }
      rgb.show();                        //显示
      break;
    case  3:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 0, 255, 0);   //第i个灯珠亮绿色
      }
      rgb.show();                        //显示
      break;
    case  4:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 0, 0, 255);   //第i个灯珠亮蓝色
      }
      rgb.show();                        //显示
      break;
    case  5:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 0, 255, 255); //第i个灯珠亮靛色
      }
      rgb.show();                        //显示
      break;
    case  6:
      for (int i = 0; i < 4; i++) {
        rgb.setPixelColor(i, 160, 32, 240);//第i个灯珠亮紫色
      }
      rgb.show();                        //显示
      break;
    default : break;
  }
}


/*********************循迹*******************************/
void Line_Tracking(void) {   //循黑线
  while (1)
  {
    uint8_t SL = digitalRead(SensorLeft);   //读取左边巡线传感器的值
    uint8_t SM = digitalRead(SensorMiddle); //读取中间巡线传感器的值
    uint8_t SR = digitalRead(SensorRight);  //读取右边巡线传感器的值
    if (SM == HIGH) {  //中间检测到黑色
      if (SL == LOW && SR == HIGH) {  // 左边检测到白色，右边检测到黑色，向右转
        mecanumCar.Turn_Right();
      }
      else if (SR == LOW && SL == HIGH) {  // 左边检测到黑色，右边检测到白色，向左转
        mecanumCar.Turn_Left();
      }
      else {  // 左右都检测到白色, 直走
        mecanumCar.Advance();
      }
    }
    else {  //中间检测到白色
      if (SL == LOW && SR == HIGH) { // 左边检测到白色，右边检测到黑色，向右转
        mecanumCar.Turn_Right();
      }
      else if (SR == LOW && SL == HIGH) {  // 左边检测到黑色，右边检测到白色，向左转
        mecanumCar.Turn_Left();
      }
      else { // 全部检测到白色, 停止
        mecanumCar.Stop();
      }
    }
    if (Serial1.available())//如果接收缓冲区非空
    {
      ble_val = Serial1.read();//读取蓝牙数据
      if (ble_val == 's') {
        mecanumCar.Stop();
        break;
      }
    }
  }
}


/*********************超声波跟随*******************************/
void ult_following(void)
{
  while (1)
  {
    int distance = get_distance();  //获取距离保存在distance变量
    //Serial.println(distance);
    if (distance <= 15)  //后退的范围
    {
      mecanumCar.Back();
    }
    else if (distance <= 25)  //停止的范围
    {
      mecanumCar.Stop();
    }
    else if (distance <= 45) //前进的范围
    {
      mecanumCar.Advance();
    }
    else  //其它情况停止
    {
      mecanumCar.Stop();
    }
    if (Serial1.available())//如果接收缓冲区非空
    {
      ble_val = Serial1.read();//读取蓝牙数据
      if (ble_val == 's') {
        mecanumCar.Stop();
        break;
      }
    }
  }
}


/*********************超声波避障*******************************/
void ult_avoiding(void)
{
  int distance_M, distance_L, distance_R;
  while (1)
  {
    distance_M = get_distance();  //获取距离保存在distance变量
    if (distance_M < 20) {//当测到前方的距离小于20cm时
      mecanumCar.Stop();  //机器人停止
      delay(500); //延时500ms
      myservo.write(180);  //超声波云台左转
      delay(500); //延时500ms
      distance_L = get_distance();  //把超声波测到左边的距离赋给变量 a1
      delay(100); //稳定读取值
      myservo.write(0); //超声波云台右转
      delay(500); //延时500ms
      distance_R = get_distance(); //把超声波测到右边的距离赋给变量 a2
      delay(100); //稳定读取值

      myservo.write(90);  //回到90度位置
      delay(500);
      if (distance_L > distance_R) { //左边的距离大于右边时
        mecanumCar.Turn_Left();  //机器人左转
        delay(300);  //左转700ms
      } else {
        mecanumCar.Turn_Right(); //机器人右转
        delay(300);
      }
    }
    else { //如果测到前方的距离>=20cm时，机器人前进
      mecanumCar.Advance(); //前进
    }
    if (Serial1.available())//如果接收缓冲区非空
    {
      ble_val = Serial1.read();//读取蓝牙数据
      if (ble_val == 's') {
        mecanumCar.Stop();
        break;
      }
    }
  }
}


/*********************超声波测距*******************************/
int get_distance(void) {    //超声波测距
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //给TRIG至少10us的高电平以触发
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58.2; //计算出距离
  delay(30);
  return dis;
}
