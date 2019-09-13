/**
  ******************************************************************************
  * @file    sys_config.c
  * @author  zjj
  * @version V1.0
  * @date    2014-10-10
  * @brief   系统配置
  ******************************************************************************
  * @attention
  *
  * 实验平台:stm32f103单片机
  * 论坛    :
  * 淘宝    :
  *
  ******************************************************************************
  */
  
#include "sys_config.h"




void sys_Configuration(void)
{
    /* System Clocks Configuration */
  	RCC_Configuration();
    

    
    //禁用JTAG功能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //开启AFIO时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*使能SWD 禁用JTAG*/
    
    /* GPIO 配置 */
    GPIO_Configuration();
}


//系统时钟配置
void RCC_Configuration(void)
{
  RCC_DeInit();//将外设 RCC寄存器重设为缺省值

  RCC_HSICmd(ENABLE);//使能HSI  
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)//等待HSI使能成功
  {
  }

  if(1)
  {
    //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //FLASH_SetLatency(FLASH_Latency_2);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);   
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);

    //设置 PLL 时钟源及倍频系数
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_2);                
    //使能或者失能 PLL,这个参数可以取：ENABLE或者DISABLE
    RCC_PLLCmd(ENABLE);//如果PLL被用于系统时钟,那么它不能被失能
    //等待指定的 RCC 标志位设置成功 等待PLL初始化成功
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    //设置系统时钟（SYSCLK） 设置PLL为系统时钟源
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
    //等待PLL成功用作于系统时钟的时钟源
    //  0x00：HSI 作为系统时钟 
    //  0x04：HSE作为系统时钟 
    //  0x08：PLL作为系统时钟  
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}


/******************NVIC_Configuration*****************************/

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports. CAN TRX config； Test Pin；
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);   //GPIO时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;					//管脚选择，LED_PINx使用了宏定义
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //管脚速率选择
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//管脚功能配置
    GPIO_Init(GPIOA, &GPIO_InitStructure);				//端口选择：如PA，PB口
    
	  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;					//管脚选择，LED_PINx使用了宏定义
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //管脚速率选择
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//管脚功能配置
    GPIO_Init(GPIOB, &GPIO_InitStructure);				//端口选择：如PA，PB口

	  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;					//管脚选择，LED_PINx使用了宏定义
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //管脚速率选择
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//管脚功能配置
    GPIO_Init(GPIOB, &GPIO_InitStructure);				//端口选择：如PA，PB口
	
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1;					//管脚选择，LED_PINx使用了宏定义
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	    //管脚速率选择
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//管脚功能配置
    GPIO_Init(GPIOD, &GPIO_InitStructure);				//端口选择：如PA，PB口
}



void GPIO_PinReverse(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->ODR ^=  GPIO_Pin;
}


/*********************软件延时*******************/
//软件延时函数，us级别
void Soft_delay_us(u16 time)
{    
   u32 i;  
   while(time--)
   {
      i=8;  //自己定义  调试时间：20141116
      while(i--){};
        __nop();
        __nop();
        __nop();
        __nop();
   }
}

//软件延时函数，ms级别
void Soft_delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=7950;  //自己定义  调试时间：20141116
      while(i--) ;    
   }
}


