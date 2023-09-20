#include "Drawing.h"
#include "GLCD/GLCD.h" 
#include <string.h>
#include "sound/music.h"
//0:transparent, 1:white, 2: red,3:brown 7:black
volatile uint8_t sec=00;
volatile uint8_t min=00;
volatile uint8_t hour=00;
volatile char time[11]="";
int isAlive=1;
uint8_t level_volume=4;

uint8_t  CheckIfAlive(void){
if(	level_happiness<=1 || level_satiety<=1)
	return 1;
else return 0;
}


void IncreaseLevel(char c){
	switch(c){
		case 'h':
			if(level_happiness<4)			
				level_happiness++;
			break;
		case 's': 
			if(level_satiety<4)
				level_satiety++;
			break;
		case 'v': 
			if(level_volume<4)
				level_volume++;
			break;
		default:
			break;
	}
	
}

void DecreaseLevel(char c){
	switch(c){
		case 'h':
			if(level_happiness>0)
				level_happiness--;
			break;
		case 's': 
			if(level_satiety>0)
				level_satiety--;
			break;
		case 'v': 
			if(level_volume>0)
				level_volume--;
			break;
		default:
			break;
	}
}


void LCD_DrawFigure1( uint16_t mat[][c1],  uint16_t r, uint16_t c,uint16_t X_start, uint16_t Y_start, uint16_t offset ){
	 uint16_t i,j;
	LCD_DrawRectangle (70, 135,  150,  125, White); //toy	
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			
			
			switch(mat[i][j]){
				case 1:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,White);
							break;
				case 2:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Red);
							break;
				case 7:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Black);
							break;
				default:
							break;
				}
			}
		}
	}

void LCD_DrawFigure2( uint16_t mat[][c2],  uint16_t r, uint16_t c,uint16_t X_start, uint16_t Y_start, uint16_t offset ){
	 uint16_t i,j;
	LCD_DrawRectangle (70, 140,  100,  120, White); //toy	
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			
			
			switch(mat[i][j]){
				case 1:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,White);
							break;
				case 2:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Red);
							break;
				case 7:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Black);
							break;
				default:
							break;
				}
			}
		}
	}


void LCD_DrawFigure3( uint16_t mat[][c3],  uint16_t r, uint16_t c,uint16_t X_start, uint16_t Y_start, uint16_t offset ){
	 uint16_t i,j;
	level_happiness=0;
	level_satiety=0;
	LCD_DrawRectangle (60, 125,  110,  135, White); //toy	
	LCD_DrawBattery (35, 58,  60,  30, Black,level_happiness); //battery1
	LCD_DrawBattery (150, 58,  60,  30, Black,level_satiety); //battery2 		
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			
			
			switch(mat[i][j]){
				case 1:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,White);
							break;
				case 2:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Red);
							break;
				case 7:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Black);
							break;
				default:
							break;
				}
			}
		}
	}


void LCD_DrawMeal( uint16_t mat[][c4],  uint16_t r, uint16_t c,uint16_t X_start, uint16_t Y_start, uint16_t offset ){
	 uint16_t i,j;
		
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			
			
			switch(mat[i][j]){
				case 1:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,White);
							break;
				case 2:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Red);
							break;
				case 3:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Brown);
							break;
				case 7:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Black);
							break;
				default:
							break;
				}
			}
		}
	}


void LCD_DrawSnack( uint16_t mat[][c5],  uint16_t r, uint16_t c,uint16_t X_start, uint16_t Y_start, uint16_t offset ){

	 uint16_t i,j;
		
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			
			
			switch(mat[i][j]){
				case 1:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,White);
							break;
				case 2:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Red);
							break;
				case 3:	
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Brown);
							break;
				case 7:
							LCD_DrawRectangle(X_start+(offset*j),Y_start+(offset*i),offset,offset,Black);
							break;
				default:
							break;
				}
			}
		}
	}
	


void LCD_DrawVolume(uint16_t X_start, uint16_t Y_start, uint16_t width, uint16_t height, uint16_t color){
	int i=0, offset=2;
	for(i=0;i<level_volume;i++){
			LCD_DrawRectangle (X_start+width+offset, Y_start+height/2-offset, 1, 2*offset, Black);
		offset+=2;
	}
	
	for(i=level_volume;i<4;i++){
			LCD_DrawRectangle (X_start+width+offset, Y_start+height/2-offset, 1, 2*offset, White);
		offset+=2;
	}
	
	
	
	
}

void ChangeVolume(uint8_t c){
	level_volume=c;
	LCD_DrawVolume(12,12, 15, 15, Black);
}
	
	void LCD_DrawMicrophone(uint16_t X_start, uint16_t Y_start, uint16_t width, uint16_t height, uint16_t color){
	
	LCD_DrawRectangle (X_start, Y_start,  width, height, Black);
	LCD_DrawTriangleUp (X_start, Y_start+height,  width,  height-4, White);
	LCD_DrawTriangleDown (X_start, Y_start,  width,  height-4, White);
	LCD_DrawVolume(X_start, Y_start,  width, height, Black);
	
}	




void LCD_DrawCase(uint16_t X_start, uint16_t Y_start, uint16_t width, uint16_t height, uint16_t color){
	LCD_DrawLine(X_start,Y_start,X_start,Y_start+height,color );
	LCD_DrawLine(X_start,Y_start, X_start+width,Y_start,color );
	LCD_DrawLine(X_start+width,Y_start, X_start+width,Y_start+height,color );
	LCD_DrawLine(X_start,Y_start+height,X_start+width, Y_start+height,color );
	LCD_DrawRectangle (X_start+width+2, Y_start+(height-7)/2,5,10, Black); //piolino
}




