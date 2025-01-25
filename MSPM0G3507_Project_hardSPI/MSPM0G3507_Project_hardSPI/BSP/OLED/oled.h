#ifndef __OLED_H
#define __OLED_H 

#include "board.h"
#include "stdlib.h"	


#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

//-----------------OLED端口定义---------------- 

//#define OLED_SCL_Clr() DL_GPIO_clearPins(GPIO_PORT,GPIO_SCL_PIN)//SCL=SCLK
//#define OLED_SCL_Set() DL_GPIO_setPins(GPIO_PORT,GPIO_SCL_PIN)

//#define OLED_SDA_Clr() DL_GPIO_clearPins(GPIO_PORT,GPIO_SDA_PIN)//SDA=MOSI
//#define OLED_SDA_Set() DL_GPIO_setPins(GPIO_PORT,GPIO_SDA_PIN)


#define OLED_RES_Clr()  DL_GPIO_clearPins(GPIO_PORT,GPIO_RES_PIN)//RES
#define OLED_RES_Set()  DL_GPIO_setPins(GPIO_PORT,GPIO_RES_PIN)

#define OLED_DC_Clr()   DL_GPIO_clearPins(GPIO_PORT,GPIO_DC_PIN)//DC
#define OLED_DC_Set()   DL_GPIO_setPins(GPIO_PORT,GPIO_DC_PIN)

#define OLED_CS_Clr()   DL_GPIO_clearPins(GPIO_PORT,GPIO_CS_PIN)//CS
#define OLED_CS_Set()   DL_GPIO_setPins(GPIO_PORT,GPIO_CS_PIN)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


// 函数声明


void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_GClear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

