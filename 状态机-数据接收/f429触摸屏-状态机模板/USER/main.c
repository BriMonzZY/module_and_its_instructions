/**
 * @project	
 * @author ���»���
 * @brief ����
 * @version 0.1
 * @date 2021-8-4
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define _MAIN_C
#include "main.h"


/* ȫ�ֱ������� */

u8 temp_usart3;
u16 screen_cnt = 0; /* ���������� */

enum estaSystem staSystem = INIT;		/* ���ó�ʼ״̬staSystemΪINIT */



/* ****************************************������*********************************** */

/**
 * @brief:		������
 * @param:		none
 * @retval:		none
 */
int main(void)
{
	/* ������������ */
	
	/* ��ʼ������ */
	HAL_Init();											/* ��ʼ��HAL�� */
	Stm32_Clock_Init(360,25,2,8);   /* ����ʱ��,180MHz */
	delay_init(180);                /* ��ʼ����ʱ���� 180MHz */
	MX_GPIO_Init();									/* ��ʼ��GPIO */
	BEEP_Init();										/* ��ʼ�������� */
	MX_DMA_Init();									/* ��ʼ��DMA */
  MX_USART1_UART_Init();					/* ��ʼ��uart1 */
  MX_USART3_UART_Init();					/* ��ʼ��uart3 */
	StartUartRxDMA();  							/* ʹ��uartDMA(uart3) */
	HAL_UART_Receive_IT(&huart3, &temp_usart3, 1);  /* ��uart�ж� */
	LED_Init();                     /* ��ʼ��LED */
	KEY_Init();                     /* ��ʼ������ */
	SDRAM_Init();                   /* ��ʼ��SDRAM*/
	LCD_Init();                     /* ��ʼ��LCD */
	tp_dev.init();				    			/* ��������ʼ�� */ 
	POINT_COLOR=BLUE;								/* �ʴ���ɫ */
	Draw_INIT_Screen();							/* ��ʼ����ĻΪInit���� */
	
	BEEP_ONCE();
	printf("init finished\n\n");
	
	
	/* *******************************************while(1)********************************************* */
	while(1){
		
		/* ������������ */
		tp_dev.scan(0);										/* ɨ�败���� */
		if(tp_dev.sta & TP_PRES_DOWN){			/* ������������ */
			if(tp_dev.sta & TP_PRES_DOWN){		/* ������������ */
				Button_App();									/* ���������¶��� */
				screen_cnt++;
				delay_ms(50);
			}
		}
		
		/* ״̬���߼��ж� */
		if(staSystem == INIT){
			INIT_Action();
		}
		
	}  /* while(1) */
}
