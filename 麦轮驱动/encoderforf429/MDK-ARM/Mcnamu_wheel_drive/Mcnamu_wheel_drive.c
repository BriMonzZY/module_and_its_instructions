#include "Mcnamu_wheel_drive.h"



#define DRV  /* ��������ѡ�� DRV HIP*/


/* �ٶȱջ���λ��ʽPID */
double PIDCalc(PID *pp, double NextPoint)   
{
	
	double dError,                              /* ��ǰ΢�� */
				 Error;                               /* ƫ�� */
	Error = pp->SetPoint - NextPoint;           /* ƫ��ֵ=�趨ֵ-����ֵ����ǰֵ��*/
	

	/* �����޷� */
	if(pp->SumError > 4000) pp->SumError = 4000;
	if(pp->SumError < -4000) pp->SumError = -4000;
	
	pp->SumError += Error;                      /* ����=����+ƫ��  --ƫ����ۼ� */
	dError = pp->LastError - pp->PrevError;     /* ��ǰ΢�� = ������ - ֮ǰ��� */
	pp->PrevError = pp->LastError;              /* ���¡�֮ǰ�� */
	pp->LastError = Error;                      /* ���¡������ */
	return (pp->Kp * Error                      /* ������ = �������� * ƫ�� */
			+   pp->Ki *  pp->SumError              /* ������ = ���ֳ��� * ������ */
			+   pp->Kd * dError                     /* ΢���� = ΢�ֳ��� * ��ǰ΢�� */
				 );
}





/* �������ת������ */
#ifdef HIP

void wheel1_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed < -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (int)speed);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 0);
	}
	else if(speed < 0){
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, (int)speed);
	}
}

void wheel2_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed <= -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, (int)speed);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 0);
	}
	else {
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, (int)speed);
	}
}

void wheel3_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed < -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (int)speed);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
	}
	else if(speed < 0){
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (int)speed);
	}
}

void wheel4_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed < -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, (int)speed);
		__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, 0);
	}
	else if(speed < 0){
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, (int)speed);
	}
}

#endif



#ifdef DRV

void wheel1_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed < -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (int)speed);
		HAL_GPIO_WritePin(WHEEL1_DIR_GPIO_Port, WHEEL1_DIR_Pin, GPIO_PIN_SET);
	}
	else if(speed < 0){
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (int)speed);
		HAL_GPIO_WritePin(WHEEL1_DIR_GPIO_Port, WHEEL1_DIR_Pin, GPIO_PIN_RESET);
	}
}

void wheel2_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed <= -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, (int)speed);
		HAL_GPIO_WritePin(WHEEL2_DIR_GPIO_Port, WHEEL2_DIR_Pin, GPIO_PIN_SET);
	}
	else {
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, (int)speed);
		HAL_GPIO_WritePin(WHEEL2_DIR_GPIO_Port, WHEEL2_DIR_Pin, GPIO_PIN_RESET);
	}
}

void wheel3_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed < -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (int)speed);
		HAL_GPIO_WritePin(WHEEL3_DIR_GPIO_Port, WHEEL3_DIR_Pin, GPIO_PIN_SET);
	}
	else if(speed < 0){
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (int)speed);
		HAL_GPIO_WritePin(WHEEL3_DIR_GPIO_Port, WHEEL3_DIR_Pin, GPIO_PIN_RESET);
	}
}

void wheel4_speed_set(float speed)
{
	if(speed >= 100) speed = 100;
	else if(speed < -100) speed = -100;
	speed = ((double)speed/100.0)*600;
	if(speed >= 0){
		__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, (int)speed);
		HAL_GPIO_WritePin(WHEEL4_DIR_GPIO_Port, WHEEL4_DIR_Pin, GPIO_PIN_SET);
	}
	else if(speed < 0){
		speed *= -1;
		__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, (int)speed);
		HAL_GPIO_WritePin(WHEEL4_DIR_GPIO_Port, WHEEL4_DIR_Pin, GPIO_PIN_RESET);
	}
}

#endif


#define pi 3.14159f

/* ȫ���ٶȽ��� */
void all_directions(int v, int angle, int angular_velocity)
{
	/* �ٶȼ�ƫת�ĽǶȺ��Դ��Ľ��ٶ� */
	int vw1, vw2, vw3, vw4;  /* ������õ����ӵ�ת�� */
	int vtx, vty;

	/* �����ٶ���0��ʱ��(��������ʱ��) */
	vtx = v*cos(pi*angle/180);
	vty = v*sin(pi*angle/180);
	vw1 = vty - vtx;
	vw2 = vty + vtx;
	vw3 = vty - vtx;
	vw4 = vty + vtx;
	
	wheel_speed_1.SetPoint = vw1;
	wheel_speed_2.SetPoint = vw2;
	wheel_speed_3.SetPoint = vw3;
	wheel_speed_4.SetPoint = vw4;
	
#if 0
	wheel1_speed_set(vw1);
	wheel2_speed_set(vw2);
	wheel3_speed_set(vw3);
	wheel4_speed_set(vw4);
#endif
	
	printf("%d %d %d %d\n", vw1, vw2, vw3, vw4);
}


