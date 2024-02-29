/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第1课
  七彩灯闪烁
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21

void setup() {
  mecanumCar.Init();//初始化电机与七彩灯驱动
}

void loop() {
  mecanumCar.right_led(1);//开启右边七彩灯闪烁
  mecanumCar.left_led(1); //开启左边七彩灯闪烁
  delay(3000);            //延时3000毫秒
  mecanumCar.right_led(0); //关闭右边七彩灯闪烁
  mecanumCar.left_led(0);  //关闭左边七彩灯闪烁
  delay(1000);             //延时1000毫秒
}
