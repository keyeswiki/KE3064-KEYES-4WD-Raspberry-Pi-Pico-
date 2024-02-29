/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第3.1课
  舵机转动
*/
#include <Servo.h>
Servo myservo;    //定义一个舵机类实例

void setup() {
  myservo.attach(2);    //舵机引脚连接到GPIO2
}

void loop() {
  for (uint8_t angle = 0; angle < 180; angle++)//从0到180度
  {
    myservo.write(angle); //转动到angle角度
    delay(15);  //等待一会,以免转得太快
  }
  for (uint8_t angle = 180; angle > 0; angle--)//从180到0度
  {
    myservo.write(angle); //转动到angle角度
    delay(15);
  }
}
