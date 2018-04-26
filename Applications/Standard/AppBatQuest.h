/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Battery questions definitions.
;
*******************************************************************/
#ifndef _BAT_QUEST_H_
#define _BAT_QUEST_H_

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

//Test States
#define BATTERY_RATING_INITIALIZE     0
#define BATTERY_RATING_QUESTION       1

//Test States
#define BATTERY_TYPE_INITIALIZE      0
#define BATTERY_TYPE_QUESTION       1

#define BAT_TYPE_REGULARFLOODED     0
#define BAT_TYPE_AGM                           1

//Test States
#define BAT_RESULT_SEND_INITIALIZE      0
#define BAT_RESULT_SEND_QUESTION_WAIT       1

#define BAT_RESULT_SEND_NO     			 0
#define BAT_RESULT_SEND_YES                   1

#define OPERATE_SYSTEM_ANDROID     	0
#define OPERATE_SYSTEM_IOS                   	1
#define OPERATE_SYSTEM_NONE                 0xFF

//Test States
#define SELECT_BLUE_MENU_INITIALIZE     		0
#define SELECT_BLUE_MENU_QUESTION       	1

//Test States
#define BATTERY_NUMBER_INITIALIZE     0
#define BATTERY_NUMBER_QUESTION       1

//Function Prototypes
extern void DisplayRating(void);
extern void BatteryRatingState(void);
extern void BatteryTypeState(void);
void SelectBluetoothMenu(void);
void AppBatNumber( void );
	
#endif
