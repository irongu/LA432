/*************************************************************************************************************
�����ۺϵ��ӹ�����(GIE������)        ��Ʒ
Gearing Interated Electronics Studio

ĩ������Ԥ��ϵͳ

GPS��Ϣ������غ���

�ο�CASIC��ģ���ǵ������ջ�Э��淶��д

��Ⱥ��714483620��Դ���ϻ���
��עBվUP����GIE������ ��ø�����Ƶ��Դ

����Դ���������Ϊרҵ�ļ���ˮƽ��GIE������ˡ���ṩ�������Լ�QQȺ�����κε����ļ���֧��
Ӳ��������Ͼ�������δ�ܷ��ֵ�bug�����ڱ���Դ���ϵ�ʹ�ÿ�����ɵ���ʧGIE�����Ҳ����κ����Ρ�

2019-3-21��һ��
��Ȩ���� ��ֹ�����κ���ҵ��;��
ע����������DS3231��SGP30��SHT20��VEML6070��������ļ����Ի�����
*************************************************************************************************************/

//GPS��Ϣ��ȡ����������
#include "ATGM336.h"
#include "string.h"

 	u16 t,xt;  	//���б���
	char *point;//�ַ���ָ��	
	u8 douhao;	//��������
	u8 ready;	  //GPS״̬��־
	u8 flag;	  //�����δ��λ����λ�ĵ�һ�β���
	u8 shijian[8];//UTCʱ��
	u8 riqi[11];
	u8 jingdu[13];//����
	u8 weidu[13]; //γ��
	u8 xing[2];	  //����
	u8 haiba[7];  //����	
	u8 sudu[7];
	uint16_t H_value;
	u8 GPS_Time_min;
	u8 GPS_Time_hour;
	u16 GPS_Time_year;
	u8 GPS_Time_mon;
	u8 GPS_Time_date;
	u8 SAT_C;//������
	u16 Alti;
	int GPS_FLAG=0;

