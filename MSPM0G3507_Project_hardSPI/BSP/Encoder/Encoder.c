#include "Encoder.h"
#include "stdlib.h"
#include "board.h"
#include "draw.h"
#include "ti_msp_dl_config.h"


int Encoder_Count;


int Encoder_Get(void)
{
	int Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}

void GROUP1_IRQHandler(void)
{
	int Encodeg_flag,A_flag,B_flag,direction_flag;
	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
	{
		case KEY_PIN_18_IIDX:
						freq += 1;
						if(freq > 10)
						{
							freq = 1;
						}
		case Encoder_A_IIDX:
		if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_A_PIN))
		{
            Encodeg_flag = 1;//A中断
            if(DL_GPIO_readPins(GPIOA, Encoder_A_PIN)) A_flag = 1;
            else A_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_B_PIN)) B_flag = 1;
            else B_flag = 0;
            direction_flag = A_flag+B_flag+Encodeg_flag;//求和判断转动方向，偶数正转，奇数反转
            if(direction_flag == 0 || direction_flag ==2)Encoder_Count++;
            else Encoder_Count--;
            
			DL_GPIO_clearInterruptStatus(GPIOA, Encoder_A_PIN);
		}
		
		if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_B_PIN))
		{
            Encodeg_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_A_PIN)) A_flag = 1;
            else A_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_B_PIN)) B_flag = 1;
            else B_flag = 0;
            direction_flag = A_flag+B_flag+Encodeg_flag;
            if(direction_flag == 0 || direction_flag ==2)Encoder_Count++;
            else Encoder_Count--;
            
			DL_GPIO_clearInterruptStatus(GPIOA, Encoder_B_PIN);
		}
 
		break;
	}
}
