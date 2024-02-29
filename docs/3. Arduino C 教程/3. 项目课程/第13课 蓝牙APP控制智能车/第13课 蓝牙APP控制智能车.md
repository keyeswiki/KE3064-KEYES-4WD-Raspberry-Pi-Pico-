# 第13课 蓝牙APP控制智能车
![Img](./media/813bf5af11dc62c669956b79c020dfe2.png)

## 1. 实验说明：                                                                                
在上一课程中，我们已经介绍了蓝牙APP的使用和各按钮的功能，并且通过蓝牙APP连接蓝牙来读取了APP界面上各按钮发送的控制字符，在本课程中，主要是通过蓝牙APP连接蓝牙实现APP控制4WD智能车的多种功能。

## 2. 添加库文件：
首先我们先确保安装了库文件，不然代码会编译出错，这里我们用到库文件“<span style="color: rgb(255, 76, 65);">MecanumCar_v2</span>”、“<span style="color: rgb(255, 76, 65);">rgb</span>”、“<span style="color: rgb(255, 76, 65);">ir</span>”和“<span style="color: rgb(255, 76, 65);">Servo</span>”，如何安装库文件请参考Arduino C 教程中的“<span style="color: rgb(0, 209, 0);">开发环境配置</span>”文件。如果库文件已经添加好了，就跳过这一步骤。
![Img](./media/b1b60f9edaa8f26ecf2534f1e0be73aa.png)

## 3. 实验代码：                                                                                

```
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
#define EchoPin  4  //ECHO 引脚接到 GPIO4
#define TrigPin  3  //TRIG 引脚接到 GPIO3

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

  myservo.attach(2);  // 舵机接到GPIO2上
  myservo.write(90);
  delay(500);

  rgb.setBrightness(100);  //rgb的亮度(0-255);
  delay(10);
  rgb.clear();  //关闭所有的LED
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
      case 'e': mecanumCar.drift_left(); break;  //左漂移
      case 'f': mecanumCar.drift_right(); break; //右漂移

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
    if (SM == HIGH) {
      if (SL == LOW && SR == HIGH) {  // 黑色在右边，白色在左边，向右转
        mecanumCar.Turn_Right();
      }
      else if (SR == LOW && SL == HIGH) {  // 黑色在左边，白色在右边，向左转
        mecanumCar.Turn_Left();
      }
      else {  // 两边都是白色，向前走
        mecanumCar.Advance();
      }
    }
    else {
      if (SL == LOW && SR == HIGH) { // 黑色在右边，白色在左边，向右转
        mecanumCar.Turn_Right();
      }
      else if (SR == LOW && SL == HIGH) {  // 白色在右边，黑色在左边，向左转
        mecanumCar.Turn_Left();
      }
      else { // 全是白色，停止
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
      distance_L = get_distance();  //把超声波测到左边的距离赋给变量distance_L
      delay(100); //稳定读取值
      myservo.write(0); //超声波云台右转
      delay(500); //延时500ms
      distance_R = get_distance(); //把超声波测到右边的距离赋给变量distance_R
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
```
<span style="color: rgb(255, 76, 65);">上传代码之前，确保蓝牙模块已经从扩展板上拔下来，否则会导致代码上传不成功。</span>

## 4. 实验结果：                                                                                
安上电池，将电机驱动底板上的电源拨码开关拨到ON一端，开启电源。选择好开发板(Raspberry Pi Pico)和端口(COMx)，编译上传代码完成后。插上蓝牙，注意蓝牙不要插反了。你就可以使用手机APP来控制如下玩法：（<span style="color: rgb(255, 76, 65);">有关APP的具体下载安装方法及使用方法，请参考**第12课 读取蓝牙数据** </span>）
（1）点击![Img](./media/49fd9134c59222bca61663c5c0044f84.png)开启七彩灯，再次点击这个按钮七彩灯就会关闭。
（2）点击![Img](./media/dc90304902e357572904ce5fc4218cad.png)会进入循迹模式，当想退出该模式时，再次点击该按钮。
（3）点击![Img](./media/fd5794661a1b87dbd39a068f05ca2342.png)会进入跟随模式、当想退出该模式时，再次点击该按钮。
（4）点击![Img](./media/b9521925d663bc37a7534a9e155c3550.png)会进入避障模式，当想退出该模式时，再次点击该按钮。
（5）![Img](./media/01dd10330fbff2f211105024590a3960.png)拉动这两个条幅回改变左边两个电机的速度，右边也是相同的操作方法。
<span style="color: rgb(255, 76, 65);">注意：</span>![Img](./media/e6ef2d7df8bfa993aa70ae3e70434fc9.png)是用来进行调速的，当进行调速时，应该拖动拉条![Img](./media/6063628aa960f2d988c2a6ee4c564397.png)；不能点击![Img](./media/6063628aa960f2d988c2a6ee4c564397.png)，如果点击的话可能调速不成功。
（6）![Img](./media/aa0e44fd88c5480215c77c363e75f61b.png)这几个按钮是用来切换底板下面4个2812灯珠颜色的，中间按钮为关闭功能。
（7）剩下其他的按钮全都是用来操控小车行驶的，跟其他按钮不同的是，这些按钮当我们按下时小车行驶，松开按钮时小车停止。
![Img](./media/92673ed92eba02ed1662b20ab7fc4434.png)

## 5. 代码说明:
|char ble_val; |定义一个char类型的变量 |
| :--: | :--: |
|Serial1.begin(9600); |设置蓝牙串口波特率为9600，这里要注意Serial和Serial1的区别，因为我们用的串口0所以使用Serial1，使用串口1时则需使用Serial2，而Serial为USB串口，即串口监视器使用。 |
|if (Serial1.available())|如果接收到蓝牙数据，这个值就不为0|
|char ble_val = Serial1.read(); | 读取蓝牙串口的数据，因为我们发生的是字符数据，所以定义一个char类型的变量来保存。 |
| ![Img](./media/9f5e68286763d4d4bd65949ecd5288d9.png)|请注意这两句代码的区别，上面这句是输出到串口监视器，后面这句是输出数据到蓝牙模块。 |
|Serial1.readStringUntil('#');|读取蓝牙发送的一串字符串，遇到“#”停止读取，注意我们这里连续使用两条这样的语句，是因为我们进行调速时，发送的字符串比如为V#50#，所以我们第一次读到的是“V”（遇到#则停止）,第二次读到的值为“50”，注意这里读到的是字符串而不是整数值|
|String(speed_str).toInt();|将读取到的数字字符串转换为整数值|
|map(speed_Upper_L, 0, 100, 0, 255);|因为我们APP上发送的速度值为0~100，所以我们得将它映射到0~255的范围中|
|![Img](./media/e3938372a0508b7e7828789a7252de42.png)|这四个变量我们没有直接定义，因为它是包含在"MecanumCar_v2.h"头文件中，分别代表四个电机的速度值，范围为0~255|



