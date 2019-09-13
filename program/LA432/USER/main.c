#include "sys_config.h"

u8 dsp_cache[12],menu_page=1,GPS_swflag;
int sec_flag,second_last;
unsigned char USART_RX_BUF[700];//GPS��DMA��������


u8 key_read()
{
	if(KEY_UP==0)
	{
		delay_ms(20);
		while(KEY_UP==0);
		return 1;
	}
	
	if(KEY_PUSH==0)
	{
		delay_ms(20);
		while(KEY_PUSH==0);
		return 2;
	}
	
	if(KEY_DOWN==0)
	{
		delay_ms(20);
		while(KEY_DOWN==0);
		return 3;
	}	
}

int main(void)
{	
	RCC_ClocksTypeDef get_rcc_clock;
	
	sys_Configuration();
	RCC_GetClocksFreq(&get_rcc_clock); 
	
	TimeValue.year=0x2019;//����������в��򿪣���Щ��ʼʱ�����Ч	
	TimeValue.month=0x03;
	TimeValue.week=0x02;
	TimeValue.date=0x12;
	TimeValue.hour=0x20;
	TimeValue.minute=0x46;
	TimeValue.second=0x55;
//	DS3231_Time_Init(&TimeValue);//�����ã�����ǿ��д��ʱ��ֵ
	MYDMA_Config(DMA1_Channel5,(u32)&USART1->DR,(u32)USART_RX_BUF,700);//����1��DMA��ʼ����һ������GPS���ݰ���Լ500�ֽڣ�����������Ϊ700�ֽ�
	Time_Handle();
	
	while(1)
	{
		
		switch(menu_page)
		{
			case 1:
				display_time();
			break;
			
			case 2:
				display_date();
			break;
			
			case 3:
				GPS_switch();
			break;
			
			case 4:
				
			break;
			
			case 5:
				
			break;
			
			case 6:
				
			break;
			
			case 7:
				
			break;
		
			
		}
	
		
		if(USART_RX_BUF[0])//DMA�յ���ÿ�����ĵ�һ������   
		{
					delay_ms(160);//������ʱ�ȴ�DMA����
					GPS_Refresh ();//GPS���ݰ���������
					memset(USART_RX_BUF,0,700);    //��ս��ջ�����
					MYDMA_Enable(DMA1_Channel5);
		}
	}
}
