/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第10.1课
  红外遥控
*/

#include "ir.h"

IR IRreceive(6);//红外接收接GP6

void setup(){
}

void loop() {
  int key = IRreceive.getKey();
  if (key != -1) {
    Serial.println(key);
  }
}
