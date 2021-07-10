# CollegeTrainingProjects

本仓库储存有大学实训课期间写的代码。大学专业是电子信息工程，所以本仓库内的代码主要用于单片机/嵌入式方向开发，也因此本仓库的代码主要以C写成。

除极特殊需要外，本仓库已停止维护，代码仅供参考，且不保证能够正常运行，因此使用前请仔细甄别，由此产生的损失本人概不负责。

## 代码列表

<details>
<summary>展开查看</summary>
<pre>
<code>
├── ds18b20.c
│   └── 使用DS18B20传感器的测温显示电路程序，其中四位共阴极数码管由PNP三极管驱动
├── IntelligentVehicleProject1_MotorBasicMotion.c
│   └── 由L298N电机驱动模块驱动两部电机组成的智能小车，并使其完成前后左右基本移动
├── IntelligentVehicleProject2_SingleIRSensor.c
│   └── 由L298N驱动电机与一组红外对管组成的智能小车，智能小车可以根据红外对管的反射状态变化自主完成指定动作
├── IntelligentVehicleProject3_BothIRSensorTracking.c
│   └── 由L298N驱动电机与两组红外对管组成的智能小车，智能小车可以根据两部红外对管的反射状态变化判断循迹线位置，并通过控制电机转动方向完成小车的自主左右转弯，实现循迹功能
├── IntelligentVehicleProject4_QuadIRSensorTracking.c
│   └── 由L298N驱动电机与四组红外对管组成的智能小车，在上一个程序基础上，用以提高智能小车的循迹精度
├── IntelligentVehicleProject5_SingleSupersonicSensorObstacleAvoidance.c
│   └── 由L298N驱动电机与一部HC-SR06超声波测距模块组成的智能小车，智能小车可以根据测距模块提供的距离信息完成距障碍物一定距离时的自主转向动作
├── IntelligentVehicleProject6_Synthesis.c
│   └── 由L298N驱动电机与四对红外对管、一部HC-SR06超声波测距模块组成的智能小车，合并上述程序使智能小车实现完整功能
└── to be continued...
</code>
</pre>
</details>
