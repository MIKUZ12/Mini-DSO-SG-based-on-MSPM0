#include "adc.h"
#include "stdlib.h"
#include "draw.h"


volatile bool gCheckADC;        //ADC�ɼ��ɹ���־λ
unsigned int adc_getValue(unsigned int number);//��ȡADC������
volatile uint16_t ADC_VALUE[2560];

//��ȡADC������
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

////ADC�жϷ�����
//void ADC_VOLTAGE_INST_IRQHandler(void)
//{
//        //��ѯ�����ADC�ж�
//        switch (DL_ADC12_getPendingInterrupt(ADC_VOLTAGE_INST)) 
//        {
//                        //����Ƿ�������ݲɼ�
//                        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
//                                        gCheckADC = true;//����־λ��1
//                                        break;
//                        default:
//                                        break;
//        }
//}
