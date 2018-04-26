/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;  This module defines the battery testing state routine(s)
;
****************************************************************************/
#include <stdlib.h>         
#include <string.h>
#include "SysDisplay.h"
#include "AppBatQuest.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvTimer_18F67J10.h"
#include "DrvPan1026.h"
#include "AppUtility.h"
#include "AppData.h"
#include "DrvKey.h"
#include "AppStates.h"
#include "AppCalibrat.h"
#include "DatDictStandard.h"
#include "AppBattest.h"
#include "AppBluetooth.h"
#include "DrvEeprom_25AA320.h"

#define INCREMENT_VALUE       5
#define INCREMENT_VALUE_CBT100       25

//
//
//
//
void DisplayBatJISNB(void)
{ 
	SysClear_Line(2);
	strcpypgm2ram((char *)tempBuffer,(const rom char*)(JISNumbers[Battery.BatJISIndex].Text));
	SysDisplayString(tempBuffer, 2, DISPLAY_C);
}

//
//
//
//
void DisplayRating(void)
{ 
	itoabase(Battery.RatedCCA, tempBuffer, 4, 10);
	strcatpgm2ram((char *)tempBuffer," CCA");
    	/*********Display Voltage***********/
	SysDisplayString(tempBuffer, 2, DISPLAY_C);
}
//
//
//
//
void DisplayType(void)
{ 
    	/*********Display Battery Type***********/
	SysDisplayString_W(BatteryTypeDICT[Battery.BatteryTypeId], 2, DISPLAY_C);
}
//
//
//
//
void BatteryRatingState(void)
{
   switch(TestState)
   {
      case BATTERY_RATING_INITIALIZE:  
	   CLEARSCREEN();
	   AppControlStatus(CTRL_UP|CTRL_DOWN|CTRL_ENTER);
	   SysDisplayString_W(DICT_TEXT_INPUTRATING, 1, DISPLAY_C);
          DisplayRating();
	   DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 100);	 
         TestState++;                 
         break;

      case BATTERY_RATING_QUESTION:
	  	
//		 if(CBT300_CONFIG != ConfigData)
//		 {
//		 	if((!UpArrowInput)&&(!DownArrowInput)&& FALSE == ConnectionFlag)
//			{
//				OperatingState = BATTERY_TEST;
//         			TestState = BATTERY_TEST_INITIALIZE;
//				Battery.RatedCCA = 500;
//				EOLTestFlg= TRUE;
//			}
//		 }
		 
         switch(KeyPad.Keys)
         {
            case ENTER_KEY:
               if(Status.Bit.KeysReleased == TRUE && FALSE == ConnectionFlag)
               {
                  	CLEARSCREEN();
                  	OperatingState = BATTERY_TEST;
                  	TestState = BATTERY_TEST_INITIALIZE;
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;

            case DOWN_ARROW_KEY:
            case UP_ARROW_KEY:
               if(((Status.Bit.KeysReleased == TRUE)  || 
			   	DrvTimer0CounterDone(TIMER0_MS_COUNTER_2)) && 
			   	FALSE == ConnectionFlag)
               {

		    	if(CBT300_CONFIG == ConfigData)
		    	{
                  		if(KeyPad.Keys == UP_ARROW_KEY && Battery.RatedCCA < 2000)
                  		{                    
                     		Battery.RatedCCA += INCREMENT_VALUE;
                  		}
                  		else if(KeyPad.Keys == DOWN_ARROW_KEY && Battery.RatedCCA > 100)
                  		{                   
                     		Battery.RatedCCA -= INCREMENT_VALUE;
                  		}
		    	}
			else
			{
                  		if(KeyPad.Keys == UP_ARROW_KEY && Battery.RatedCCA < 1200)
                  		{                    
                     		Battery.RatedCCA += INCREMENT_VALUE_CBT100;
                  		}
                  		else if(KeyPad.Keys == DOWN_ARROW_KEY && Battery.RatedCCA > 200)
                  		{                   
                     		Battery.RatedCCA -= INCREMENT_VALUE_CBT100;
                  		}
			}
			
                  DisplayRating();
		     DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 100);	  
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;
         }
         break;
   }
}
//
//
//
//
void BatteryTypeState(void)
{

   	switch(TestState)
   	{
		case BATTERY_TYPE_INITIALIZE:
			SysDisplayString_W(DICT_TEXT_BATTERYTYPE, 1, DISPLAY_C);
			if(Battery.BatteryTypeId == BAT_TYPE_REGULARFLOODED)
			{
				AppControlStatus(CTRL_UP|CTRL_ENTER);
			}
			else
			{
				AppControlStatus(CTRL_DOWN|CTRL_ENTER);
			}
			DisplayType();
			TestState++;
			break;
		case BATTERY_TYPE_QUESTION:
			
			if(CBT300_CONFIG == ConfigData)
			{
				if((!UpArrowInput)&&(!DownArrowInput)&& FALSE == ConnectionFlag)
				{
					OperatingState = BATTERY_RATING;
                  			TestState = BATTERY_RATING_INITIALIZE;
					Battery.BatteryTypeId = BAT_TYPE_REGULARFLOODED;
					EOLTestFlg = TRUE;
				}
			}
			
         		switch(KeyPad.Keys)
         		{
            			case ENTER_KEY:
               			if(Status.Bit.KeysReleased == TRUE && FALSE == ConnectionFlag)
               			{
                  				OperatingState = BATTERY_RATING;
                  				TestState = BATTERY_RATING_INITIALIZE;
               			}
               			Status.Bit.KeysReleased = FALSE;
               		break;
					
            			case DOWN_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE && FALSE == ConnectionFlag)
               			{
						Battery.BatteryTypeId = BAT_TYPE_REGULARFLOODED;
						DisplayType();
						AppControlStatus(CTRL_UP|CTRL_ENTER);
               			}
               			Status.Bit.KeysReleased = FALSE;
               			break;
						
            			case UP_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE && FALSE == ConnectionFlag) 
               			{                      
                     			Battery.BatteryTypeId = BAT_TYPE_AGM;
                  				DisplayType();
									AppControlStatus(CTRL_DOWN|CTRL_ENTER);		
               			}                       
               			Status.Bit.KeysReleased = FALSE;
               			break;					
         		}
			break;

   	}
}

