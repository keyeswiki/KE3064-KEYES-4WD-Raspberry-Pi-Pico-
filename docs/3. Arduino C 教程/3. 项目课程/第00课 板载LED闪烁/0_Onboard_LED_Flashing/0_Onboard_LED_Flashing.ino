//**********************************************************************
/*
项目 01：板载LED闪烁
使PICO主板上的LED闪烁.
*/
#define LED_BUILTIN 25

// 按复位键或单板上电时，设置功能运行一次
void setup() {
  // 初始化数字引脚LED_BUILTIN作为输出模式.
  pinMode(LED_BUILTIN, OUTPUT);
}

// 循环函数会一直运行下去
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // 点亮LED (HIGH是高电平)
  delay(1000);                       // 延时1秒
  digitalWrite(LED_BUILTIN, LOW);    // 通过使电压为0来关闭LED
  delay(1000);                       // 延时1秒
}
//*************************************************************************************
