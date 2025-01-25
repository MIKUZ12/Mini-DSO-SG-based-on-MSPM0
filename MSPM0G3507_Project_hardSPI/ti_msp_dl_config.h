/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)




/* Defines for SPI_LCD */
#define SPI_LCD_INST                                                       SPI1
#define SPI_LCD_INST_IRQHandler                                 SPI1_IRQHandler
#define SPI_LCD_INST_INT_IRQN                                     SPI1_INT_IRQn
#define GPIO_SPI_LCD_PICO_PORT                                            GPIOB
#define GPIO_SPI_LCD_PICO_PIN                                     DL_GPIO_PIN_8
#define GPIO_SPI_LCD_IOMUX_PICO                                 (IOMUX_PINCM25)
#define GPIO_SPI_LCD_IOMUX_PICO_FUNC                 IOMUX_PINCM25_PF_SPI1_PICO
/* GPIO configuration for SPI_LCD */
#define GPIO_SPI_LCD_SCLK_PORT                                            GPIOB
#define GPIO_SPI_LCD_SCLK_PIN                                     DL_GPIO_PIN_9
#define GPIO_SPI_LCD_IOMUX_SCLK                                 (IOMUX_PINCM26)
#define GPIO_SPI_LCD_IOMUX_SCLK_FUNC                 IOMUX_PINCM26_PF_SPI1_SCLK



/* Defines for ADC_VOLTAGE */
#define ADC_VOLTAGE_INST                                                    ADC0
#define ADC_VOLTAGE_INST_IRQHandler                              ADC0_IRQHandler
#define ADC_VOLTAGE_INST_INT_IRQN                                (ADC0_INT_IRQn)
#define ADC_VOLTAGE_ADCMEM_ADC_CH0                            DL_ADC12_MEM_IDX_0
#define ADC_VOLTAGE_ADCMEM_ADC_CH0_REF           DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC_VOLTAGE_ADCMEM_ADC_CH0_REF_VOLTAGE                                      -1 // VDDA cannot be determined
#define GPIO_ADC_VOLTAGE_C0_PORT                                           GPIOA
#define GPIO_ADC_VOLTAGE_C0_PIN                                   DL_GPIO_PIN_27



/* Defines for DMA_CH0 */
#define DMA_CH0_CHAN_ID                                                      (0)
#define ADC_VOLTAGE_INST_DMA_TRIGGER                  (DMA_ADC0_EVT_GEN_BD_TRIG)



/* Port definition for Pin Group GPIO_GRP_0 */
#define GPIO_GRP_0_PORT                                                  (GPIOA)

/* Defines for PIN_4: GPIOA.1 with pinCMx 2 on package pin 2 */
#define GPIO_GRP_0_PIN_4_PIN                                     (DL_GPIO_PIN_1)
#define GPIO_GRP_0_PIN_4_IOMUX                                    (IOMUX_PINCM2)
/* Port definition for Pin Group GPIO */
#define GPIO_PORT                                                        (GPIOA)

/* Defines for RES: GPIOA.21 with pinCMx 46 on package pin 39 */
#define GPIO_RES_PIN                                            (DL_GPIO_PIN_21)
#define GPIO_RES_IOMUX                                           (IOMUX_PINCM46)
/* Defines for DC: GPIOA.22 with pinCMx 47 on package pin 40 */
#define GPIO_DC_PIN                                             (DL_GPIO_PIN_22)
#define GPIO_DC_IOMUX                                            (IOMUX_PINCM47)
/* Defines for CS: GPIOA.2 with pinCMx 7 on package pin 8 */
#define GPIO_CS_PIN                                              (DL_GPIO_PIN_2)
#define GPIO_CS_IOMUX                                             (IOMUX_PINCM7)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for PIN_18: GPIOA.18 with pinCMx 40 on package pin 33 */
// groups represented: ["Encoder","KEY"]
// pins affected: ["A","PIN_18"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define KEY_PIN_18_IIDX                                     (DL_GPIO_IIDX_DIO18)
#define KEY_PIN_18_PIN                                          (DL_GPIO_PIN_18)
#define KEY_PIN_18_IOMUX                                         (IOMUX_PINCM40)
/* Defines for KEY1: GPIOA.7 with pinCMx 14 on package pin 13 */
#define KEY_KEY1_PIN                                             (DL_GPIO_PIN_7)
#define KEY_KEY1_IOMUX                                           (IOMUX_PINCM14)
/* Defines for KEY2: GPIOA.9 with pinCMx 20 on package pin 17 */
#define KEY_KEY2_PIN                                             (DL_GPIO_PIN_9)
#define KEY_KEY2_IOMUX                                           (IOMUX_PINCM20)
/* Defines for KEY_3: GPIOA.8 with pinCMx 19 on package pin 16 */
#define KEY_KEY_3_PIN                                            (DL_GPIO_PIN_8)
#define KEY_KEY_3_IOMUX                                          (IOMUX_PINCM19)
/* Port definition for Pin Group Encoder */
#define Encoder_PORT                                                     (GPIOA)

/* Defines for A: GPIOA.12 with pinCMx 34 on package pin 27 */
#define Encoder_A_IIDX                                      (DL_GPIO_IIDX_DIO12)
#define Encoder_A_PIN                                           (DL_GPIO_PIN_12)
#define Encoder_A_IOMUX                                          (IOMUX_PINCM34)
/* Defines for B: GPIOA.13 with pinCMx 35 on package pin 28 */
#define Encoder_B_PIN                                           (DL_GPIO_PIN_13)
#define Encoder_B_IOMUX                                          (IOMUX_PINCM35)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_LCD_init(void);
void SYSCFG_DL_ADC_VOLTAGE_init(void);
void SYSCFG_DL_DMA_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
