/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "board.h"
#include <stdio.h>
#include "oled.h"
#include "adc.h"
#include "draw.h"
#include "bmp.h"
#include "Encoder.h"
#include "key.h"
#include "AD9833.h"
#include "math.h"

int DSO(void);
void SG(void);
unsigned char str[] = "zoom:";
unsigned char str_mode[] = "mode:";
unsigned char str_tri[] = "triV:";
unsigned char str_freq[] = "freq:";

unsigned char strf[] = "freq:";
unsigned char strw[] = "wave:";
unsigned char stra[] = "amp:";
unsigned char strp[] = "phase:";
unsigned char Param[] = "param:";
unsigned char Fmode[] = "fmode:";
/***********oled成功示例*******************/
int main(void)
{
    //开发板初始化
    board_init();
    OLED_Init();    //初始化OLED
    OLED_Clear();
	
		SYSCFG_DL_init();
        
    //清除串口中断标志
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    //开启串口中断
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

		NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);

    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC0->ULLMEM.MEMRES[0]);

    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC_VALUE[0]);

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
	
	  DL_ADC12_startConversion(ADC_VOLTAGE_INST);
		
		volatile unsigned int voltage_value = 0;
		int flag = 0;
		int mode = 1;
		int step = 0; 
		int adc_value_now;
		int trigger = 0;
		int trigger_value = 0;
		float true_trigger;
		int switch1 = 0;
		
			
		
    while(1) 
    {
				
				OLED_GClear();

				Encoder_Count = Encoder_Get();
			  Encoder_Count0 = Encoder0_Get();//here
			  Encoder_Count1 = Encoder1_Get();//here
				
				
			
				int menu = draw_menu();
				if(menu == 0)
				{
					flag = DSO();
				}	
				if(menu == 1)
				{
					SG();
				}

		}
							
}							


				


int DSO(void)
{
	Encoder_Count = 0;
	Encoder_Count0 = 0;
	Encoder_Count1 = 0;
	int adc_value_now;
	int trigger = 0;
	int trigger_value,last_trigger_value = 0;
	float true_trigger;
	int switch1 = 0;          
	int last_encoder_value = 0;  
	int encoder_delta,current_encoder_value;
	int last_freq = 0;
	int real_freq = 0;
	while(1)
	{
		draw_axis();
		key_stop();
		Encoder_Count = Encoder_Get();
		Encoder_Count0 = Encoder0_Get();//here
		Encoder_Count1 = Encoder1_Get();//here
//		printf("%d",Encoder_Count);
		if( DL_GPIO_readPins(KEY_PORT, KEY_KEY_3_PIN) == 0 )
		{
			delay_ms(1);
			if( DL_GPIO_readPins(KEY_PORT, KEY_KEY_3_PIN) == 0 )
			{
				switch1 ++;
				switch1 %= 2;
			}
		}
		switch(switch1)
		{
			case 0:
				FLAG = 0;
				trigger_value = Encoder_Count0;//here
				if(trigger_value > 47)
				{
					Encoder_Count0 = 47;//here
				}
				if(trigger_value < 0)
				{
					Encoder_Count0 = 0;//here
				}

				OLED_ShowString(1,0, str_tri,8,0);
				OLED_ShowString(72,0, str,8,1);
				OLED_ShowString(72,8, str_mode,8,1);
				break;
			case 1:
				FLAG = 1;
				freq = Encoder_Count1;//here
				if (freq <= 0)
				{
						freq += 12; 
				}
				freq %= 12;
				freq ++;
				OLED_ShowString(1,0, str_tri,8,1);
				OLED_ShowString(72,0, str,8,0);
				OLED_ShowString(72,8, str_mode,8,1);
				break;
		}

		OLED_ShowNum(112,0,freq,2,8,1);
		OLED_DrawXLine(0,63-trigger_value,127,63-trigger_value);
		trigger = Get_Triggervoltage(trigger_value);
		true_trigger = trigger_value*7.0/100;
		for(int i = 0; i < 256; i++)
		{
			adc_value[i] = (int)((ADC_VALUE[i*freq]/4095.0*3.3)*100)/7;
		}
		real_freq = getWaveFreq();
		OLED_ShowFNum(32,0,true_trigger,1);
		OLED_ShowString(1,8, str_freq,8,1);
		OLED_ShowNum(32,8,real_freq,4,8,1);
		draw_wave(trigger);
		
		delay_ms(10);
		if(flag == 1)
		{
			flag = 0;
			return flag;
		}
	}
}

