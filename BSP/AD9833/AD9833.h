#ifndef __AD9833_H
#define __AD9833_H

#include "board.h"
#include "stdlib.h"	
//#include "stm32f10x.h"

/* Port definition for Pin Group AD9833 */
#define AD9833_PORT                                                      (GPIOB)

/* Defines for FSYNC: GPIOB.2 with pinCMx 15 on package pin 14 */
#define AD9833_FSYNC_PIN                                         (DL_GPIO_PIN_2)
#define AD9833_FSYNC_IOMUX                                       (IOMUX_PINCM15)
/* Defines for SCK: GPIOB.3 with pinCMx 16 on package pin 15 */
#define AD9833_SCK_PIN                                           (DL_GPIO_PIN_3)
#define AD9833_SCK_IOMUX                                         (IOMUX_PINCM16)
/* Defines for DAT: GPIOB.6 with pinCMx 23 on package pin 20 */
#define AD9833_DAT_PIN                                           (DL_GPIO_PIN_6)
#define AD9833_DAT_IOMUX                                         (IOMUX_PINCM23)
/* Defines for ad9833CS: GPIOB.7 with pinCMx 24 on package pin 21 */
#define AD9833_ad9833CS_PIN                                      (DL_GPIO_PIN_7)
#define AD9833_ad9833CS_IOMUX                                    (IOMUX_PINCM24)

//****************************************************************

	#define FSYNC_0()		DL_GPIO_clearPins(AD9833_PORT, AD9833_FSYNC_PIN)
	#define FSYNC_1()		DL_GPIO_setPins(AD9833_PORT, AD9833_FSYNC_PIN)

	#define SCK_0()		DL_GPIO_clearPins(AD9833_PORT, AD9833_SCK_PIN)
	#define SCK_1()		DL_GPIO_setPins(AD9833_PORT, AD9833_SCK_PIN)

	#define DAT_0()		DL_GPIO_clearPins(AD9833_PORT, AD9833_DAT_PIN)
	#define DAT_1()		DL_GPIO_setPins(AD9833_PORT, AD9833_DAT_PIN)

	#define CS_0()		DL_GPIO_clearPins(AD9833_PORT, AD9833_ad9833CS_PIN)
	#define CS_1()		DL_GPIO_setPins(AD9833_PORT, AD9833_ad9833CS_PIN)

#define TRI_WAVE 	0  		//输出三角波
#define SIN_WAVE 	1		//输出正弦波
#define SQU_WAVE 	2		//输出方波

//extern unsigned int wave_select;
//extern int wave_fre;
//extern unsigned char wave_amp_num ;
//extern unsigned int wave_phase_num;


void AD9833_WaveSeting(double frequence,unsigned int frequence_SFR,unsigned int WaveMode,unsigned int Phase );
void AD9833_AmpSet(unsigned char amp);

void AD9833_wave_select(void);
void AD9833_wave_fre_amp_phase_change(void);//0--1hz,1--10hz,2--100hz,3--1khz,4--V,5--phase
void AD9833_num_change(void);
//void AD9833_wave_output(void);


#endif




