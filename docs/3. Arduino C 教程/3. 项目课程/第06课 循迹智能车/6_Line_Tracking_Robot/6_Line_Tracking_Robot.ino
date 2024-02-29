/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第6课
  循迹智能车
*/

#include "MecanumCar_v2.h"
mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21

/*******循迹传感器引脚定义**********/
#define SensorLeft    16   //左循迹传感器输入引脚
#define SensorMiddle  17   //中间循迹传感器输入引脚
#define SensorRight   18   //右循迹传感器输入引脚


void setup() {
  Serial.begin(9600); // 打开串口监视器，设置波特率为9600
  /****循迹传感器接口全部设置为输入模式***/
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  uint8_t SL = digitalRead(SensorLeft);   //读取左边巡线传感器的值
  uint8_t SM = digitalRead(SensorMiddle); //读取中间巡线传感器的值
  uint8_t SR = digitalRead(SensorRight);  //读取右边巡线传感器的值
  Serial.print("Left:");  //串口打印信息
  Serial.print(SL);
  Serial.print("  Middle:");
  Serial.print(SM);
  Serial.print("  Right:");
  Serial.print(SR);
  Serial.println(); //换行
  delay(100);
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
    else { // 全是白色，停止走
      mecanumCar.Stop();
    }
  }
}