void SG(void)
{
		Encoder_Count0 = 0;
		Encoder_Count1 = 100;
		Encoder_Count2 = 50;
	  Encoder_Count3 = 0;
		unsigned wave_select = 0;
		
		int wave_fre_select = 0;
		int wave_fre_num_1	= 1;
		int wave_fre_num_10	= 0;
		int wave_fre_num_100	= 0;
		int wave_fre_num_1k	= 1;
		int wave_fre = 1000;
		unsigned char wave_amp_num = 50;
		unsigned int wave_phase_num = 0;
	
		int param = 0;
		OLED_GClear();

    while(1) 
    {

				draw_axis1();
			  OLED_Refresh();			
				if(!DL_GPIO_readPins(KEY_PORT, KEY_KEY_3_PIN))
					{
							delay_us(1);

							if(!DL_GPIO_readPins(KEY_PORT, KEY_KEY_3_PIN))
							{
								param++;
								param = param%4;
							}
					}


			switch(param)
			{
				case 0:
					FLAG = 0;
					wave_select = Encoder_Count0;
					wave_select %= 3;
					OLED_ShowString(1,0,strw,8,0);
					OLED_ShowString(1,8,strf,8,1);
          OLED_ShowString(70,0,stra,8,1);
		      OLED_ShowString(70,8,strp,8,1);
					if(wave_select == 0)
					{
						OLED_GClear_area();
						OLED_DrawLine(24,56,64,22,1);
						OLED_DrawLine(64,22,104,56,1);

					}
					else if(wave_select == 1)
					{
						OLED_GClear_area();
						OLED_DrawSin();
					}
					else if(wave_select == 2)
					{
						OLED_GClear_area();
						OLED_DrawLine(24,56,24,22,1);
						OLED_DrawLine(24,22,64,22,1);
						OLED_DrawLine(64,56,64,22,1);
						OLED_DrawLine(64,56,104,56,1);
						OLED_DrawLine(104,56,104,22,1);

					}
					break;
				case 1:
						FLAG = 1;
						wave_fre = Encoder_Count1*10;
					  wave_fre %= 1001;
//						if(!DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN))//采用key1按键，即旋转编码器按键
//						{
//							delay_us(1);
//							if(!DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN))
//							{
//									wave_fre_select++;
//									wave_fre_select %=4;
//							}
//						}	
//						switch(wave_fre_select)
//						{
//							case 0:
//								wave_fre_num_1 =Encoder_Count1;
//								wave_fre_num_1 %= 10;
//							case 1:
//								wave_fre_num_10 =Encoder_Count1;
//								wave_fre_num_10 %= 10;							
//							case 2:
//								wave_fre_num_100 =Encoder_Count1;
//								wave_fre_num_100 %= 10;							
//							case 3:
//								wave_fre_num_1k =Encoder_Count1;
//								wave_fre_num_1k %= 10;							
//						}
//						wave_fre = wave_fre_num_1k *1000 + wave_fre_num_100 *100 + wave_fre_num_10 *10 + wave_fre_num_1 *1;
					OLED_ShowString(1,0,strw,8,1);
					OLED_ShowString(1,8,strf,8,0);
          OLED_ShowString(70,0,stra,8,1);
		      OLED_ShowString(70,8,strp,8,1);
					break;
				case 2:
					FLAG = 2;
					wave_amp_num = Encoder_Count2;
					wave_amp_num %= 250;
					OLED_ShowString(1,0,strw,8,1);
					OLED_ShowString(1,8,strf,8,1);
          OLED_ShowString(70,0,stra,8,0);
		      OLED_ShowString(70,8,strp,8,1);
				  break;
				case 3:
					FLAG = 3;
					wave_phase_num = Encoder_Count3;
					wave_phase_num %= 360;
					OLED_ShowString(1,0,strw,8,1);
					OLED_ShowString(1,8,strf,8,1);
          OLED_ShowString(70,0,stra,8,1);
		      OLED_ShowString(70,8,strp,8,0);
				  break;
			}	
			  
				AD9833_WaveSeting(wave_fre ,1,wave_select, wave_phase_num);

				AD9833_AmpSet(wave_amp_num);
			
				
				OLED_ShowNum(32,0,wave_select,2,8,1);
				OLED_ShowNum(32,8,wave_fre,4,8,1);
				OLED_ShowNum(110,0,wave_amp_num,3,8,1);
				OLED_ShowNum(110,8,wave_phase_num,3,8,1);

					if(flag == 1)
					{
						flag = 0;
						return;
					}				
     }
}