void SelectBluetoothMenu(void)
{
   switch(TestState)
   {
      case SELECT_BLUE_MENU_INITIALIZE:  
	   CLEARSCREEN();
	   AppControlStatus(CTRL_ENTER);
	   SysDisplayString_W(DICT_TEXT_BLUETOOTHREADY, 1, DISPLAY_C);
	   AppData.OperateSystemId = OPERATE_SYSTEM_ANDROID;
	   SysDisplayString_W(DICT_TEXT_PRESSENTERCANCEL, 2, DISPLAY_C);
       TestState++;                 
         break;

      case SELECT_BLUE_MENU_QUESTION:
	  	
         switch(KeyPad.Keys)
         {
            case ENTER_KEY:
               if(Status.Bit.KeysReleased == TRUE)
               {
                  	CLEARSCREEN();
                  	if(AppData.OperateSystemId == OPERATE_SYSTEM_ANDROID)
                  	{											
							DrvPan1026Off();				
							BTSystemConfig = OPERATE_SYSTEM_NONE;
                  		OperatingState = BAT_NUMBER_STATE;
                  		TestState = BATTERY_NUMBER_INITIALIZE;
							AppData.OperateSystemId = OPERATE_SYSTEM_NONE;
                  	}
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;

            	case DOWN_ARROW_KEY:
            	case UP_ARROW_KEY:
               if(Status.Bit.KeysReleased == TRUE) 
               {   
               
				  }                       
              Status.Bit.KeysReleased = FALSE;
               break;	
         }
         break;
		
   }
}


void AppBatNumber( void )
{
   switch(TestState)
   {
      case BATTERY_NUMBER_INITIALIZE:  
	   CLEARSCREEN();
	   SysDisplayString_W(DICT_TEXT_BATTERYREFNB, 1, DISPLAY_C);	
//		Battery.BatJISIndex = 20;	 
       DisplayBatJISNB();
		if(Battery.BatJISIndex == FIRST_JIS_INDEX)
	    	AppControlStatus(CTRL_UP|CTRL_ENTER);
		else if(Battery.BatJISIndex == LAST_JIS_INDEX)
			AppControlStatus(CTRL_DOWN|CTRL_ENTER);
		else
			AppControlStatus(CTRL_UP|CTRL_DOWN|CTRL_ENTER);
			 
	   DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 200);	 
         TestState++;                 
         break;

      case BATTERY_NUMBER_QUESTION:
	  	
//		 if(CBT300_CONFIG != ConfigData)
//		 {
//		 	if((!UpArrowInput)&&(!DownArrowInput)&& FALSE == ConnectionFlag)
//			{
//				OperatingState = BATTERY_TEST;
//         		TestState = BATTERY_TEST_INITIALIZE;
//				Battery.RatedCCA = 500;
//				EOLTestFlg= TRUE;
//			}
//		 }
		 
         switch(KeyPad.Keys)
         {
            case ENTER_KEY:
               if(Status.Bit.KeysReleased == TRUE && FALSE == ConnectionFlag)
               {
               		Battery.AlgorithmId = JISNumbers[Battery.BatJISIndex].Curve;
						Battery.RatedCCA = JISNumbers[Battery.BatJISIndex].RatedCapacity;
						Battery.BatteryTypeId = BAT_TYPE_REGULARFLOODED;
						
                  	CLEARSCREEN();
                  	OperatingState = BATTERY_TEST;
                  	TestState = BATTERY_TEST_INITIALIZE;
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;

            case DOWN_ARROW_KEY:
            case UP_ARROW_KEY:
               if(((Status.Bit.KeysReleased == TRUE)  || 
			   	DrvTimer0CounterDone(TIMER0_MS_COUNTER_2)) && FALSE == ConnectionFlag)
               {

                  		if(KeyPad.Keys == UP_ARROW_KEY)
                  		{                    
                           if(Battery.BatJISIndex < LAST_JIS_INDEX)
							Battery.BatJISIndex ++;
						   else
						   	Battery.BatJISIndex = 1;
						   	
						   
                  		}
                  		else if(KeyPad.Keys == DOWN_ARROW_KEY)
                  		{                   
                     		
							if(Battery.BatJISIndex > FIRST_JIS_INDEX)
							Battery.BatJISIndex --;
						   else
						   	Battery.BatJISIndex = LAST_JIS_INDEX;
                  		}
											
          				DisplayBatJISNB();
						if(Battery.BatJISIndex == FIRST_JIS_INDEX)
	    					AppControlStatus(CTRL_UP|CTRL_ENTER);
						else if(Battery.BatJISIndex == LAST_JIS_INDEX)
							AppControlStatus(CTRL_DOWN|CTRL_ENTER);
						else
							AppControlStatus(CTRL_UP|CTRL_DOWN|CTRL_ENTER);		
						
		    			DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 200);	  
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;
         }
         break;
   }
}