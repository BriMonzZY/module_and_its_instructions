#include "encoder.h"


/**
 * @brief		TIM2初始化函数
 *
 * @param		无
 * @return		无
 */
void Encoder_Init_TIM2(void)
{
	/* 初始化结构体 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 打开时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器4的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PB端口时钟

	/* 配置GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);				 //根据设定参数初始化GPIOB

	/* 配置时基 */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
	TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
	//TIM_TimeBaseStructure.TIM_Period =  (374-1)*4;  //设定计数器重装值   减速后一圈输出374个脉冲，4倍频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	//Reset counter
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}


/**
 * @brief		TIM4初始化函数
 *
 * @param		无
 * @return		无
 */
void Encoder_Init_TIM4(void)
{
	/* 初始化结构体 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 打开时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟

	/* 配置GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB

	/* 配置时基 */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
	TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
	//TIM_TimeBaseStructure.TIM_Period =  (374-1)*4;  //设定计数器重装值   减速后一圈输出374个脉冲，4倍频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	//Reset counter
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);
}

/**
 * @brief		读取TIM获取的编码器的值
 *
 * @param		TIMx：要读取的TIM的值
 * @return		编码器的值
 */
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;
	switch (TIMX) {
	case 2:  Encoder_TIM = (short)TIM2->CNT;  TIM2->CNT = 0; break;
	case 3:  Encoder_TIM = (short)TIM3->CNT;  TIM3->CNT = 0; break;
	case 4:  Encoder_TIM = (short)TIM4->CNT;  TIM4->CNT = 0; break;
	default: Encoder_TIM = 0;
	}
	return Encoder_TIM;
}

/*
int Read_Encoder(u8 TIMX)
{
	int value_1;
	switch(TIMX) {
		case 2: value_1 = (short)TIM_GetCounter(TIM2); TIM_SetCounter(TIM2, 0); break;
		case 4: value_1 = (short)TIM_GetCounter(TIM4); TIM_SetCounter(TIM4, 0); break;
		default: value_1 = 0;
	}
	return value_1;
}
*/


/**
 * @brief		TIM4中断服务函数
 *
 * @param		无
 * @return		无
 */
void TIM4_IRQHandler(void)
{
	if (TIM4->SR & 0X0001) {  // 溢出中断              
	}
	TIM4->SR &= ~(1 << 0);  // 清除中断标志位      
}

/**
 * @brief		TIM2中断服务函数
 *
 * @param		无
 * @return		无
 */
void TIM2_IRQHandler(void)
{
	if (TIM2->SR & 0X0001) {  // 溢出中断             
	}
	TIM2->SR &= ~(1 << 0);  // 清除中断标志位      
}

/*
void TIM2_IQRHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != 0) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM4_IQRHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != 0) {
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
*/


