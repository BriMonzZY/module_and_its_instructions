## encoder.c

使用正交编码器（AB相，目前未加入Z相2021/8/6）

配置TIM为ENCODER模式





关于配置成TI1还是配置成TI1andTI2模式，还有psc和period配置我现在还没有搞懂，目前配置为TI1模式，psc为1,polarity为rising edge可以正常使用。(2021/8/6)





如果想要记录转过几圈，将重装载值改为374（==一圈脉冲值，或者引入Z相记录转过的圈数==），将中断服务函数改为下面的就行(标准库)

```c
int circle_count=0;//全局变量-圈数
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
    {      
        if((TIM3->CR1>>4 & 0x01)==0) //DIR==0，向上计数，
            circle_count++;
        else if((TIM3->CR1>>4 & 0x01)==1)//DIR==1，向下计数
            circle_count--;
    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
```





**int Read_Encoder(u8 TIMX)**

==读取对应的TIM定时器的值，作为编码器的值，返回一个整数，直接调用即可==





参考： https://blog.csdn.net/nomil9/article/details/86777323