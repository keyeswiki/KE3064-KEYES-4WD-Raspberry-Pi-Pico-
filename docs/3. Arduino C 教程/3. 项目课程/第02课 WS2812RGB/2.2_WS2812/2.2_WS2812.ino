/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第2.2课
  WS2812
*/
#include "rgb.h"
//创建一个用于控制rgb的类,名为rgb,共4个灯珠,引脚连接到GP7
RGB rgb(7, 4);  //rgb(pin, num);  num = 0-100

void setup() {
  rgb.setBrightness(100);  //rgb.亮度(0-255);
  delay(10);
  rgb.clear();  //关闭所有的灯
  delay(10);

}

void loop() {
  uint8_t r = random(0, 255);
  uint8_t g = random(0, 255);
  uint8_t b = random(0, 255);
  for (uint8_t i = 0; i < 4; i++)
  {
    rgb.setPixelColor(i, r, g, b);//第i+1个灯珠颜色为随机(r,g,b)
    rgb.show();    //刷新显示
    delay(100); //等待一会儿
  }
}
