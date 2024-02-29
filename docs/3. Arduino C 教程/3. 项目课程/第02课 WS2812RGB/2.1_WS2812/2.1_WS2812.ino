/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第2.1课
  WS2812
*/
#include "rgb.h"

//创建一个用于控制rgb的类,名为rgb,共4个灯珠,引脚连接到GP7
RGB rgb(7, 4);  //rgb(pin, num);  num = 0-100

void setup() {
  rgb.setBrightness(100);  //rgb亮度(0-255);
  delay(10);
  rgb.clear();  //关闭所有的灯
  delay(10);

  rgb.setPixelColor(0, 255, 0, 0);//第1个灯珠亮红
  rgb.setPixelColor(1, 0, 255, 0);//第2个灯珠亮绿色
  rgb.setPixelColor(2, 0, 0, 255);//第3个灯珠亮蓝
  rgb.setPixelColor(3, 255, 255, 255);//第4个灯珠亮白色
  rgb.show();    //刷新显示
}

void loop() {
}
