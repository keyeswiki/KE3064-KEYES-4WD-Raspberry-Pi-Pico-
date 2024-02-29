/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第11课
  红外遥控智能车
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21

/****引入红外遥控头文件***/
#include "ir.h"

IR IRreceive(6);//红外接收接GP6

void setup()
{
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  int key = IRreceive.getKey();
  if (key != -1) {
    Serial.println(key);
    switch (key)
    {
      case 64: mecanumCar.Stop();       break;  //停止
      case 70: mecanumCar.Advance();    break;  //前进
      case 21: mecanumCar.Back();       break;  //后退
      case 68: mecanumCar.Turn_Left();  break;  //左转
      case 67: mecanumCar.Turn_Right(); break;  //右转
    }
  }
}
