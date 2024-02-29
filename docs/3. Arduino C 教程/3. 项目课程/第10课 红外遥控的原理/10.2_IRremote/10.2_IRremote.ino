/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第10.2课
  红外遥控控制LED
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21
#include "ir.h"

IR IRreceive(6);//红外接收接GP6
bool flag = true;

void setup(){
  mecanumCar.Init();//初始化电机与七彩灯驱动
}

void loop() {
  int key = IRreceive.getKey();
  if (key == 64 && flag == true) {
    mecanumCar.right_led(1);
    mecanumCar.left_led(1);
    flag = false;
  }else if (key == 64 && flag == false) {
    mecanumCar.right_led(0);
    mecanumCar.left_led(0);
    flag = true;
  }
}
