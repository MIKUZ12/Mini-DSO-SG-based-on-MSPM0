#ifndef __DRAW_H
#define __DRAW_H

void draw_axis(void);
void draw_wave(int TG);
extern int freq;
extern unsigned int adc_value[256];
int getWaveFreq(void);
int draw_menu(void);
int Get_Triggervoltage(float Value);
#endif