#include "encoder.h"
#include "draw.h"
#include "ti_msp_dl_config.h"
#include "board.h"
#include <stdio.h>


int Encoder_Count1 = 0;//here
int Encoder_Count0 = 0;//here
int Encoder_Count2 = 0;
int Encoder_Count3 = 0;
int Encoder_Count = 0;
int flag = 0;
int FLAG = 0;
int Encoder_Get(void)
{
	int Temp = 0;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}

int Encoder0_Get(void)
{
	int Temp = 0;
	Temp = Encoder_Count0;
	Encoder_Count0 = 0;
	return Temp;
}//here
int Encoder1_Get(void)
{
	int Temp = 0;
	Temp = Encoder_Count1;
	Encoder_Count1 = 0;
	return Temp;
}//here

//void GROUP1_IRQHandler(void)
//{
//		
//	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
//	{
//		case GPIO_MULTIPLE_GPIOA_INT_IIDX:
//				if(DL_GPIO_getEnabledInterruptStatus(GPIOA, KEY_PIN_18_PIN))
//				{		
//						flag = 1;
//						DL_GPIO_clearInterruptStatus(GPIOA, KEY_PIN_18_PIN);
//				}

//			 else if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_A_PIN))
//				{
//					if(!DL_GPIO_readPins(GPIOA,Encoder_B_PIN))
//					{
//							Encoder_Count--;
//					}
//					else
//					{
//							Encoder_Count++;
//					}
//				}

//			else if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_B_PIN))
//				{
//					if(!DL_GPIO_readPins(GPIOA,Encoder_A_PIN))
//					{
//							Encoder_Count--;
//					}
//					else
//					{
//							Encoder_Count++;
//					}
//				}
//		default:
//			break;
//	}
//}




//void GROUP1_IRQHandler(void)
//{	
//	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
//	{
//		case GPIO_MULTIPLE_GPIOA_INT_IIDX:
//				if(DL_GPIO_getEnabledInterruptStatus(GPIOA, KEY_PIN_18_PIN))
//				{		
//						flag = 1;
//						DL_GPIO_clearInterruptStatus(GPIOA, KEY_PIN_18_PIN);
//				}

//			 else if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_A_PIN))
//				{
//					if((!DL_GPIO_readPins(GPIOA,Encoder_B_PIN))&&(FLAG == 1))
//					{
//							Encoder_Count1--;
//						  Encoder_Count--;
//					}
//					else if((!DL_GPIO_readPins(GPIOA,Encoder_B_PIN))&&(FLAG == 0))
//					{
//							Encoder_Count0--;
//   						Encoder_Count--;
//					}
//					else if(DL_GPIO_readPins(GPIOA,Encoder_B_PIN)&&(FLAG == 1))
//					{
//							Encoder_Count1++;
//						  Encoder_Count++;
//					}
//			    else if(DL_GPIO_readPins(GPIOA,Encoder_B_PIN)&&(FLAG == 0))
//					{
//							Encoder_Count0++;
//						  Encoder_Count++;
//					}				
//				}

//			else if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_B_PIN))
//				{
//					if((!DL_GPIO_readPins(GPIOA,Encoder_A_PIN))&&(FLAG == 1))
//					{
//							Encoder_Count1--;
//						  Encoder_Count--;
//					}
//					else if((!DL_GPIO_readPins(GPIOA,Encoder_A_PIN))&&(FLAG == 0))
//					{
//							Encoder_Count0--;
//						  Encoder_Count--;
//					}
//					else if(DL_GPIO_readPins(GPIOA,Encoder_A_PIN)&&(FLAG == 1))
//					{
//							Encoder_Count1++;
//						  Encoder_Count++;
//					}
//					else if(DL_GPIO_readPins(GPIOA,Encoder_A_PIN)&&(FLAG == 0))
//					{
//							Encoder_Count0++;
//						  Encoder_Count++;
//					}
//				}
//		default:
//			break;
//	}
//}here

void GROUP1_IRQHandler(void)
{
		
	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
	{
		case GPIO_MULTIPLE_GPIOA_INT_IIDX:
				if(DL_GPIO_getEnabledInterruptStatus(GPIOA, KEY_PIN_18_PIN))
				{		
						flag = 1;
						DL_GPIO_clearInterruptStatus(GPIOA, KEY_PIN_18_PIN);
				}

			 else if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_A_PIN))
				{
					if(!DL_GPIO_readPins(GPIOA,Encoder_B_PIN))
					{
							Encoder_Count++;
							if(FLAG == 1)
							{
								Encoder_Count1++;
							}
							else if(FLAG == 0)
							{
								Encoder_Count0++;
							}
							else if(FLAG == 2)
							{
								Encoder_Count2++;
							}
							else if(FLAG == 3)
							{
								Encoder_Count3++;
							}
					}
					else
					{
							Encoder_Count--;
						if(FLAG == 1)
							{
								Encoder_Count1--;
							}
							else if(FLAG == 0)
							{
								Encoder_Count0--;
							}
							else if(FLAG == 2)
							{
								Encoder_Count2--;
							}
							else if(FLAG == 3)
							{
								Encoder_Count3--;
							}
					}
				}

			else if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_B_PIN))
				{
					if(!DL_GPIO_readPins(GPIOA,Encoder_A_PIN))
					{
							Encoder_Count--;
							if(FLAG == 1)
							{
								Encoder_Count1--;
							}
							else if(FLAG == 0)
							{
								Encoder_Count0--;
							}
							else if(FLAG == 2)
							{
								Encoder_Count2--;
							}
							else if(FLAG == 3)
							{
								Encoder_Count3--;
							}
					}
					else
					{
							Encoder_Count++;
							if(FLAG == 1)
							{
								Encoder_Count1++;
							}
							else if(FLAG == 0)
							{
								Encoder_Count0++;
							}
							else if(FLAG == 2)
							{
								Encoder_Count2++;
							}
							else if(FLAG == 3)
							{
								Encoder_Count3++;
							}
					}
				}
		default:
			break;
	}
}




