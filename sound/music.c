#include "music.h"

int eatingtrack [3]= {A5,B5,C6};
int cuddlingtrack[8]={C3,D3,E3,F3,G3,A4,B4,C4};
int deathtrack[5]={C2,D2,E2,F2,G2};
int actual_note=0;
int melody;
void BipSound(){
	melody=0;
	init_timer(1, A4);
	init_timer(2, 0x2625A0); // 0x2625A0 corrisponde ad 1/10 di secondo
	enable_timer(1);
	enable_timer(2);
}

void EatingSound(){
	melody=1;
	actual_note=0;
	init_timer(1, eatingtrack[actual_note]);
	init_timer(2, 0x2625A0);
	enable_timer(1);
	enable_timer(2);
	

}

void CuddlingSound(){
	melody=2;
	actual_note=0;
	init_timer(1, cuddlingtrack[actual_note]);
	init_timer(2, 0x2625A0);
	enable_timer(1);
	enable_timer(2);
}

void DeathSound(){
	melody=3;
	actual_note=0;
	init_timer(1, deathtrack[actual_note]);
	init_timer(2, 0x2625A0);
	enable_timer(1);
	enable_timer(2);
}