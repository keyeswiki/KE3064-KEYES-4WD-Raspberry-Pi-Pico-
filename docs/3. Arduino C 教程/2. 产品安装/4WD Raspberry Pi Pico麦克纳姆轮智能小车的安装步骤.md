# 4WD Raspberry Pi Pico麦克纳姆轮智能小车的安装步骤

## 安装1

安装所需零件:
![Img](./media/a108b5aa0cd622bdcf2e4bd0081a9f9d.png)

安装:
![Img](./media/af30e1eb79927fcaf046599841a714d1.png)

完成:
![Img](./media/31a0c112d0e5940dfe5b93f3a722bc29.png)

## 安装2

安装所需零件:
![Img](./media/f65ceee3ed6970021dbb09348438347e.png)

安装:
![Img](./media/5d4adb5ed864b30fe0e418abdd802b6f.png)

完成:
![Img](./media/2c84c18b96952e62020ac8385f08aa48.png)

## 安装3

安装所需零件：
![Img](./media/dffc68bb48759c1f184f870cb6727198.png)

安装：
![Img](./media/e8968d6dd83418f2e529c855acf39bc4.png)

完成：
![Img](./media/bab661b1a63fb1deeb08dc304d1cecc0.png)

## 安装4

**舵机初始化：**
安装前需要先设置舵机角度为90°。设置舵机角度时，将舵机连接在Raspberry Pi Pico扩展板的G、V、GIO2，在Raspberry Pi Pico主控板上上传对应代码，外接电源供电后，舵机就转到90°的位置。
| 舵机 | Microbit扩展板 |
| :--: | :--: |
| 棕线 | G |
| 红线 | V |
| 橙线 | G2 |
![Img](./media/467fad21c91e80f72fea47f8f38abbc6.png)

```
/*
  初始化舵机角度为90°
*/
#define  servo_pin  2      //舵机接GP2

void setup() {
    pinMode(servo_pin, OUTPUT);    //舵机引脚设置为输出模式
    servopulse(servo_pin, 90);  //转动到90°角度
    delay(500);
}

void loop() {

}

void servopulse(int pin, int myangle) {   //脉冲函数
  int pulsewidth = map(myangle, 0, 180, 500, 2500); //将角度映射到脉宽
  //输出脉冲
  digitalWrite(pin, HIGH);        //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(pin, LOW);         //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);  //周期为20ms
}

```
我们提供的初始化舵机角度的代码位置如下图：
![Img](./media/8e5bc1885a22286ced7e1a4084fa5d9b.png)

安装所需零件：
![Img](./media/a6273f2838f9b23717db9682651e79a1.png)

安装：
<span style="color: rgb(255, 76, 65);">(注意安装方向)</span>
![Img](./media/822d76ff8a2d5a7373c1604ae6211eea.png)

完成：
![Img](./media/81edd32173751ca1b74bbc0c145b89ae.png)

## 安装5

安装所需零件：
![Img](./media/ca601e4d62ee01d3d66fbe346b31dfc7.png)

安装：
![Img](./media/52d44f6e974586645207096db0b64fc8.png)

完成：
![Img](./media/f635ebcd790ae8799c153c9d1adcdd32.png)

## 安装6

安装所需零件：
![Img](./media/371e2969a28003a85e7cbec00079d39d.png)

安装：
![Img](./media/d6c895df17a35c71af94381e002824c4.png)

完成：
![Img](./media/15f3b5037f8ee903fac5e4a70e0e549d.png)

## 安装7

安装所需零件：
![Img](./media/30ecef73107aafc1ace9b986f20d6886.png)

安装：
<span style="color: rgb(255, 76, 65);">（注意电机安装方向，线材方向朝内）</span>

![Img](./media/79fbd9f4d559f4b93f0be021764920a0.png)

完成：
![Img](./media/3c723ede4dc593de328226793e206cd8.png)

## 安装8

安装所需零件：
![Img](./media/eb96fb06bb13ab417ac6dad3b8229527.png)

安装：
![Img](./media/8d7c3766edcad436f9c34077c8a4b249.png)

完成：
![Img](./media/fae0827e3152d784b74ec0a8c2015394.png)

## 安装9

安装所需零件：
![Img](./media/bbe81bf5cf74c3e416b50239b416eb67.png)

安装：
![Img](./media/5e5f37e9191d64ed535e812a71d2ecb8.png)

完成：
![Img](./media/42719cbbe0dd9e648eef7caa6acbc6a1.png)

## 安装10

安装准备零件：
![Img](./media/daaa045fc53ebf187bfc10d1868e2aa8.png)

安装：
![Img](./media/6c0b75d4e039cfb70aa8e8dcbb8ad632.png)

完成：
![Img](./media/5ad6a165b6b3972809051c7aca97beb4.png)

## 安装11

安装准备零件：
![Img](./media/933ca34b37235c4881949ef8ce8bbbd9.png)

安装：
![Img](./media/738807793b2f10696b5581c7f1f6b193.png)

完成：
![Img](./media/30584e7bab2c3e3b4f0287466693ae99.png)

## 接线

舵机接线：
| 舵机 | Raspberry Pi Pico 扩展板 |
| :--: | :--: |
| 棕线 | G |
| 红线 | 5V |
| 橙线 | G2 |
![Img](./media/467fad21c91e80f72fea47f8f38abbc6.png)
![Img](./media/14771ab5bd1148aa86ad49349bae9bc9.png)

超声波模块接线：
| 超声波模块 | Raspberry Pi Pico 扩展板 |
| :--: | :--: |
| Vcc | 5V|
| Trig | G3 |
| Echo |G4|
|Gnd|G|
![Img](./media/87c137c8c7301fa4c6ac5c81911786dc.png)
![Img](./media/599c989627c0fef3eef0ee4a7146d6d6.png)

控制红外模块接线：
| 驱动板 |Raspberry Pi Pico 扩展板 |
| :--: | :--: |
| GND | G|
| 5V | 5V |
| S5 | G6|
![Img](./media/290709948855e2b9e1296e3775283d08.png)
![Img](./media/e63531b6709f5007f4a31d57f052696e.png)

控制WS2812RGB接线：
| 驱动板 | Raspberry Pi Pico 扩展板 |
| :--: | :--: |
| GND | G|
| 5V | 5V |
| S4 | G7|
![Img](./media/9ed485f70ceb0084fa5bcade5057a14f.png)
![Img](./media/1b8b7fd37446b8426e32789859a4c9f4.png)

控制电机和七彩灯接线:
| 驱动板 | Raspberry Pi Pico 扩展板 |
| :--: | :--: |
| SCL | G21|
| SDA | G20 |
|5V | 5V|
|GND|G|
![Img](./media/fee7861fd52bcfa568e1e6fc0994880a.png)
![Img](./media/97bab3d446890a38e5d4af5539909055.png)

控制三路循迹模块接线:
| 驱动板 | Raspberry Pi Pico 扩展板 |
| :--: | :--: |
| S1 | G18|
| S2 | G17 |
|S3| G16|
| | |
|GND|G|
![Img](./media/875f676b8a7fa089085243faf2c14d7a.png)
![Img](./media/f8acc681d0622e30d384fe993ede4bb4.png)

电源接线:
![Img](./media/e48d3e76a8a0c8410c31497d97967272.png)

电机接到对应的接口上:
![Img](./media/716ba73134597d9f429d5c8b3ec1d148.png)

电池安装示范:
![Img](./media/4060740fcb686ec8ae5eff3420937538.png)


