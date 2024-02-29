/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第7课
  超声波传感器
*/
/*******超声波传感器接口*****/
#define EchoPin  4  //ECHO引脚连接到GPIO4
#define TrigPin  3  //TRIG引脚连接到GPIO3

void setup() {
  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式
}

void loop() {
  float distance = get_distance();  //获取距离保存在distance变量
  Serial.print("ditance:");
  Serial.print(distance);
  Serial.println("cm");
  delay(100);
}

float get_distance(void) {    //超声波测距
  float dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //给TRIG引脚至少10us的高电平以触发
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) /58.2;  //计算出距离
  delay(50);
  return dis;
}
