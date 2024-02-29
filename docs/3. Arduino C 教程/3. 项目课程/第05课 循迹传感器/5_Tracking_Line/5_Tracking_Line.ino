/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第5课
  循迹传感器
*/
/*******循迹传感器引脚定义**********/
#define SensorLeft    16   //左循迹传感器输入引脚
#define SensorMiddle  17   //中间循迹传感器输入引脚
#define SensorRight   18   //右循迹传感器输入引脚


void setup() {
  /****循迹传感器接口全部设置为输入模式***/
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);

}

void loop() {
  uint8_t SL = digitalRead(SensorLeft); //读取左边巡线传感器的值
  uint8_t SM = digitalRead(SensorMiddle); //读取中间巡线传感器的值
  uint8_t SR = digitalRead(SensorRight); //读取右边巡线传感器的值
  Serial.print("Left:");  //串口打印信息
  Serial.print(SL);
  Serial.print("  Middle:");
  Serial.print(SM);
  Serial.print("  Right:");
  Serial.print(SR);
  Serial.println(); //换行
  delay(100);
}
