#ifndef SOUND_H
#define SOUND_H
#include "LPC17xx.H"
#include "../timer/timer.h"

#define B0 17921
#define C1 16835
#define CS1 15873
#define D1 15015
#define DS1 14245
#define E1 13550
#define F1 12626
#define FS1 12077
#define G1 11337
#define GS1 10683
#define A1 10101
#define AS1 9578
#define B1 8960
#define C2 8547
#define CS2 8051
#define D2 7610
#define DS2 7122
#define E2 6775
#define F2 6385
#define FS2 5973
#define G2 5668
#define GS2 5341
#define A2 5050
#define AS2 4748
#define B2 4516
#define C3 4240
#define CS3 3996
#define D3 3779
#define DS3 3561
#define E3 3367
#define F3 3174
#define FS3 3003
#define G3 2834
#define GS3 2670
#define A3 2525
#define AS3 2384
#define B3 2249
#define C4 2120
#define CS4 2005
#define D4 1889
#define DS4 1786
#define E4 1683
#define F4 1591
#define FS4 1501
#define G4 1417
#define GS4 1338
#define A4 1262
#define AS4 1192
#define B4 1124
#define C5 1062
#define CS5 1002
#define D5 946
#define DS5 893
#define E5 843
#define F5 795
#define FS5 750
#define G5 708
#define GS5 668
#define A5 631
#define AS5 596
#define B5 562
#define C6 530
#define CS6 500
#define D6 472
#define DS6 446
#define E6 421
#define F6 397
#define FS6 375
#define G6 354
#define GS6 334
#define A6 315
#define AS6 297
#define B6 281
#define C7 265
#define CS7 250
#define D7 236
#define DS7 223
#define E7 210
#define F7 198
#define FS7 187
#define G7 177
#define GS7 167
#define A7 157
#define AS7 148
#define B7 140
#define C8 132
#define CS8 125
#define D8 118
#define DS8 111
#define REST 0


extern int eatingtrack[3];
extern int cuddlingtrack[8];
extern int deathtrack[5];
extern int melody;
extern int actual_note;
void BipSound(void);
void EatingSound(void);
void CuddlingSound(void);
void DeathSound(void);
#endif