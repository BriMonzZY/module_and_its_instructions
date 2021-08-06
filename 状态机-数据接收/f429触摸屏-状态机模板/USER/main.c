/**
 * @project	
 * @author 五月花队
 * @brief 电赛
 * @version 0.1
 * @date 2021-8-4
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define _MAIN_C
#include "main.h"


/* 全局变量定义 */

u8 temp_usart3;
u16 screen_cnt = 0; /* 触摸屏计数 */

enum estaSystem staSystem = INIT;		/* 设置初始状态staSystem为INIT */



/* ****************************************主函数*********************************** */

/**
 * @brief:		主函数
 * @param:		none
 * @retval:		none
 */
int main(void)
{
	/* 变量定义区域 */
	
	/* 初始化区域 */
	HAL_Init();											/* 初始化HAL库 */
	Stm32_Clock_Init(360,25,2,8);   /* 设置时钟,180MHz */
	delay_init(180);                /* 初始化延时函数 180MHz */
	MX_GPIO_Init();									/* 初始化GPIO */
	BEEP_Init();										/* 初始化蜂鸣器 */
	MX_DMA_Init();									/* 初始化DMA */
  MX_USART1_UART_Init();					/* 初始化uart1 */
  MX_USART3_UART_Init();					/* 初始化uart3 */
	StartUartRxDMA();  							/* 使能uartDMA(uart3) */
	HAL_UART_Receive_IT(&huart3, &temp_usart3, 1);  /* 打开uart中断 */
	LED_Init();                     /* 初始化LED */
	KEY_Init();                     /* 初始化按键 */
	SDRAM_Init();                   /* 初始化SDRAM*/
	LCD_Init();                     /* 初始化LCD */
	tp_dev.init();				    			/* 触摸屏初始化 */ 
	POINT_COLOR=BLUE;								/* 笔触颜色 */
	Draw_INIT_Screen();							/* 初始化屏幕为Init界面 */
	
	BEEP_ONCE();
	printf("init finished\n\n");
	
	
	/* *******************************************while(1)********************************************* */
	while(1){
		
		/* 触摸屏处理部分 */
		tp_dev.scan(0);										/* 扫描触摸屏 */
		if(tp_dev.sta & TP_PRES_DOWN){			/* 触摸屏被按下 */
			if(tp_dev.sta & TP_PRES_DOWN){		/* 触摸屏被按下 */
				Button_App();									/* 触摸屏按下动作 */
				screen_cnt++;
				delay_ms(50);
			}
		}
		
		/* 状态机逻辑判断 */
		if(staSystem == INIT){
			INIT_Action();
		}
		
	}  /* while(1) */
}
