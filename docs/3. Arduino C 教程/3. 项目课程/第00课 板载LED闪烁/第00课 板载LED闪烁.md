# 第00课 板载LED闪烁

## 1.实验介绍：
Raspberry Pi Pico上有个板载LED，这个LED是固定接在Raspberry Pi Pico上的GP25引脚，在这个项目中，我们将来学习使板载LED闪烁的效果。

## 2.实验元件：
|![Img](./media/5d97fb6721ef25ff45a3cb87a401438c.png)| ![Img](./media/b4421594adeb4676d63581a1047c6935.png) |
| :--: | :--: |
| Raspberry Pi Pico*1 |USB 线*1 |

## 3.实验接线：
在本项目中，用USB线将Raspberry Pi Pico和电脑连起来。连接方法请参照文档：<span style="color: rgb(255, 76, 65);">开发环境配置</span>
![Img](./media/469785ddad60a9a3c9a1e002c32a64b5.png)

## 4.实验代码：
Raspberry Pi Pico板载LED是由GP25控制，当GP25输出高电平时，LED点亮;当输出低时，LED灯关闭。

```
//**********************************************************************
/*
第00课：板载LED闪烁
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

```

## 5.实验结果：
选择好开发板(Raspberry Pi Pico)和端口(COMx)，编译上传代码完成后，利用USB线上电，可以看到的现象是：Raspberry Pi Pico的LED开始闪烁，循环进行。
![Img](./media/7efa0d347e4079a56218a69f75485f92.png)

