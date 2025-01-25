#ifndef __ADC_H
#define __ADC_H 

#include "board.h"
#include "stdlib.h"	

unsigned int adc_getValue(unsigned int number);
extern  volatile uint16_t ADC_VALUE[20];

#endif