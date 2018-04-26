/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     This module defines the operating state routine(s)
;          
****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "AppStates.h"
#include "AppData.h"
#include "AppBluetooth.h"
#include "AppCalibrat.h"
#include "AppStartUp.h"
#include "AppBatQuest.h"
#include "AppBattest.h"
#include "AppError.h"
#include "SelfTest.h"

/****************************************************************************

   This function selects which operating state routine to run based on the
   global variable OperatingState.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   10-19-15    KC          Developed

****************************************************************************/
void RunOperatingState(void)
{    
   switch(OperatingState)
   {
      case POWER_UP:
         PowerUpState();               
         break;
      case BATTERY_TYPE:
         BatteryTypeState();
         break;
      case BATTERY_RATING:
         BatteryRatingState();
         break;
      case BATTERY_TEST:
         BatteryTestState();
         break;
      case TEST_COMPLETE:
         TestCompleteWait();
         break;
      case DEFAULT_CAL_ERROR:
      case EEPROM_ERROR:
         ErrorState();
         break;
      case CALIBRATE:
         CalState();
         break;
	case BT_CONNECT:
        BlueToothState();
	  break;
	case VOLTAGE_TEST:
        VoltageTestState();
	  break;
	case KEY_TEST:
        KeyTestState();
	  break;
	case LCD_TEST:
        LcdTestState();
	  break;	
	case BLUETOOTH_TEST:
        BTTestState();
	  break;	  
	case LANGUAGE_STATE:
	 LanguageState();
	  break;
	case SERIALNOINPUT_STATE:
	 SerialNoInputState();
	  break;
	case SELECT_BLUEMENU_STATE:
        SelectBluetoothMenu();
	  break;
	case BAT_NUMBER_STATE:
        AppBatNumber();
	  break;		
      default:
         for(;;);  //
   }
}

