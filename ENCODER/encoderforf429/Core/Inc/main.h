/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
	
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

typedef struct PID{
	double SetPoint;            //�趨ֵ
	double Kp;                  //����ϵ��
	double Ki;                  //����ϵ��
	double Kd;                  //΢��ϵ��
	double LastError;           //���һ�������Er[-1]
	double PrevError;           //���ڶ��������er[-2]
	double SumError;            //������  
}PID;


extern PID wheel_speed_1;
extern PID wheel_speed_2;
extern PID wheel_speed_3;
extern PID wheel_speed_4;

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WHEEL3_DIR_Pin GPIO_PIN_7
#define WHEEL3_DIR_GPIO_Port GPIOE
#define WHEEL4_DIR_Pin GPIO_PIN_8
#define WHEEL4_DIR_GPIO_Port GPIOE
#define WHEEL1_DIR_Pin GPIO_PIN_0
#define WHEEL1_DIR_GPIO_Port GPIOD
#define WHEEL2_DIR_Pin GPIO_PIN_1
#define WHEEL2_DIR_GPIO_Port GPIOD
#define RTS_Pin GPIO_PIN_3
#define RTS_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
