/*NAVYA NANJUNDAIAH
 * Switched Internal LED
 * This program uses PA6 for external switch and uses Port B to output data to turn on/off external LED.
 * Also the timer has been used to control the time of LED on/off.
 */
 
#include <stdint.h>
#include <math.h>
#include "inc/tm4c123gh6pm.h"

// One Second Delay
void One_Second_Delay(void)
{ 
    NVIC_ST_CTRL_R = 0;            				// (1) disable SysTick during setup
    NVIC_ST_RELOAD_R = 16000000-1;   			// (2) Reload Value goes here
    NVIC_ST_CTRL_R |= 0x5;         				// (4) enable SysTick with core clock
 
    while((NVIC_ST_CTRL_R & (1<<16)) == 0)
        ;                          				// Monitoring bit 16 to be set
		NVIC_ST_CTRL_R = 0;										// (4) Disabling SysTick Timer
}

int main (void)
{
	uint32_t btn_state, flag=0, i=0;
  SYSCTL_RCGCGPIO_R |= 0x00000020;   			// enable clock to GPIO PORTB at clock gating control register
  GPIO_PORTB_DIR_R = 0xFF;
  GPIO_PORTA_DIR_R = 0xBF;        				// enable digital I/O on PORTF
	GPIO_PORTA_PUR_R |= 0x40;							// enable SW at PA6
 
  GPIO_PORTB_DATA_R = 0x0E;      					// turn on LED 
		for(int i=0; i<7; i++)
			One_Second_Delay();      						// call one second delay
  GPIO_PORTB_DATA_R = 0x00;      					// turn off LED
		for(int i=0; i<7; i++)
			One_Second_Delay();      						// call one second delay

	while(1)
	{
		btn_state = GPIO_PORTA_DATA_R & 0x10;		//Ox00000010
		if(btn_state == 0x00)
		{
			flag = 1;
			if(i%8==1) {
				GPIO_PORTB_DATA_R = 0x01;				// turn on PB0 LED
			} else if(i%8==2) {
				GPIO_PORTB_DATA_R = 0x02;				// turn on PB1 LED
			} else if(i%8==3) {
				GPIO_PORTB_DATA_R = 0x04;				// turn on PB2 LED
			} else if(i%8==4) {
				GPIO_PORTB_DATA_R = 0x08;				// turn on PB3 LED 
			} else if(i%8==5) {
				GPIO_PORTB_DATA_R = 0x10;				// turn on PB4 LED 
			} else if(i%8==6) {
				GPIO_PORTB_DATA_R = 0x20;				// turn on PB5 LED 
			}else if(i%8==7) {
				GPIO_PORTB_DATA_R = 0x40;                               // turn on PB6 LED 
                        }else if(i%8==0) {
				GPIO_PORTB_DATA_R = 0x80;                               // turn on PB7 LED 

                        }
		}
		else
		{
			GPIO_PORTB_DATA_R = 0x80;
			if(flag==1) {
				i++;
			}
			flag = 0;
		}
		for(int j=0; j<16000; j++);             
	}
}
