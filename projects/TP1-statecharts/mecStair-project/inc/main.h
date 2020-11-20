#ifndef __MAIN_H__
#define __MAIN_H__

#include "board.h"
#include "MecStair.h"
#include "TimerTicks.h"

// Tickrate definitions
#define TICKRATE_1MS		   (1000)				/* 1000 ticks per second */
#define TICKRATE_MS			(TICKRATE_1MS)	/* 1000 ticks per second */

// This is a timed state machine that requires timer services
#define NOF_TIMERS (sizeof(MecStairTimeEvents)/sizeof(sc_boolean))

#define OPT_SQR	0
#define OPT_SIN 1
#define OPT_TRI 2

// BOARD LEDS
#define LED0_R    0
#define LED0_G    1
#define LED0_B    2
#define LED1      3
#define LED2      4
#define LED3      5


#endif
