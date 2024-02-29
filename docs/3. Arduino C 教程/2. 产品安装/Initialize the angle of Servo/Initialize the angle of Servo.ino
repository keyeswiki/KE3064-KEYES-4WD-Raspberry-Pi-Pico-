/*
  初始化舵机角度为90°
*/
#define  servo_pin  2      //舵机接GP2

void setup() {
    pinMode(servo_pin, OUTPUT);    //舵机引脚设置为输出模式
}

void loop() {
    servopulse(servo_pin, 90);  //转动到90°角度
    delay(500);
}

void servopulse(int pin, int myangle) {   //脉冲函数
  int pulsewidth = map(myangle, 0, 180, 500, 2500); //将角度映射到脉宽
  //输出脉冲
  digitalWrite(pin, HIGH);        //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(pin, LOW);         //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);  //周期为20ms
}
