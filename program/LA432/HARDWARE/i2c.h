#ifndef _i2c_h
#define _i2c_h

#include "stm32f10x.h"

#define SCL_H() GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define SCL_L() GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define SDA_H() GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define SDA_L() GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define IN_SDA() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)

#define ds_a = 0 IN_SDA

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(u8 a);
u8 IIC_Write_Byte(u8 dat);
u8 IIC_Read_Byte(void);
u8 Single_WriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 data);
u8 Single_WriteI2C_com(u8 Slave_Address,u8 REG_Address);
u8 I2C_WaitAck(void);
extern void Soft_delay_ms(u16 time);
#endif
