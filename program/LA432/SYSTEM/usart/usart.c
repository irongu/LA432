/*************************************************************************************************************
�����ۺϵ��ӹ�����(GIE������)        ��Ʒ
Gearing Interated Electronics Studio

ĩ������Ԥ��ϵͳ

����������غ���(USART1&USART3)

��Ⱥ��714483620��Դ���ϻ���
��עBվUP����GIE������ ��ø�����Ƶ��Դ

����Դ���������Ϊרҵ�ļ���ˮƽ��GIE������ˡ���ṩ�������Լ�QQȺ�����κε����ļ���֧��
Ӳ��������Ͼ�������δ�ܷ��ֵ�bug�����ڱ���Դ���ϵ�ʹ�ÿ�����ɵ���ʧGIE�����Ҳ����κ����Ρ�

2019-3-21��һ��
��Ȩ���� ��ֹ�����κ���ҵ��;��
ע����������DS3231��SGP30��SHT20��VEML6070��������ļ����Ի�����
*************************************************************************************************************/
#include "Usart.h"
#include <stdarg.h>
u16 USART_RX_STA=0;
void USART1_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;			//���崮�ڽṹ��
	USART_InitTypeDef USART_InitStructure;		//���崮�ڳ�ʼ���ṹ��
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
	  
	USART_InitStructure.USART_BaudRate = 9600;//������9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	
	//����������1�жϣ���ʹ��DMA��������
// 	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
// 	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   
  //  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	
 // USART_Cmd(USART1, ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	
	
}

