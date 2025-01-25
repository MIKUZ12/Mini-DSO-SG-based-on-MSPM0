#include "adc.h"
#include "stdlib.h"
#include "draw.h"


volatile bool gCheckADC;        //ADC采集成功标志位
unsigned int adc_getValue(unsigned int number);//读取ADC的数据
volatile uint16_t ADC_VALUE[2560];

//读取ADC的数据
unsigned int adc_getValue(unsigned int number)
{
        unsigned int gAdcResult = 0;
        unsigned char i = 0;


        for( i = 0; i < number; i++ )
        {
                gAdcResult += ADC_VALUE[i];
        }

        gAdcResult /= number;

        return gAdcResult;
}

////ADC中断服务函数
//void ADC_VOLTAGE_INST_IRQHandler(void)
//{
//        //查询并清除ADC中断
//        switch (DL_ADC12_getPendingInterrupt(ADC_VOLTAGE_INST)) 
//        {
//                        //检查是否完成数据采集
//                        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
//                                        gCheckADC = true;//将标志位置1
//                                        break;
//                        default:
//                                        break;
//        }
//}
