/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h" 
#include "../Drawing.h"
#include "../joystick/joystick.h"
#include "../adc/adc.h"
#include "../sound/music.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern uint8_t sec;
extern uint8_t min;
extern uint8_t hour;
extern char time[11];
volatile int feeding;

void RIT_IRQHandler (void)
{					
	static int select=0;
	volatile int J_left = LPC_GPIO1->FIOPIN &=(1<<27); //non deve essere volatile, perchè puo essere usata solo come statica e qui
	volatile int J_right=LPC_GPIO1->FIOPIN &=(1<<28);
	static int button=0;
	ADC_start_conversion();
	
	if(!J_left && isAlive ){	//27 --> left
		/* Joytick Lef pressed p1.27 --> using J_LEFT due to emulator issues*/		
				
				LCD_DrawButton (120, 265,  120,  60, Black,"Snack"); //snack
				LCD_DrawButton (0, 265,  120,  60, Red,"Meal"); //meal
				button=-1;
	}
	
	
	
	else if(!J_right && isAlive){	//28 --> right
		/* Joytick Right pressed p1.28 --> using J_RIGHT due to emulator issues*/
			
			LCD_DrawButton (0, 265,  120,  60, Black,"Meal"); //meal	
			LCD_DrawButton (120, 265,  120,  60, Red,"Snack"); //snack
			button=1;
	}

	
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0 ){	//25 --> select
		/* Joytick select pressed p1.25 --> using SELECT due to emulator issues*/
		
		
		select++;
		BipSound();
		switch(select){
			case 1:  //eseguo l'azione una sola volta --> meal
				if(button<0 && isAlive){
					disable_timer(0);
					feeding=1;
					LCD_DrawRectangle (70, 130,  150,  130, White); //toy	->clean window
					LCD_FeedingUp('m');
					LCD_DrawButton (0, 265,  120,  60, Black,"Meal"); //meal
					enable_timer(0);
					button=0;
				}
				
				if(button>0 && isAlive){
					disable_timer(0);
					feeding=1;
					LCD_DrawRectangle (70, 130,  150,  130, White); //toy	->clean window
					LCD_FeedingUp('s');
					LCD_DrawButton (120, 265,  120,  60, Black,"Snack"); //snack
					enable_timer(0);
					button=0;
				}
				
				if(!isAlive){
				//facciamolo risorgere
					isAlive=1;
					LCD_DrawButton (0, 265,240,60, Red,"Reset"); //reset
					LCD_DrawRectangle(0,265,240,60,White); //cancel button
					LCD_DrawRectangle(60,170,180,60,White);//cancel toy
					LCD_DrawToy();
					init_RIT(0x004C4B40);	
					init_timer(0,0x17D7840); 
					enable_timer(0);
					LPC_TIM0->IR = 3;
					reset_RIT();
					enable_RIT();
				}
				break;
			default:
				break;
		}
	}
	else{
			select=0;  //ritorna a zero in modo tale che l'azione venga eseguita una sola volta
	}
	
	

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
