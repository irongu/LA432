/*************************************************************************************************************
舸轮综合电子工作室(GIE工作室)        出品
Gearing Interated Electronics Studio

末世生存预警系统

串口配置相关函数(USART1&USART3)

加群：714483620开源资料汇总
关注B站UP主：GIE工作室 获得更多视频资源

本开源资料仍需较为专业的技术水平，GIE工作室恕不提供本资料以及QQ群以外任何单独的技术支持
硬件、软件上均可能有未能发现的bug，对于本开源资料的使用可能造成的损失GIE工作室不负任何责任。

2019-3-21第一版
版权所有 禁止用于任何商业用途！
注：本程序中DS3231、SGP30、SHT20、VEML6070相关驱动文件来自互联网
*************************************************************************************************************/
#include "Usart.h"
#include <stdarg.h>
u16 USART_RX_STA=0;
void USART1_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;			//定义串口结构体
	USART_InitTypeDef USART_InitStructure;		//定义串口初始化结构体
//	NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	USART_InitStructure.USART_BaudRate = 9600;//波特率9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	
	//不开启串口1中断，而使用DMA接收数据
// 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
// 	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
   
  //  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	
 // USART_Cmd(USART1, ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	
	
}

