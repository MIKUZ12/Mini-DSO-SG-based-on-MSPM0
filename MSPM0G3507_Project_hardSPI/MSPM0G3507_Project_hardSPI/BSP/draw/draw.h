#ifndef __DRAW_H
#define __DRAW_H

void draw_axis(void);
void draw_wave(int TG);
extern int freq;
extern unsigned int adc_value[128];

int Get_Triggervoltage(float Value);
#endif