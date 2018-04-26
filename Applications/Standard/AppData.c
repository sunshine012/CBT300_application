/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          AppData.c
 *
 * Designed by:   King Chen
 *
 *
 * Description:
 *
 * References:
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "AppData.h"
#include "DatDictStandard.h"
#include "AppBatQuest.h"
#include "AppBattest.h"


////////////////////////////////////////////////////////////////////////////////
//
// Mirco.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////
UINT8 StartBatteryTestFlg = FALSE;
UINT8 SPPBatteryTestState;

_AppData AppData;
UINT8 ConfigData;
_AppGlobalFlg AppGlobalFlg;
_CalFactorStruct CalFactor;							 
_BatteryData Battery;
_BTRemoteData BTRemoteData;

UINT8 BTSystemConfig;

UINT8               EOLTestFlg = FALSE;                   //EOL test flg
UINT8               TestState;                   //current tool test mode state
UINT8               OperatingState;           //current tool operating state
								   
UINT8               LastKeysPressed;          //used in key debounce routine
UINT8               KeyDebounceCounter;       //counter used to debounce the keypad
_KeyPad             KeyPad;                   //debounced keypad port

_StatusReg           Status;                   //register status flags
UINT8                  ConnectionFlag;   
UINT8                  ConnectionCounter;

unsigned char                tempBuffer[21];           //buffer to hold various strings
unsigned char                DisplayBuffer[21];

UINT16 BatteryTypeDICT[2]={DICT_TEXT_REGULARFLOODED, DICT_TEXT_AGM};
UINT16 BatResultSendDICT[2]={DICT_TEXT_NO, DICT_TEXT_YES};
UINT16 LanguageDICT[2]={DICT_TEXT_CHINESE, DICT_TEXT_ENGLISH};
UINT16 BatteryResultDICT[5]={DICT_TEXT_GOODBATTERY,DICT_TEXT_GOODRECHARGE,DICT_TEXT_CHARGERETEST,
	DICT_TEXT_REPLACEBATTERY, DICT_TEXT_BADCELL };
UINT8 TempBTBuffer[128];  
UINT8 WrapperBuffer[128];  


UINT8 SerialNumberData[SERIALNUMBER+1]="0216300000";

#pragma udata GlobalBuffer
_DataGlobalBuffer   GlobalDataBuffer;
#pragma udata

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////
