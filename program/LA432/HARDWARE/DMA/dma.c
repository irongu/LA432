#include "dma.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DMA ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

DMA_InitTypeDef DMA_InitStructure;

u16 DMA1_MEM_LEN=700;//����DMAÿ�����ݴ��͵ĳ��� 	    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ����� 
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //??DMA??
	DMA_DeInit(DMA_CHx); //?DMA???1?????????
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA?????
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA?????
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //??????,??????????
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMA???DMA?????
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //?????????
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //?????????
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //?????8?
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //?????8?
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //???????
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA?? x?????? 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA??x????????????
	DMA_Init(DMA_CHx, &DMA_InitStructure); //??DMA_InitStruct?????????DMA???USART1_Rx_DMA ???????
	USART_Cmd(USART1, ENABLE); //????1 
	DMA_Cmd(DMA_CHx, ENABLE); //??USART1 TX DMA1 ?????? 
	MYDMA_Enable(DMA1_Channel5);//????DMA??!SART1_Tx_DMA_Channel����ʶ�ļĴ��� 	
} 
//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��      
 	DMA_SetCurrDataCounter(DMA1_Channel5,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
 	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
}	  
 

























