/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../Drawing.h"
#include "../RIT/RIT.h"
#include "../joystick/joystick.h"
#include "../TouchPanel/TouchPanel.h"
#include "../sound/music.h"
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern uint8_t sec;
extern uint8_t min;
extern uint8_t hour;
extern char time[11];
static uint8_t feeding;
static uint8_t time_feed=0;
static uint8_t cuddling=0;
static uint8_t time_cuddle=0;
static uint8_t flag=0;
static uint8_t batteries=0;

uint16_t SinTable[45] =                                       /*                      */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


void TIMER0_IRQHandler (void)
{
	//disable_timer(3);
	
	batteries++;
	
	if (!flag && !feeding && isAlive && !cuddling){
	LCD_DrawFigure1(matrix1,r1,c1,70,145,4);
		flag++;
	}
	else if(flag && !feeding && isAlive && !cuddling){
		LCD_DrawFigure1(matrix1,r1,c1,70,135,4);
		flag--;
	}
	
	if(sec==59 && min==59 && isAlive){
		sec=0;
		min=0;
		hour++;
	}
	else {
		if(sec==59){
			sec=0;
			min++;}
		else sec ++;
		}
	LCD_UpdateTime(hour,min,sec);	
		
	if(batteries>=5 && !feeding && isAlive && !cuddling){
		
		if(CheckIfAlive()){
		//dead
			DeathSound();
			disable_timer(0);	//stoppo entrambi i timer
			disable_RIT();
			reset_RIT();
			enable_RIT();
			disable_timer(3);
			LCD_Reset();
			LPC_TIM0->IR = 5;
		}
		else {
			DecreaseLevel('h');	
			DecreaseLevel('s');
			LCD_DrawBattery (35, 58,  60,  30, Black,'h'); //battery1
			LCD_DrawBattery (150, 58,  60,  30, Black,'s'); //battery2 
	
		}
		
		batteries=0;
	}

		if(feeding && isAlive && !cuddling){
			time_feed++;
			if(time_feed>=1){
					LCD_DrawRectangle (70, 140,  100,  120, White); //clean toy	
					time_feed=0;
					feeding=0;
					enable_RIT();
			}
		}

		if(cuddling && isAlive){
			time_cuddle++;
			if(time_cuddle>=2){
					LCD_DrawRectangle (70, 140,  100,  120, White); //clean toy	
					IncreaseLevel('h');
					LCD_DrawBattery (35, 58,  60,  30, Black,'h'); //battery2
					time_cuddle=0;
					cuddling=0;
			}
		}
		
		if(isAlive){
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
		}
		else disable_timer(0);
	//	enable_timer(3);
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{ 
	int current_volume=level_volume*1023/5;
	static int ticks=0;
	/* DAC management */	
	LPC_DAC->DACR = ((SinTable[ticks]*current_volume)/819)<<6;
	ticks++;
	if(ticks==45) ticks=0;
	
	 LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;


}

void TIMER2_IRQHandler (void){
	switch(melody){
		case 0:
			disable_timer(1);
			disable_timer(2);
			break;
		case 1:
			if(actual_note<3){
				actual_note++;
				disable_timer(1);
				disable_timer(2);
				reset_timer(1);
				reset_timer(2);
				init_timer(1,eatingtrack[actual_note]);
				init_timer(2, 0x2625A0);
				enable_timer(1);
				enable_timer(2);
			}
			else {
				disable_timer(1);
				disable_timer(2);}
			break;
		
		case 2:
			if(actual_note<8){
				actual_note++;
				disable_timer(1);
				disable_timer(2);
				reset_timer(1);
				reset_timer(2);
				init_timer(1,cuddlingtrack[actual_note]);
				init_timer(2, 0x2625A0);
				enable_timer(1);
				enable_timer(2);
			}
			else {
				disable_timer(1);
				disable_timer(2);}
			break;
		case 3:
			if(actual_note<5){
				actual_note++;
				disable_timer(1);
				disable_timer(2);
				reset_timer(1);
				reset_timer(2);
				init_timer(1,deathtrack[actual_note]);
				init_timer(2, 0x2625A0);
				enable_timer(1);
				enable_timer(2);
			}
			else {
				disable_timer(1);
				disable_timer(2);}
			break;		
	}
	
	
	
	
	LPC_TIM2->IR = 1;	//stop timer 2
	return ;
	
}

void TIMER3_IRQHandler (void){
	//timer for cuddling


	if(getDisplayPoint(&display, Read_Ads7846(), &matrix)){
		if (display.x>=70 && display.x<=170 && display.y>=140 && display.y<=280 && isAlive){
				CuddlingSound();
				disable_timer(0);
				LCD_DrawRectangle (70, 130,  100,  130, White); //clean toy	
				LCD_DrawFigure2(matrix2,r2,c2,70,140,4);
				time_cuddle=0;
				cuddling=1;
				enable_timer(0);
		}
	}
	
	LPC_TIM3->IR = 1;
	
}




/******************************************************************************
**                            End Of File
******************************************************************************/
