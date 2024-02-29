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
Raspberry Pi Pico板载LED是由GP25控制，当GP25输出高电平时，LED点亮; 当输出低时，LED灯关闭。

本教程中使用的代码保存在：“**..\4. Python 教程\3. 项目课程**” 的路径中。你可以把代码移到任何地方。例如，我们将代码保存在**D盘**中，<span style="color: rgb(0, 209, 0);">路径为D:\3. 项目课程</span>。
![Img](./media/92103adf9654c97f49aea829c933d86f.png)

打开“**Thonny**”软件，点击“**此电脑**”→“**D:**”→“**3. 项目教程**”→“**第00课 板载LED闪烁**”，然后鼠标左键双击“**0_Onboard_LED_Flashing.py**”。
![Img](./media/ac1ec25a7f2f4eba88a5675a5a964273.png)

```
from machine import Pin
import time

led = Pin(25, Pin.OUT)   # 从引脚25创建LED对象，设置引脚25输出

try:
    while True:
        led.value(1)    # 点亮LED
        time.sleep(0.5) # 延时 0.5s
        led.value(0)    # 关闭LED
        time.sleep(0.5) # 延时 0.5s
except:
    pass

```

## 5.实验结果：
确保Raspberry Pi Pico主板已经连接到电脑上，单击“![Img](./media/555a25f055ba1b4c56ee4c3a28ffe5af.png)”。
![Img](./media/7dc51a813fcbc163c6a5e92e8a4535a1.png)

利用USB线上电，单击“![Img](./media/5c05febdb56bb5ef370e897c012c1b91.png)”，代码开始执行，你会看到的现象是：Raspberry Pi Pico的LED开始闪烁，循环进行。按“Ctrl+C”或单击“![Img](./media/555a25f055ba1b4c56ee4c3a28ffe5af.png)”退出程序。
![Img](./media/80f463ac32c7d9991d0c5465b6f10b28.png)
![Img](./media/7efa0d347e4079a56218a69f75485f92.png)

