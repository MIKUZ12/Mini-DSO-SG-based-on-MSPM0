#include "oled.h"
#include "stdlib.h"
#include "board.h"
#include "math.h"
#include "encoder.h"
#include "stdio.h"
#include "adc.h"



int voltage_row[128]={0};
unsigned int adc_value[256] = {0};

int freq = 1;
unsigned char str1[] = "NA";
unsigned char str2[] = "YE";
unsigned char str_menu1[] = "MINI-DSO";
unsigned char str_menu2[] = "MINI-SG";
int draw_menu(void)
{
	int main_menu = 0;
	while(1)
	{
		Encoder_Count = Encoder_Get();
		main_menu = abs(Encoder_Count)%2;
		OLED_ShowString(32,16,str_menu1,16,main_menu);
		OLED_ShowString(32,34,str_menu2,16,(main_menu+1)%2);
		OLED_Refresh();
		if( DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) == 0 )
				{
					delay_us(1);
					if( DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) == 0 )
					{
						return main_menu;
					}
				}
	}
}

void draw_axis(void)
{
				OLED_DrawLine(0,17,0,64,1);
				OLED_DrawLine(0,63,128,63,1);//axis
				OLED_DrawLine(127,17,127,64,1);
			  OLED_DrawLine(0,17,128,17,1);
				

				OLED_DrawLine(0,17,4,17,1);
				OLED_DrawLine(0,24,3,24,1);
				OLED_DrawLine(0,32,4,32,1);
				OLED_DrawLine(0,40,3,40,1);
				OLED_DrawLine(0,48,4,48,1);
				OLED_DrawLine(0,56,3,56,1);
				OLED_DrawLine(0,63,4,63,1);//vertical index

}	
void draw_axis1(void)
{
				OLED_DrawLine(0,17,0,64,1);
				OLED_DrawLine(0,63,128,63,1);//axis
				OLED_DrawLine(127,17,127,64,1);
			  OLED_DrawLine(0,17,128,17,1);


}	

void OLED_DrawSin(void)
{
    u8 x0 = 64, y0 = 24;  
    float Si, Sx, Sy, Rad;  

    for (Si = -180; Si < 180; Si += 1)  
    {
        Rad = Si * 3.14 / 180;         
        Sx = Si / 3.5;                  
        Sy = sin(Rad) * 15;            

        OLED_DrawPoint((int)(Sx + x0), (int)(64 - (Sy + y0)),1);
    }

}



void draw_wave(int TG)
{
    u8 Xtime;
		
			for(int Xtime=1;Xtime<127;Xtime++)
			{

				OLED_DrawLine(Xtime-1,63-adc_value[TG+Xtime-1],Xtime,63-adc_value[TG+Xtime],1);
				
				if(TG!=0)
				{
					OLED_ShowString(112,8, str2,8,1);
				}
				else
				{
					OLED_ShowString(112,8, str1,8,1);
				}
			}

    OLED_Refresh();
		
			
		OLED_GClear();
    delay_ms(1);
}


int Get_Triggervoltage(float Value)
{
	volatile uint16_t Trigger=0,Trigger_Count=0,Trigger_Count1=0;

	while(Trigger_Count<128)
	{
		
		Trigger_Count1=Trigger_Count+3;
		
		if(fabs(adc_value[Trigger_Count]-Value)<=freq  && adc_value[Trigger_Count1]>=Value+freq)
		{
			Trigger=Trigger_Count;
			break;				
		}
		Trigger_Count++;
	}
	return Trigger;
}

int getWaveFreq(void)
{
    int i=0;
        int FLAG=0;
      int Pos1=0;
        int Pos2=0;
        int real_freq;
    while(FLAG <4)
        {            
            if((ADC_VALUE[i]<ADC_VALUE[i+1])&&(ADC_VALUE[i+1]>ADC_VALUE[i+2]))
            {
                FLAG++;
                if(FLAG==1)
                {
                    Pos1=i+1;
                }
                else if(FLAG==4)
                {
                    Pos2=i+1;
                }
            }
            i++;
        }
        real_freq=32000/((Pos2-Pos1));
        return real_freq;
}


