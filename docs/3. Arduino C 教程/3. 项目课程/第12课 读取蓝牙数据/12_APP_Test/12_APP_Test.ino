/*
  KEYES 4WD Raspberry Pi Pico 麦克纳姆轮智能小车
  第12课
  读取蓝牙数据
*/

char ble_val;
void setup() {
  Serial1.begin(9600);  //设置蓝牙串波特率为9600
}

void loop() {
  if (Serial1.available())//如果接收区非空
  {
    char ble_val = Serial1.read();//读取蓝牙数据
    Serial.println(ble_val);//USB串口打印读取到的数据
  }
}
