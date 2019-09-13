#ifndef __ATGM336_H
#define __ATGM336_H

#include "stm32f10x.h"
#include "Usart.h"

extern unsigned char USART_RX_BUF[];  
void USART1_Config(void);
void GPS_Refresh (void);

char Find(char *a);

#endif
