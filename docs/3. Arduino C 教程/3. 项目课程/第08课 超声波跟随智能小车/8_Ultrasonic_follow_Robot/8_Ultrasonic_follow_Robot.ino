/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第8课
  超声波跟随智能小车
*/
#include "MecanumCar_v2.h"

#define  servo_pin  2      //舵机接GP2
mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21

/*******超声波传感器接口*****/
#define EchoPin  4  //ECHO 引脚连接到 GPIO4
#define TrigPin  3  //TRIG 引脚连接到 GPIO3

void setup() {
  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式
  pinMode(servo_pin, OUTPUT);    //舵机引脚设置为输出模式
  servopulse(servo_pin, 90); //转动到90度
  delay(300);  //等待一会,以免转得太快
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  int distance = get_distance();  //获取距离保存在distance变量
  Serial.println(distance);
  if (distance < 15)  //后退的范围
  {
    mecanumCar.Back();
  }
  else if (distance < 25)  //停止的范围
  {
    mecanumCar.Stop();
  }
  else if (distance < 45) //前进的范围
  {
    mecanumCar.Advance();
  }
  else  //其它情况停止
  {
    mecanumCar.Stop();
  }
}


/*********************超声波测距*******************************/
int get_distance(void) {    //超声波测距
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //给TRIG至少10us的高电平以触发
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58.2; //计算出距离
  delay(30);
  return dis;
}

/*********************舵机转动*******************************/
void servopulse(int pin, int myangle) {   //脉冲函数
  int pulsewidth = map(myangle, 0, 180, 500, 2500); //将角度映射到脉宽
  //输出脉冲
  digitalWrite(pin, HIGH);        //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(pin, LOW);         //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);  //周期为20ms
}