/*************************************************************************************************************
舸轮综合电子工作室(GIE工作室)        出品
Gearing Interated Electronics Studio

末世生存预警系统

GPS信息解析相关函数

参考CASIC多模卫星导航接收机协议规范编写

加群：714483620开源资料汇总
关注B站UP主：GIE工作室 获得更多视频资源

本开源资料仍需较为专业的技术水平，GIE工作室恕不提供本资料以及QQ群以外任何单独的技术支持
硬件、软件上均可能有未能发现的bug，对于本开源资料的使用可能造成的损失GIE工作室不负任何责任。

2019-3-21第一版
版权所有 禁止用于任何商业用途！
注：本程序中DS3231、SGP30、SHT20、VEML6070相关驱动文件来自互联网
*************************************************************************************************************/

//GPS信息截取及分析函数
#include "ATGM336.h"
#include "string.h"

 	u16 t,xt;  	//空闲变量
	char *point;//字符串指针	
	u8 douhao;	//逗号索引
	u8 ready;	  //GPS状态标志
	u8 flag;	  //定义从未定位到定位的第一次测量
	u8 shijian[8];//UTC时间
	u8 riqi[11];
	u8 jingdu[13];//经度
	u8 weidu[13]; //纬度
	u8 xing[2];	  //卫星
	u8 haiba[7];  //海拔	
	u8 sudu[7];
	uint16_t H_value;
	u8 GPS_Time_min;
	u8 GPS_Time_hour;
	u16 GPS_Time_year;
	u8 GPS_Time_mon;
	u8 GPS_Time_date;
	u8 SAT_C;//卫星数
	u16 Alti;
	int GPS_FLAG=0;

void GPS_Refresh ()
 {	
			/***********提取一堆数据中重要信息：定位情况、
			搜索卫星数、经纬度、时间、海拔等************/

			if(Find("$GNGGA")&&Find("$GNZDA")&&Find("$GNVTG"))							//判断在几行数据中能否找到以"$GNGGA"（位置信息）、"$GNZDA"（日期信息）、"GNVTG"（速度信息）打头的一行
			{
				point = strstr(USART_RX_BUF,"$GNGGA");	//找到"$GNGGA"位置（准备截取GPS状态信息）
				for(t = 0;t<45;t++)						//已定位标志离"$"最多不会超过45
				{
					point++;
					if(*point == ',')					//找“,”
					douhao++;						
					if(douhao == 6)						//找到第6个“,”
					{
						douhao = 0;						//逗号索引归零
						point++;
						ready = *point;
						break;							//找到了第6个“,”后跳出寻找逗号循环
					}
				}
				
				
				if(ready == '0')						//如果第6个“,”后的GPS状态标志为0，则打印“搜索定位卫星……”
				{
					if(flag != 0)
					xing[0]=0;xing[1]=0;
					flag = 0;
				}
				else									//否则开始开始定位，授时
				{
					flag++;
					if(flag == 255)flag = 2;
						point = strstr(USART_RX_BUF,"$GNZDA");	//找到"$GNZDA"位置（准备截取时间信息）
						point += 7;								//时间数据处
						for(t = 0;t<6;t++)						//给打印数据数组赋值
						{
							shijian[t] = *point;
							point++;
						}
						shijian[7] = shijian[5];				//在时分秒中间加上“:”
						shijian[6] = shijian[4];
						shijian[5] = ':';
						shijian[4] = shijian[3];
						shijian[3] = shijian[2];
						shijian[2] = ':';
						point += 5;	
						for(t = 0;t<10;t++)						//给打印数据数组赋值
						{
							riqi[t] = *point;
							point++;
						}
					point = strstr(USART_RX_BUF,"$GNGGA");	//找到"$GNGGA"位置（准备截取经纬度信息）		
					for(t = 0;t<20;t++)						//"$GNGGA"中的'$'离纬度数据位数最多超不过20
					{
						point++;
						if(*point == ',')					//找“,”
						douhao++;						
						if(douhao == 2)						//找到第二个“,”
						{
							douhao = 0;						//逗号索引归零
							point++;						//定位到纬度数据处
							for(t = 0;t<12;t++)				//给打印数据数组赋值
							{
								weidu[t] = *point;
								point++;
							}
							weidu[12]='\0';
							break;							//找到了第二个“,”后跳出寻找逗号循环
						}
					}
					
					point += 1;								//找到经度数据所在位置
					for(t = 0;t<13;t++)						//给打印数据数组赋值
					{
						jingdu[t] = *point;
						point++;
					}
					jingdu[12]='\0';
					point += 3;								//找到使用的卫星数量信息所在位置
					xing[0] = *point;
					point++;
					xing[1] = *point;
					

					for(t = 0;t<7;t++)						//卫星个数数据第2位离海拔数据位数最多超不过7
					{
						point++;
						if(*point == ',')					//找“,”
						douhao++;						
						if(douhao == 1)						//找到第二个“,”
						{
							douhao = 0;						//逗号索引归零
							point+=1;						//定位到海拔数据处
							for(t = 0;t<7;t++)				//给打印数据数组赋值（-9999.9~99999.9）
							{
								haiba[t] = *point;
								/*若不是数字或小数点，则放入空格*/
								if(haiba[t] != 46&&haiba[t]<48||haiba[t]>57)
								haiba[t] = ' ';
								point++;
							}
							for(t = 0;t<7;t++)				//给打印数据数组赋值（-9999.9~99999.9）
							{
								if(haiba[t] == ' ')
								{
								haiba[t] = 'm';
								haiba[t+1] = '\0';
									break;
								}
							}
							break;							//找到了第二个“,”后跳出寻找逗号循环
						}
					}
					
					point = strstr(USART_RX_BUF,"$GNVTG");//找到GNVTG位置，准备提取速度
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
					for(t = 0;t<4;t++)				//给打印数据数组赋值（-9999.9~99999.9）
					{
						if(*point==',')
							break;
						sudu[t]=(*point);
						point++;
					}
					sudu[t]='k';
					sudu[t+1]='p';
					sudu[t+2]='h';
					////////////////////////////////////////////////////////此处输出各种GPS数据
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