void LCD_DrawBattery(uint16_t X_start, uint16_t Y_start, uint16_t width, uint16_t height, uint16_t color, char c){
	int i=0,	offset=2;
	
	switch(c){
	case 'h':
			for(i=0;i<level_happiness;i++){
					LCD_DrawRectangle (X_start+offset, Y_start+2,  12,  26, Black);  
					offset+=15;
			}
			for(i=level_happiness;i<4;i++){
				LCD_DrawRectangle (X_start+offset, Y_start+2,  12,  26, White);  //canceling
				offset+=15;
			}
			break;
	case 's': 
			for(i=0;i<level_satiety;i++){
					LCD_DrawRectangle (X_start+offset, Y_start+2,  12,  26, Black);  
					offset+=15;
			}
			for(i=level_satiety;i<4;i++){
				LCD_DrawRectangle (X_start+offset, Y_start+2,  12,  26, White);  //canceling
				offset+=15;
			}			
			break;
	default:
			break;	
	}
	

}





void LCD_DrawButton(uint16_t X_start, uint16_t Y_start, uint16_t width, uint16_t height, uint16_t color,char* text){
	LCD_DrawLine(X_start,Y_start,X_start,Y_start+height,color );
	LCD_DrawLine(X_start,Y_start, X_start+width,Y_start,color );
	LCD_DrawLine(X_start+width,Y_start, X_start+width,Y_start+height,color );
	LCD_DrawLine(X_start,Y_start+height,X_start+width, Y_start+height,color );
	
	if(!strcmp(text,"Reset") ){
		GUI_Text(X_start+width*5/12, Y_start+height/3, (uint8_t *) text, color, White);
	} 
	else {
	GUI_Text(X_start+width/3, Y_start+height/3, (uint8_t *) text, color, White);
	}
}



void LCD_UpdateTime(uint8_t hour,uint8_t min,uint8_t sec){
	sprintf(time,"Age: %.2d:%.2d:%.2d",hour,min,sec);
	GUI_Text(70, 15, (uint8_t *) time, Black, White);	
	}



void LCD_MoveFigure1( uint16_t mat[][c1],  uint16_t r, uint16_t c,uint16_t X_start, uint16_t Y_start, uint16_t offset ){
	 uint16_t i,j,k;
	
	for(k=0;k<7;k++){
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			
			
			switch(mat[i][j]){
				case 1:
							LCD_DrawRectangle(X_start+(offset*j)+(offset*k),Y_start+(offset*i),offset,offset,White);
							break;
				case 2:	
							LCD_DrawRectangle(X_start+(offset*j)+(offset*k),Y_start+(offset*i),offset,offset,Red);
							break;
				case 7:
							LCD_DrawRectangle(X_start+(offset*j)+(offset*k),Y_start+(offset*i),offset,offset,Black);
							break;
				default:
							break;
				}
			}
		}
	}
	}



void LCD_FeedingUp(char d){
		EatingSound();
	switch(d){
			case 'm':
				LCD_DrawMeal(matrix4,r4,c4,157,195,3);
				LCD_MoveFigure1(matrix1,r1,c1,70,140,4);
				IncreaseLevel('s');
				LCD_DrawBattery (150, 58,  60,  30, Black,'s'); //battery2
				//delay deve durare tutto almeno un secondo
				LCD_DrawRectangle (70, 140,  100,  120, White); //toy	->clean window
				LCD_DrawFigure1(matrix1,r1,c1,70,140,4);
				break;
			case 's':
				LCD_DrawSnack(matrix5,r5,c5,162,205,3);
				LCD_MoveFigure1(matrix1,r1,c1,70,140,4);
				IncreaseLevel('h');
				LCD_DrawBattery (35, 58,  60,  30, Black,'h'); //battery2
				//delay deve durare tutto almeno un secondo
				LCD_DrawRectangle (70, 140,  100,  120, White); //toy	->clean window
				LCD_DrawFigure1(matrix1,r1,c1,70,140,4);
				break;
			default:
					break;
		}
	}


void LCD_Reset(void){
	isAlive=0;
	LCD_DrawFigure3(matrix3,r3,c3,60,170,4);
	level_happiness=0;
	level_satiety=0;
	LCD_DrawBattery (35, 58,  60,  30, Black,'h'); //battery1
	LCD_DrawBattery (150, 58,  60,  30, Black,'s'); //battery2
	LCD_DrawRectangle(0,265,249,60,White); //cancel button
	LCD_DrawButton (0, 265,  240,  60, Black,"Reset"); //Select	
	LPC_TIM0->IR = 5;
	disable_timer(0);
}



void LCD_DrawToy(){
	level_happiness=4;
	level_satiety=4;
	sec=0;
	min=0;
	hour=0;
	LCD_UpdateTime(hour,min,sec);	
	LCD_DrawBattery (35, 58,  60,  30, Black,'h'); //battery1
	LCD_DrawBattery (150, 58,  60,  30, Black,'s'); //battery2 	
	LCD_DrawButton (0, 265,  120,  60, Black,"Meal"); //meal	
	LCD_DrawButton (120, 265,  120,  60, Black,"Snack"); //snack	
}


void LCD_start(void){
	LCD_Clear(White);
	LCD_SetOrientation('V');
		
	GUI_Text(20, 33, (uint8_t *) " Happiness", Green, White);		
	GUI_Text(144, 33, (uint8_t *) " Satiety", Green, White);
	LCD_DrawMicrophone(12, 12,  15,  15, Black);
	LCD_DrawCase(35, 58,  60,  30, Black);
	LCD_DrawCase(150, 58,  60,  30, Black);

LCD_DrawToy();

	
}	


	

