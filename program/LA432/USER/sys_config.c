/**
  ******************************************************************************
  * @file    sys_config.c
  * @author  zjj
  * @version V1.0
  * @date    2014-10-10
  * @brief   ϵͳ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:stm32f103��Ƭ��
  * ��̳    :
  * �Ա�    :
  *
  ******************************************************************************
  */
  
#include "sys_config.h"




void sys_Configuration(void)
{
    /* System Clocks Configuration */
  	RCC_Configuration();
    

    
    //����JTAG����
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //����AFIOʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*ʹ��SWD ����JTAG*/
    
    /* GPIO ���� */
    GPIO_Configuration();
}


//ϵͳʱ������
void RCC_Configuration(void)
{
  RCC_DeInit();//������ RCC�Ĵ�������Ϊȱʡֵ

  RCC_HSICmd(ENABLE);//ʹ��HSI  
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)//�ȴ�HSIʹ�ܳɹ�
  {
  }

  if(1)
  {
    //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //FLASH_SetLatency(FLASH_Latency_2);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);   
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);

    //���� PLL ʱ��Դ����Ƶϵ��
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_2);                
    //ʹ�ܻ���ʧ�� PLL,�����������ȡ��ENABLE����DISABLE
    RCC_PLLCmd(ENABLE);//���PLL������ϵͳʱ��,��ô�����ܱ�ʧ��
    //�ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    //����ϵͳʱ�ӣ�SYSCLK�� ����PLLΪϵͳʱ��Դ
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
    //�ȴ�PLL�ɹ�������ϵͳʱ�ӵ�ʱ��Դ
    //  0x00��HSI ��Ϊϵͳʱ�� 
    //  0x04��HSE��Ϊϵͳʱ�� 
    //  0x08��PLL��Ϊϵͳʱ��  
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}


/******************NVIC_Configuration*****************************/

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports. CAN TRX config�� Test Pin��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);   //GPIOʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;					//�ܽ�ѡ��LED_PINxʹ���˺궨��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //�ܽ�����ѡ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�ܽŹ�������
    GPIO_Init(GPIOA, &GPIO_InitStructure);				//�˿�ѡ����PA��PB��
    
	  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;					//�ܽ�ѡ��LED_PINxʹ���˺궨��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //�ܽ�����ѡ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�ܽŹ�������
    GPIO_Init(GPIOB, &GPIO_InitStructure);				//�˿�ѡ����PA��PB��

	  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;					//�ܽ�ѡ��LED_PINxʹ���˺궨��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //�ܽ�����ѡ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//�ܽŹ�������
    GPIO_Init(GPIOB, &GPIO_InitStructure);				//�˿�ѡ����PA��PB��
	
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1;					//�ܽ�ѡ��LED_PINxʹ���˺궨��
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //�ܽ�����ѡ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�ܽŹ�������
    GPIO_Init(GPIOD, &GPIO_InitStructure);				//�˿�ѡ����PA��PB��
}



void GPIO_PinReverse(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->ODR ^=  GPIO_Pin;
}


/*********************�����ʱ*******************/
//�����ʱ������us����
void Soft_delay_us(u16 time)
{    
   u32 i;  
   while(time--)
   {
      i=8;  //�Լ�����  ����ʱ�䣺20141116
      while(i--){};
        __nop();
        __nop();
        __nop();
        __nop();
   }
}

//�����ʱ������ms����
void Soft_delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=7950;  //�Լ�����  ����ʱ�䣺20141116
      while(i--) ;    
   }
}


