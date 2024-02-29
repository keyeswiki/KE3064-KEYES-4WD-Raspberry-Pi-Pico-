/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第3.1课
  舵机转动
*/
#define  servo_pin  2      //舵机接GP2

void setup() {
  pinMode(servo_pin, OUTPUT);    //舵机引脚设置为输出模式
}

void loop() {
  for (uint8_t angle = 0; angle < 180; angle++)
  {
    servopulse(servo_pin, angle); //转动到angle角度
    delay(15);  //等待一会,以免转得太快
  }
  for (uint8_t angle = 180; angle > 0; angle--)
  {
    servopulse(servo_pin, angle); //转动到angle角度
    delay(15);  //等待一会,以免转得太快
  }
}

void servopulse(int pin, int myangle) {   //脉冲函数
  int pulsewidth = map(myangle, 0, 180, 500, 2500); //将角度映射到脉宽
  //输出脉冲
  digitalWrite(pin, HIGH);        //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(pin, LOW);         //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);  //周期为20ms
}
