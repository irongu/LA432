#include "dma.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DMA 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

DMA_InitTypeDef DMA_InitStructure;

u16 DMA1_MEM_LEN=700;//保存DMA每次数据传送的长度 	    
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量 
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
	MYDMA_Enable(DMA1_Channel5);//????DMA??!SART1_Tx_DMA_Channel所标识的寄存器 	
} 
//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA1_Channel5,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
}	  
 

























