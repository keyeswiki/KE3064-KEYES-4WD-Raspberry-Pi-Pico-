/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第4课
  舵机转动
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21

void setup() {
  mecanumCar.Init();  //初始化麦轮车驱动
}

void loop() {
  mecanumCar.Advance();
  delay(2000);            //等待2秒
  
  mecanumCar.Back();      //后退
  delay(2000);
  
  mecanumCar.Turn_Left(); //左转
  delay(2000);

  mecanumCar.Turn_Right();//右转
  delay(2000);

  mecanumCar.Stop();      //停止
  delay(1000);
}
