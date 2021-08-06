#ifndef UART_DMA_UART_DMA_H_
#define UART_DMA_UART_DMA_H_

#include "main.h"

extern UART_HandleTypeDef huart3;	//�޸�Ϊ���ô���
#define USB_Huart huart3			//�޸�Ϊ���ô���

#define UART_RX_BUF_SIZE 128

#define UART_RXTX_Switch 1			//���ڻ��Կ���

/*
Ҫ��Cube�п�����ȫ���жϺ��շ�DMA
 */

extern uint8_t RxBuffer[UART_RX_BUF_SIZE];
extern uint8_t TxBuffer[UART_RX_BUF_SIZE];
extern uint8_t TxLen;

void USB_DMA_printf(const char *format,...);			//printf DMA��ʽ
void USB_printf(const char *format,...);				//printf ��ͨ��ʽ
uint8_t UartTxData(UART_HandleTypeDef *huart, uint8_t *buf, const uint32_t len);
uint8_t StartUartRxDMA(void);								//����DMA��ʼ��
uint8_t StartUartTxDMA(void);								//����Ҫ�Լ�����
void ProcessData(void);										//������������ݴ�����
void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);	//��USARTx_IRQHandler�����

#endif /* UART_DMA_UART_DMA_H_ */


