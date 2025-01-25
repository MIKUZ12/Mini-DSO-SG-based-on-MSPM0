#include "oled.h"
#include "stdlib.h"
#include "board.h"
#include "math.h"

int voltage_row[128]={0};
unsigned int adc_value[128] = {0};
int freq = 1;
unsigned char str1[] = "NA";
unsigned char str2[] = "YE";


void draw_axis(void)
{
				OLED_DrawLine(0,0,0,64,1);
				OLED_DrawLine(0,63,128,63,1);//axis
				OLED_DrawLine(125,60,128,63,1);

				
				OLED_DrawLine(0,0,4,0,1);
				OLED_DrawLine(0,8,3,8,1);
				OLED_DrawLine(0,16,4,16,1);
				OLED_DrawLine(0,24,3,24,1);
				OLED_DrawLine(0,32,4,32,1);
				OLED_DrawLine(0,40,3,40,1);
				OLED_DrawLine(0,48,4,48,1);
				OLED_DrawLine(0,56,3,56,1);
				OLED_DrawLine(0,63,4,63,1);//vertical index

}	


	
#define THRESHOLD 0.5

void draw_wave(int TG)
{
    u8 Xtime;
//    u8 range = 63;
//    float scale = (float)range/255;


//    for(Xtime = 128; Xtime > 0; Xtime -= 1)
//    {
//        adc_value[Xtime] = adc_value[Xtime - 1];
//    }


//    adc_value[0] = v/6;

//    for (int Xtime = 0; Xtime < 127; Xtime++)
//    {

//        int i1 = (Xtime / freq) * freq;   
//        int i2 = i1 + freq;              
//        if (i2 > 127) i2 = 127;          


//        int   dx    = Xtime - i1;           
//        float ratio = (float)dx / (float)(i2 - i1);  


//        float val1F = (1.0f - ratio)*adc_value[i1] 
//                    + ratio*adc_value[i2];
//        int y1 = (int)(val1F);

//        int   Xnext = Xtime + 1;
//        int   j1    = (Xnext / freq)*freq;
//        int   j2    = j1 + freq;
//        if (j2 > 127) j2 = 127;

//        int   dx2    = Xnext - j1;
//        float ratio2 = (float)dx2 / (float)(j2 - j1);

//        float val2F = (1.0f - ratio2)*adc_value[j1]
//                    + ratio2*adc_value[j2];
//        int y2 = (int)(val2F);

//        int drawY1 = 63 - y1;
//        int drawY2 = 63 - y2;


//        float diff = (adc_value[i2] - adc_value[i1]);

//        if (diff > THRESHOLD)
//        {

//            int yA = 63 - (int)adc_value[i1];
//            int yB = 63 - (int)adc_value[((Xtime+1) / freq) * freq];

//            OLED_DrawLine(Xtime,   yA,
//                          Xtime+1, yB,
//                          1);
//        }
//        else
//        {

//            OLED_DrawLine(Xtime,   drawY1,
//                          Xtime+1, drawY2,
//                          1);
//        }
//    }


		if(TG != 0)
		{
			for(int Xtime=1;Xtime<127;Xtime++)
			{
				OLED_DrawLine(Xtime-1,63-adc_value[TG+Xtime-1],Xtime,63-adc_value[TG+Xtime],1);
				OLED_ShowString(112,16, str2,8,1);
			}
		}
		else
		{
			for(int Xtime=1;Xtime<127;Xtime++)
			{
				OLED_DrawLine(Xtime-1,63-adc_value[Xtime-1],Xtime,63-adc_value[Xtime],1);
			}
			OLED_ShowString(112,16, str1,8,1);
		}
		

    OLED_Refresh();
    delay_ns(1);
}


int Get_Triggervoltage(float Value)
{
	volatile uint16_t Trigger=0,Trigger_Count=0,Trigger_Count1=0,Trigger_Count2=0;
	Trigger_Count=3;
	while(Trigger_Count<128)
	{
		Trigger_Count++;
		Trigger_Count1=Trigger_Count+3;
		Trigger_Count2=Trigger_Count-3;
		if(Value==0 &&  fabs(adc_value[Trigger_Count]-Value) <= 2  && adc_value[Trigger_Count1]>=Value+3)
		{
			Trigger=Trigger_Count;	
			break;
		}
		else if(Value!=0 && fabs(adc_value[Trigger_Count]-Value) <= 2 && adc_value[Trigger_Count2]<=Value-3)
		{
			Trigger=Trigger_Count;
			break;				
		}
	}
	return Trigger;
}


