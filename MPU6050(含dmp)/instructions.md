## 一些说明

使用MPU6050时，可以用定时器中断读取MPU获取的数据。



不过一般推荐使用MPU的中断功能，MPU采集到的数据是会产生中断（下降沿），一般配置成优先级最高的中断（控制中断）。



在imv_mpu.h文件第26行的宏定义进行修改(#define DEFAULT_MPU_HZ  (100))可以更改MPU的采样速率。







## **inv_mpu.c**



**u8 mpu_dmp_get_data(float *pitch,float *roll,float *yaw)**

==获取进行dmp运算后的数据(欧拉角)，并返回是否成功读取数据==

> pitch:俯仰角 精度:0.1°   范围:-90.0° <---> +90.0°
>
> roll:横滚角  精度:0.1°   范围:-180.0°<---> +180.0°
>
> yaw:航向角   精度:0.1°   范围:-180.0°<---> +180.0°



**mpu_dmp_init()**								 

==初始化MPU6050的DMP模式==





## **mpu6050.c**



**u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)**

==获取mpu的原始数据(角速度值)==

**u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)**

==获取mpu的原始数据(加速度值)==



**MPU_Init()**					    			 

==初始化MPU6050==		