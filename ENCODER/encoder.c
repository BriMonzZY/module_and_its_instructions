#include "encoder.h"


/**
 * @brief		TIM2��ʼ������
 *
 * @param		��
 * @return		��
 */
void Encoder_Init_TIM2(void)
{
	/* ��ʼ���ṹ�� */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��

	/* ����GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				 //�����趨������ʼ��GPIOB

	/* ����ʱ�� */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = 65535; //�趨�������Զ���װֵ
	//TIM_TimeBaseStructure.TIM_Period =  (374-1)*4;  //�趨��������װֵ   ���ٺ�һȦ���374�����壬4��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	//Reset counter
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}


/**
 * @brief		TIM4��ʼ������
 *
 * @param		��
 * @return		��
 */
void Encoder_Init_TIM4(void)
{
	/* ��ʼ���ṹ�� */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��

	/* ����GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB

	/* ����ʱ�� */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = 65535; //�趨�������Զ���װֵ
	//TIM_TimeBaseStructure.TIM_Period =  (374-1)*4;  //�趨��������װֵ   ���ٺ�һȦ���374�����壬4��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	//Reset counter
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);
}

/**
 * @brief		��ȡTIM��ȡ�ı�������ֵ
 *
 * @param		TIMx��Ҫ��ȡ��TIM��ֵ
 * @return		��������ֵ
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
 * @brief		TIM4�жϷ�����
 *
 * @param		��
 * @return		��
 */
void TIM4_IRQHandler(void)
{
	if (TIM4->SR & 0X0001) {  // ����ж�              
	}
	TIM4->SR &= ~(1 << 0);  // ����жϱ�־λ      
}

/**
 * @brief		TIM2�жϷ�����
 *
 * @param		��
 * @return		��
 */
void TIM2_IRQHandler(void)
{
	if (TIM2->SR & 0X0001) {  // ����ж�             
	}
	TIM2->SR &= ~(1 << 0);  // ����жϱ�־λ      
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


