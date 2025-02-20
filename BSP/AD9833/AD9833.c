
#include "AD9833.h"
#include "stdlib.h"
#include "Encoder.h"
#include "stdio.h"
#include "ti_msp_dl_config.h"
//#include "common.h"



//***************************
//		Pin assign	   	
//			STM32			AD9833
//		GPIOB_Pin_15 		---> FSYNC
//		GPIOB_Pin_14 		---> SCK
//		GPIOB_Pin_13 		---> DAT
//		GPIOB_Pin_12		---> CS
//***************************	

	/*端口定义 */ 
//	#define PORT_FSYNC	GPIOB
//	#define PIN_FSYNC	GPIO_Pin_15

//	#define PORT_SCK	GPIOB
//	#define PIN_SCK		GPIO_Pin_14

//	#define PORT_DAT	GPIOB
//	#define PIN_DAT		GPIO_Pin_13

//	#define PORT_CS		GPIOB
//	#define PIN_CS		GPIO_Pin_12  //数字电位器片选



//初始化AD9833 GPIO

//void AD9833_Init_GPIO()
//{
//    GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

//	GPIO_InitStructure.GPIO_Pin = PIN_FSYNC|PIN_SCK|PIN_DAT|PIN_CS; 
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(PORT_SCK, &GPIO_InitStructure);
//}

//变量定义






/*
*********************************************************************************************************
*	函 数 名: AD9833_Delay
*	功能说明: 时钟延时
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AD9833_Delay(void)
{
	uint16_t i;
	for (i = 0; i < 1; i++);
}



/*
*********************************************************************************************************
*	函 数 名: AD9833_Write
*	功能说明: 向SPI总线发送16个bit数据
*	形    参: TxData : 数据
*	返 回 值: 无
*********************************************************************************************************
*/
void AD9833_Write(unsigned int TxData)
{
	unsigned char i;

	SCK_1();
	//AD9833_Delay();
	FSYNC_1();
	//AD9833_Delay();
	FSYNC_0();
	//AD9833_Delay();
	for(i = 0; i < 16; i++)
	{
		if (TxData & 0x8000)
			DAT_1();
		else
			DAT_0();
		
		AD9833_Delay();
		SCK_0();
		AD9833_Delay();		
		SCK_1();
		
		TxData <<= 1;
	}
	FSYNC_1();
	
} 

/*
*********************************************************************************************************
*	函 数 名: AD9833_AmpSet
*	功能说明: 改变输出信号幅度值
*	形    参: 1.amp ：幅度值  0- 255
*	返 回 值: 无
*********************************************************************************************************
*/ 


void AD9833_AmpSet(unsigned char amp)
{
	unsigned char i;
	unsigned int temp;
   	
	CS_0();
	temp =0x1100|amp;
	for(i=0;i<16;i++)
	{
	    SCK_0();	
	   if(temp&0x8000)
	   	DAT_1();
	   else
		DAT_0();
		temp<<=1;
	    SCK_1();
	    AD9833_Delay();
	}
	
   	CS_1();
}


/*
*********************************************************************************************************
*	函 数 名: AD9833_WaveSeting
*	功能说明: 向SPI总线发送16个bit数据
*	形    参: 1.Freq: 频率值, 0.1 hz - 12Mhz
			  2.Freq_SFR: 0 或 1
			  3.WaveMode: TRI_WAVE(三角波),SIN_WAVE(正弦波),SQU_WAVE(方波)
			  4.Phase : 波形的初相位
*	返 回 值: 无
*********************************************************************************************************
*/ 
void AD9833_WaveSeting(double Freq,unsigned int Freq_SFR,unsigned int WaveMode,unsigned int Phase )
{

		int frequence_LSB,frequence_MSB,Phs_data;
		double   frequence_mid,frequence_DATA;
		long int frequence_hex;

		/*********************************计算频率的16进制值***********************************/
		frequence_mid=268435456/25;//适合25M晶振
		//如果时钟频率不为25MHZ，修改该处的频率值，单位MHz ，AD9833最大支持25MHz
		frequence_DATA=Freq;
		frequence_DATA=frequence_DATA/1000000;
		frequence_DATA=frequence_DATA*frequence_mid;
		frequence_hex=frequence_DATA;  //这个frequence_hex的值是32位的一个很大的数字，需要拆分成两个14位进行处理；
		frequence_LSB=frequence_hex; //frequence_hex低16位送给frequence_LSB
		frequence_LSB=frequence_LSB&0x3fff;//去除最高两位，16位数换去掉高位后变成了14位
		frequence_MSB=frequence_hex>>14; //frequence_hex高16位送给frequence_HSB
		frequence_MSB=frequence_MSB&0x3fff;//去除最高两位，16位数换去掉高位后变成了14位

		Phs_data=Phase|0xC000;	//相位值
		AD9833_Write(0x0100); //复位AD9833,即RESET位为1
		AD9833_Write(0x2100); //选择数据一次写入，B28位和RESET位为1

		if(Freq_SFR==0)				  //把数据设置到设置频率寄存器0
		{
		 	frequence_LSB=frequence_LSB|0x4000;
		 	frequence_MSB=frequence_MSB|0x4000;
			 //使用频率寄存器0输出波形
			AD9833_Write(frequence_LSB); //L14，选择频率寄存器0的低14位数据输入
			AD9833_Write(frequence_MSB); //H14 频率寄存器的高14位数据输入
			AD9833_Write(Phs_data);	//设置相位
			//AD9833_Write(0x2000); /**设置FSELECT位为0，芯片进入工作状态,频率寄存器0输出波形**/
	    }
		if(Freq_SFR==1)				//把数据设置到设置频率寄存器1
		{
			 frequence_LSB=frequence_LSB|0x8000;
			 frequence_MSB=frequence_MSB|0x8000;
			//使用频率寄存器1输出波形
			AD9833_Write(frequence_LSB); //L14，选择频率寄存器1的低14位输入
			AD9833_Write(frequence_MSB); //H14 频率寄存器1为
			AD9833_Write(Phs_data);	//设置相位
			//AD9833_Write(0x2800); /**设置FSELECT位为0，设置FSELECT位为1，即使用频率寄存器1的值，芯片进入工作状态,频率寄存器1输出波形**/
		}

		if(WaveMode==TRI_WAVE) //输出三角波波形
		 	AD9833_Write(0x2002); 
		if(WaveMode==SQU_WAVE)	//输出方波波形
			AD9833_Write(0x2028); 
		if(WaveMode==SIN_WAVE)	//输出正弦波形
			AD9833_Write(0x2000); 

}

