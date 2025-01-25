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

volatile bool isInDeadLoop = false;
void check_key_press(void);
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

		NVIC_EnableIRQ(KEY_INT_IRQN);

    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC0->ULLMEM.MEMRES[0]);

    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC_VALUE[0]);

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
	
	  DL_ADC12_startConversion(ADC_VOLTAGE_INST);
		
		volatile unsigned int voltage_value = 0;
		unsigned char str[] = "freq:";
		unsigned char str1[] = "mode:";
		int mode = 1;
		int step = 0; 
		int adc_value_now;
		int trigger = 0;
	
    while(1) 
    {
				OLED_GClear();
				draw_axis();
			
				OLED_ShowNum(112,0,freq,2,8,1);
//				else
//				{
//						DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_PIN_4_PIN);
////						DL_GPIO_clearPins(LED1_PORT,LED1_PIN_14_PIN);
//						//OLED_ShowNum(112,16,mode,1,8,1);
//				}
				
				if( DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) <= 0 )
				{
					delay_us(1);
					if( DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) <= 0 )
					{
						DL_GPIO_setPins(GPIO_GRP_0_PORT,GPIO_GRP_0_PIN_4_PIN);  
					}
				}
				else
				{
						DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_PIN_4_PIN);
				}
				

				
        if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
				{
            delay_us(1); 
            if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
						{ 
                while (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0); 

                isInDeadLoop = !isInDeadLoop; 
            }
        }

        if (isInDeadLoop) 
				{   
						while (isInDeadLoop) 
						{
                if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
								{
                    delay_us(1);
                    if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
										{ 
                        while (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0); 
                        isInDeadLoop = false; 
                    }
                }
            }
        }
			
				
				adc_value_now = adc_getValue(10);
				OLED_ShowString(72,0, str,8,1);
				OLED_ShowString(72,16, str1,8,1);
				voltage_value = (int)((adc_value_now/4095.0*3.3)*100);
				
				
				adc_value[0] = voltage_value/6;
				for(int Xtime = 128; Xtime > 0; Xtime -= 1)
				{
						adc_value[Xtime] = adc_value[Xtime - 1];
				}


				
				
				trigger = Get_Triggervoltage(50);

				draw_wave(trigger);

				OLED_Refresh();
        
        delay_ns(1);

    }
}

void GROUP1_IRQHandler(void)
{
						freq *= 2;
						if(freq > 16)
						{
							freq = 1;
						}

}