void GPS_Refresh ()
 {	
			/***********��ȡһ����������Ҫ��Ϣ����λ�����
			��������������γ�ȡ�ʱ�䡢���ε�************/

			if(Find("$GNGGA")&&Find("$GNZDA")&&Find("$GNVTG"))							//�ж��ڼ����������ܷ��ҵ���"$GNGGA"��λ����Ϣ����"$GNZDA"��������Ϣ����"GNVTG"���ٶ���Ϣ����ͷ��һ��
			{
				point = strstr(USART_RX_BUF,"$GNGGA");	//�ҵ�"$GNGGA"λ�ã�׼����ȡGPS״̬��Ϣ��
				for(t = 0;t<45;t++)						//�Ѷ�λ��־��"$"��಻�ᳬ��45
				{
					point++;
					if(*point == ',')					//�ҡ�,��
					douhao++;						
					if(douhao == 6)						//�ҵ���6����,��
					{
						douhao = 0;						//������������
						point++;
						ready = *point;
						break;							//�ҵ��˵�6����,��������Ѱ�Ҷ���ѭ��
					}
				}
				
				
				if(ready == '0')						//�����6����,�����GPS״̬��־Ϊ0�����ӡ��������λ���ǡ�����
				{
					if(flag != 0)
					xing[0]=0;xing[1]=0;
					flag = 0;
				}
				else									//����ʼ��ʼ��λ����ʱ
				{
					flag++;
					if(flag == 255)flag = 2;
						point = strstr(USART_RX_BUF,"$GNZDA");	//�ҵ�"$GNZDA"λ�ã�׼����ȡʱ����Ϣ��
						point += 7;								//ʱ�����ݴ�
						for(t = 0;t<6;t++)						//����ӡ�������鸳ֵ
						{
							shijian[t] = *point;
							point++;
						}
						shijian[7] = shijian[5];				//��ʱ�����м���ϡ�:��
						shijian[6] = shijian[4];
						shijian[5] = ':';
						shijian[4] = shijian[3];
						shijian[3] = shijian[2];
						shijian[2] = ':';
						point += 5;	
						for(t = 0;t<10;t++)						//����ӡ�������鸳ֵ
						{
							riqi[t] = *point;
							point++;
						}
					point = strstr(USART_RX_BUF,"$GNGGA");	//�ҵ�"$GNGGA"λ�ã�׼����ȡ��γ����Ϣ��		
					for(t = 0;t<20;t++)						//"$GNGGA"�е�'$'��γ������λ����೬����20
					{
						point++;
						if(*point == ',')					//�ҡ�,��
						douhao++;						
						if(douhao == 2)						//�ҵ��ڶ�����,��
						{
							douhao = 0;						//������������
							point++;						//��λ��γ�����ݴ�
							for(t = 0;t<12;t++)				//����ӡ�������鸳ֵ
							{
								weidu[t] = *point;
								point++;
							}
							weidu[12]='\0';
							break;							//�ҵ��˵ڶ�����,��������Ѱ�Ҷ���ѭ��
						}
					}
					
					point += 1;								//�ҵ�������������λ��
					for(t = 0;t<13;t++)						//����ӡ�������鸳ֵ
					{
						jingdu[t] = *point;
						point++;
					}
					jingdu[12]='\0';
					point += 3;								//�ҵ�ʹ�õ�����������Ϣ����λ��
					xing[0] = *point;
					point++;
					xing[1] = *point;
					

					for(t = 0;t<7;t++)						//���Ǹ������ݵ�2λ�뺣������λ����೬����7
					{
						point++;
						if(*point == ',')					//�ҡ�,��
						douhao++;						
						if(douhao == 1)						//�ҵ��ڶ�����,��
						{
							douhao = 0;						//������������
							point+=1;						//��λ���������ݴ�
							for(t = 0;t<7;t++)				//����ӡ�������鸳ֵ��-9999.9~99999.9��
							{
								haiba[t] = *point;
								/*���������ֻ�С���㣬�����ո�*/
								if(haiba[t] != 46&&haiba[t]<48||haiba[t]>57)
								haiba[t] = ' ';
								point++;
							}
							for(t = 0;t<7;t++)				//����ӡ�������鸳ֵ��-9999.9~99999.9��
							{
								if(haiba[t] == ' ')
								{
								haiba[t] = 'm';
								haiba[t+1] = '\0';
									break;
								}
							}
							break;							//�ҵ��˵ڶ�����,��������Ѱ�Ҷ���ѭ��
						}
					}
					
					point = strstr(USART_RX_BUF,"$GNVTG");//�ҵ�GNVTGλ�ã�׼����ȡ�ٶ�
					t=0;xt=0;
					for(t=0;t<80;t++)
					{
						if(*point==',')
						{
							xt++;
							point++;
							if(xt==7)
								break;
						}
						else
							point++;
					}
					for(t = 0;t<4;t++)				//����ӡ�������鸳ֵ��-9999.9~99999.9��
					{
						if(*point==',')
							break;
						sudu[t]=(*point);
						point++;
					}
					sudu[t]='k';
					sudu[t+1]='p';
					sudu[t+2]='h';
					////////////////////////////////////////////////////////�˴��������GPS����
					GPS_Time_hour=10*(shijian[0]-48)+(shijian[1]-48);
					GPS_Time_min=10*(shijian[3]-48)+(shijian[4]-48);
					GPS_Time_date=10*(riqi[0]-48)+(riqi[1]-48);
					GPS_Time_mon=10*(riqi[3]-48)+(riqi[4]-48);
					GPS_Time_year=1000*(riqi[6]-48)+100*(riqi[7]-48)+10*(riqi[8]-48)+(riqi[9]-48);
					SAT_C=xing[1]-48+((xing[0]-48)*10);
					if(xing[0]==0x2C)
						SAT_C=xing[1]-48;
					else if(xing[1]==0x2C)
						SAT_C=xing[0]-48;
					else
						SAT_C=xing[1]-48+((xing[0]-48)*10);
					Alti=100*(haiba[0]-48)+10*(haiba[1]-48)+(haiba[2]-48);
					GPS_FLAG=1;
				}
			}	
 }
char Find(char *a)
{ 
	if(strstr(USART_RX_BUF,a)!=NULL)
    return 1;
	else
	return 0;
}
