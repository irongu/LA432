#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>
//unsigned char USART_RX_BUF[700];
void USART1_Config(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
//u16 USART_RX_STA=0;       //����״̬���	  
//u8 USART_RX_BUF[100];     //���ջ���,���USART_REC_LEN���ֽ�.
#define USART_REC_LEN 20
// void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif /* __USART1_H */


