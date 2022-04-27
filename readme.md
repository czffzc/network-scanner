# 网络扫描器操作文档



[toc]

## 一.整体介绍

* 语言:C++

* 运行环境：Windows 10 

* 运行平台：Qt 5.12.11 MinGW_32_bit-Release

  

      该网络扫描器主要实现了主机扫描，端口和服务扫描，操作系统探测等相关功能。

![image-20220423215345126](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423215345126.png)

## 二.按钮及输入说明

      界面最上方有三个下拉列表分别是文件，运行，帮助。
      点击文件可以退出，点击运行可以运行，点击帮助显示该程序编写人员信息。

![image-20220423215527275](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423215527275.png)




    之后是一块输入的框，其中在配置中有三个选择，主机+操作系统，仅主机扫描，端口服务扫描。
    第一行的输入框是对于主机+操作系统和仅主机扫描两种选择设立的，第二行的输入框是对于端口服务扫描设置的。

![image-20220423215605188](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423215605188.png)



      输入对应的信息并选择配置后，点击scan按钮或者上方的运行按钮，即可运行。

![image-20220423215741331](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423215741331.png)



## 三.界面说明

#### 1.主机+操作系统界面
      该界面主要实现了扫描指定网段，显示该网段下活跃(能ping通的主机)的主机(关闭防火墙)列表，并显示其操作系统的功能。
      在上方第一行的输入框输入主机扫描起始ip和主机扫描结束ip后，选择配置为主机+操作系统或者仅主机扫描，点击运行或者scan按钮，得到的主机列表及其操作系统(选择配置为仅主机扫描时不会显示)会在该界面上显示。


![image-20220423221044442](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423221044442.png)



#### 2.本机明细界面

      该界面主要实现显示运行该程序的本机相关信息，在打开该程序时就会显示，无需相关的输入操作。
![image-20220423220428778](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423220428778.png)



#### 3.端口+服务界面

      该界面主要实现指定主机的端口及其服务扫描。
      在上方第二行的输入框中输入端口扫描的主机ip，及起始端口和结束端口，选择配置为端口服务扫描后，点击运行或者scan按钮，在该界面上会显示该主机在指定的端口范围内开放的端口及对应的服务信息。

![image-20220423220751344](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423220751344.png)

## 四、其他说明

#### 缺陷

1. cancel按钮可以停止线程，但无法终止运行。

2. 操作系统扫描根据icmp协议中的获取的ttl值推测主机的ttl初始值，从而进行判断，无法精确判断操作系统。

#### 注意事项

1. 扫描主机测试时需要先关闭防火墙。
2. 为保证实验结果，主机扫描尽可能在局域网内测试。

#### 提交文件说明

​	![image-20220423222558083](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220423222558083.png)

1. exe中为可执行文件
2. setup中为程序安装包
3. src中为源代码