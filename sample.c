/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "Drawing.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "TouchPanel/TouchPanel.h"
#include "adc/adc.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

extern int feeding;

int main(void)
{
	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	TP_Init();
	TouchPanel_Calibrate();
	LCD_start();	
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	enable_RIT();	
	init_timer(0,0x17D7840); 
	enable_timer(0); 
	init_timer(3,0x32DCD);  // 1/120 di secondo
	feeding=0;
	enable_timer(3);
	ADC_init();														/* ADC Initialization									*/
			
	LPC_PINCON->PINSEL1 |= (1<<21);   //inizialization of DAC
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
		
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
