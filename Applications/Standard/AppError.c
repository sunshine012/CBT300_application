/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     This module defines the error handling routine(s)
;
****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "AppError.h"
#include "AppData.h"
#include "AppStates.h"
#include "AppBattest.h"
#include "DrvLCD_OPTO1140GG.h"
#include "SysDisplay.h"
#include "SysVoltage.h"
#include "DrvAdc_18F67J10.h"
#include "DatDictStandard.h"

UINT8 CheckConnection(void)
{
	 UINT16 TempValue = 0;
	 UINT16 TempVoltsCD;
	 UINT16 TempVoltsAB;
	//Battery.VoltsCD = SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 16);
	//Battery.VoltsAB = SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 16);	
	TempVoltsCD = SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 16);
	TempVoltsAB = SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 16);		
   	if(TempVoltsAB > TempVoltsCD)
   		TempValue = TempVoltsAB - TempVoltsCD;
   	else
   		TempValue = TempVoltsCD - TempVoltsAB;
   
  	 if((TempValue <= _200MILLIVOLTS) && TempVoltsCD >= MIN_CHECK_CONN_VOLT &&
   		TempVoltsCD <= MAX_CHECK_CONN_VOLT)
   	{
      		return(FALSE);
   	}
   	else
      		return(TRUE);
}


void ErrorState(void)
{
   switch(TestState)
   {
	case ERROR_INIT:
   		if(OperatingState == EEPROM_ERROR)
   		{
   	 		CLEARSCREEN();
		/*********Inner Error***********/
			SysDisplayString_W(DICT_TEXT_INNERERROR,1,DISPLAY_C);
			SysDisplayString_W(DICT_TEXT_SERVICEREQUIRED,2,DISPLAY_C);
			TestState++;
   		}
   		else if(OperatingState == DEFAULT_CAL_ERROR)
   		{
      			CLEARSCREEN();
		/*********Calibration error***********/
			SysDisplayString_W(DICT_TEXT_CALIBATIONFAIL,1,DISPLAY_C);
			SysDisplayString_W(DICT_TEXT_SERVICEREQUIRED,2,DISPLAY_C);
			TestState++;
   		}
   		break;
	case ERROR_WAIT:
		
      break;
   }
}
