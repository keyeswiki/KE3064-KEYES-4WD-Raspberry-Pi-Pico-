# Raspberry Pi Pico 扩展板

## 1.概述
keyestudio sensor Shield V2 for Raspberry Pi Pico是专为Raspberry Pi Pico开发的扩展板，无需焊接，全引脚引出。为方便接线采用2.54防反插端子，且扩展板上接口都带有丝印。3pin接口丝印一般为G、V、S，其中扩展板上所有的G代表GND，V代表VCC（3.3V/5V，注意标了3.3V的不能接5V电源）接口，S代表接口上方的数字口/模拟口。4pin/5pin接口左面都有对应接口丝印。扩展板上自带间距为2.54mm的排母接口（主要为了方便舵机接线）。同时扩展板上自带1个电源指示灯PWR、自带4个定位孔。
该扩展板提供各种通信接口包括 I2C、UART、3 x模拟IO和13 x数字IO，并提供5V的电源接口为原型开发提供最简单的连接方式。

## 2.规格参数：
- 电流：最大为1.2A（其Raspberry Pi Pico整体IO输出为200mA，wifi模块处最大为1A）
- DC输入电压：5V
- 输出电压：DC3.3V\5V（电路5V,wifi模块为3V）
- 最大功率：4W
- 推荐环境温度：-10°C ~ 50°C
- 产品尺寸：70*55*15mm
- 排针间距：2.54mm

## 3.原理图：
![Img](./media/c3c55f44be0b28db69dd43dcf5b5b7fc.png)

## 4.接口说明：
![Img](./media/55119a349c4c761296fbd086f788fd71.png)

## 5.使用方法：
将Raspberry Pi Pico主板堆叠在扩展板上即可使用，如下图：
![Img](./media/f82c0a0d7384aec8cf33591441a49e54.png)







