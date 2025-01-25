#include "key.h"
#include "stdlib.h"
#include "board.h"
#include "math.h"
volatile bool isInDeadLoop = false;
void key_stop(void)
{
	 if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
				{

            delay_us(1); 
            if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
						{ 
                while (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0); 

                isInDeadLoop = !isInDeadLoop; 
            }
        }

        if (isInDeadLoop) 
				{   
						while (isInDeadLoop) 
						{
                if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
								{
                    delay_us(1);
                    if (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0) 
										{ 
                        while (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) == 0); 
                        isInDeadLoop = false; 
                    }
                }
            }
        }
}