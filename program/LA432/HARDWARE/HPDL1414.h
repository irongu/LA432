#ifndef _HPDL1414_H_
#define _HPDL1414_H_

#include <stdio.h>   //Keil library
//#include "intrins.h"
#include "delay.h"

//****************************************
// ����IO��
//****************************************
#define D0	PAout(11)							//�������ݶ�ӦIO
#define	D1	PAout(12)
#define	D2	PAout(15)
#define	D3	PBout(3)
#define	D4	PDout(1)
#define	D5	PDout(0)
#define	D6	PBout(4)
#define	A0	PAout(2)					//1414λѡ
#define	A1	PAout(1)
#define	WR1	PBout(7)					//1414Ƭѡ,0����1�ر�
#define	WR2	PAout(0)
#define	WR3	PAout(3)

//****************************************
// 1414������λѡ
//****************************************
void HPDLbit_select(u8 select);				//����1��4������

//****************************************
// 1414�������������λ
//****************************************
void HPDLoutput_Data(u8 word);				//����һ��8λ16���������ߵ�1λ��ȥ��ʣ�µ������ɸߵ���������D6D5D4D3D2D1D0


void HPDLoutput_Databit(u8 WR,u8 word1,u8 word2,u8 word3,u8 word4);
//****************************************
// 1414�����������
//****************************************
void HPDLoutput_Data1(u8 WR,u8 word[4]); //��������ΪƬѡ����һ�������ĸ��ַ���ֱ�Ӵ���ascll��

void HPDL_dsp(u8 HPDL_dspin[12]);

#endif
