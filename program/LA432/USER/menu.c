#include "sys_config.h"
#include "menu.h"

extern u8 dsp_cache[12];
extern u8 GPS_swflag;
void time_datashift()
{
	dsp_cache[0]=' ';
	dsp_cache[1]=' ';
	dsp_cache[2]=Display_Time[0];
	dsp_cache[3]=Display_Time[1];
	dsp_cache[4]=':';
	dsp_cache[5]=Display_Time[3];
	dsp_cache[6]=Display_Time[4];
	dsp_cache[7]=':';
	dsp_cache[8]=Display_Time[6];
	dsp_cache[9]=Display_Time[7];
	dsp_cache[10]=' ';
	dsp_cache[11]=' ';
}

void date_datashift()
{
	dsp_cache[0]=' ';
	dsp_cache[1]=Display_Date[0];
	dsp_cache[2]=Display_Date[1];
	dsp_cache[3]=Display_Date[2];
	dsp_cache[4]=Display_Date[3];
	dsp_cache[5]='-';
	dsp_cache[6]=Display_Date[5];
	dsp_cache[7]=Display_Date[6];
	dsp_cache[8]='-';
	dsp_cache[9]=Display_Date[8];
	dsp_cache[10]=Display_Date[9];
	dsp_cache[11]=' ';
}

void display_time()
{
	Time_Handle();
	time_datashift();
	HPDL_dsp(dsp_cache);	
}

void display_date()
{
	Time_Handle();
	date_datashift();
	HPDL_dsp(dsp_cache);
}

void GPS_switch()
{
	while(KEY_UP==1|KEY_PUSH==1)
	{
		if(KEY_PUSH==0)
		{
			
			GPS_swflag=!GPS_swflag;
		}
	}
	
	
}
