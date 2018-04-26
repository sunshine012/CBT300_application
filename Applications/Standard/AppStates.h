/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Operating state definitions.
;
*******************************************************************/ 
#ifndef APPSTATES_H_
#define APPSTATES_H_


#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"


// Operating state definitions
#define POWER_UP                		0
#define BATTERY_TYPE              	1
#define BATTERY_RATING          	2
#define BATTERY_TEST            	3
#define TEST_COMPLETE           	4
#define EEPROM_ERROR            	5
#define CALIBRATE               		6
#define DEFAULT_CAL_ERROR       	7
#define BT_CONNECT       			8
#define VOLTAGE_TEST       		9
#define KEY_TEST       			10
#define LCD_TEST       			11
#define BLUETOOTH_TEST              12
#define LANGUAGE_STATE              13
#define SERIALNOINPUT_STATE              		14
#define BAT_RESULT_SEND_QUESTION              	15
#define SELECT_BLUEMENU_STATE        16
#define BAT_NUMBER_STATE        17

// Operating state routine function prototypes
extern void RunOperatingState(void);

#endif