//void AD9833_wave_fre_amp_phase_change(void)//0--1hz,1--10hz,2--100hz,3--1khz,4--V,5--phase
//{
//				if( DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) == 0 )//采用key1按键，即旋转编码器按键
//				{
//					delay_us(1);
//					if( DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) == 0 )
//					{
//						if(wave_fre_amp_phase < 6)
//						{
//							wave_fre_amp_phase++;
//						}
//						else
//						{
//							wave_fre_amp_phase = 0;
//						}//限幅
//					}
//				}
//				else
//				{
//						DL_GPIO_clearPins(GPIO_GRP_0_PORT,GPIO_GRP_0_PIN_4_PIN);
//				}
				
//}

//void AD9833_num_change(void)
//{
//	int Encoder_Count_temp = Encoder_Count + 1;//////////////////////////////////////////////////
//	switch (wave_fre_amp_phase)
//	{
//		case 0:
//			if(wave_fre_num_1 < 10)
//			{
//				wave_fre_num_1 = Encoder_Count_temp;
//			}
//			else
//			{
//				wave_fre_num_1 =0;
//			}
//		case 1:
//			if(wave_fre_num_10 < 10)
//			{
//				wave_fre_num_10 = Encoder_Count_temp;
//			}
//			else
//			{
//				wave_fre_num_10 = 0;
//			}
//		case 2:
//			if(wave_fre_num_100 < 10)
//			{
//				wave_fre_num_100 = Encoder_Count_temp;
//			}
//			else
//			{
//				wave_fre_num_100 = 0;
//			}
//		case 3:
//			if(wave_fre_num_1k < 10)
//			{
//				wave_fre_num_1k = Encoder_Count_temp;
//			}
//			else
//			{
//				wave_fre_num_10 = 0;
//			}
//		case 4:
//			if(wave_amp_num <= 250)//设置最大幅值
//			{
//				wave_amp_num = Encoder_Count_temp;
//			}
//			else
//			{
//				wave_amp_num = 10;//设置最小幅值
//			}
//		default:
//			if(wave_phase_num <= 360)//设置最大相位
//			{
//				wave_phase_num = Encoder_Count_temp;
//			}
//			else
//			{
//				wave_phase_num = 0;//设置最小相位
//			}
//		}
//		wave_fre = wave_fre_num_1k *1000 + wave_fre_num_100 *100 + wave_fre_num_10 *10 + wave_fre_num_1 *1;
//}


//void AD9833_wave_select(void)
//{
//		if( DL_GPIO_readPins(KEY_PORT, KEY_KEY_3_PIN) == 0 )
//		{
//				delay_us(1);
//			  printf("wave_select");
//				if( DL_GPIO_readPins(KEY_PORT, KEY_KEY_3_PIN) == 0 )
//				{
//					wave_select++;
//					printf("%u",wave_select);
//					if (wave_select > 2) 
//					{
//							wave_select = 0;
//					}
//				}
//		}		
//}


//void AD9833_wave_output(void)
//{
//	AD9833_wave_fre_amp_phase_change();
//	AD9833_num_change();
//	wave_fre = wave_fre_num_1k *1000 + wave_fre_num_100 *100 + wave_fre_num_10 *10 + wave_fre_num_1 *1;
//	AD9833_WaveSeting(wave_fre ,1,wave_select, wave_phase_num);
//	AD9833_AmpSet(wave_amp_num);
//	
//}


