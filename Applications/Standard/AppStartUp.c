/****************************************************************************
;
;     Copyright (c) Midtronics 2015
;
;     This module defines the power up state routine(s)
;          
****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "AppStartUp.h"
#include "AppData.h"
#include "AppEEData.h"
#include "AppStates.h"
#include "AppBatQuest.h"
#include "AppError.h"
#include "AppBluetooth.h"
#include "DatDictStandard.h"
#include "DatFont6x16.h"
#include "DrvKey.h"
#include "DrvTimer_18F67J10.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvEeprom_25AA320.h"
#include "SysGraphic.h"
#include "SysDisplay.h"
#include "SysDisplay.h"
#include "SelfTest.h"

const CHAR  CBT100TesteName[]="CBT-100";
const CHAR  CBT300TesteName[]="CBT-300";
const CHAR  Version[]="192-121XXXB";
const CHAR  CompanyName[]="MIDTRONICS";
const CHAR  CBT300DemoTesteName[]="CBT-350 DEMO";

UINT8  IputEditPostion;

/****************************************************************************

   This function handles the power up state.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   10-10-15         KC          Developed


****************************************************************************/
void PowerUpState(void)
{    
   switch(TestState)
   {
      case POWER_UP_INITIALIZE:                           
            DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);
            TestState++;
            CLEARSCREEN();
            //Display start logo
            if(CBT300_CONFIG == ConfigData)
            {
                SysDisplayString((CHAR *)CBT300DemoTesteName,1,DISPLAY_C); 
                SysDisplayString((CHAR *)CompanyName,2,DISPLAY_C);  		
                DrvEepromRead((UINT16)EESerialNumberData, (UINT8*)SerialNumberData, sizeof(SerialNumberData));
            }
            else
            {
                SysDisplayString((CHAR *)CBT100TesteName,1,DISPLAY_C); 
                SysDisplayString((CHAR *)CompanyName,2,DISPLAY_C);  
            }
            while(!DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1)) 
                CLRWDT();
            break;

      case POWER_UP_WAIT:  
         while((!UpArrowInput)&&DownArrowInput)
         {   
         	if(CBT300_CONFIG == ConfigData)
			{
                // SysDisplayString((CHAR *)CBT300DemoTesteName,1,DISPLAY_C);
				memset(DisplayBuffer,0x00,sizeof(DisplayBuffer));
				strcatpgm2ram((char *)DisplayBuffer,"SNO: ");
				strcat((char *)DisplayBuffer,(char *)SerialNumberData);
				DisplayString_S(DisplayBuffer,4,DISPLAY_C);	
				DisplayString_S(Version,3,DISPLAY_C);
         	}
			else
			{
          		SysDisplayString((CHAR *)CBT100TesteName,1,DISPLAY_C); 
				SysDisplayString((CHAR *)Version,2,DISPLAY_C);				
			}
		
            CLRWDT();
			DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);	
         }
	     TestState++;
         break;
	    case POWER_UP_END: 
            while(!DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1)) 
            	CLRWDT();
		 
            DrvEepromRead((UINT16)&EEBattery, (UINT8 *)&Battery, sizeof(_BatteryData));
            DrvEepromRead((UINT16)&EEBTRemoteData, (UINT8*)&BTRemoteData, sizeof(_BTRemoteData));	

            OperatingState = BT_CONNECT;
            TestState = BLUETOOTH_INIT; 
            BTSystemConfig = OPERATE_SYSTEM_ANDROID;
            //OperatingState = BATTERY_TYPE;
            //TestState = BATTERY_TYPE_INITIALIZE;

	  break;	
	  
      default:
         break;
   }
}
//
//
//
//
void DisplayLanguage(void)
{ 
    	/*********Display Language***********/
	SysDisplayString_W(LanguageDICT[AppData.LanguageId], 2, DISPLAY_C);
}

//
//
//
//

void LanguageState(void)
{

   	switch(TestState)
   	{
		case LANGUANGE_INITIALIZE:
			SysDisplayString_W(DICT_TEXT_LANGUAGE, 1, DISPLAY_C);
			AppControlStatus(CTRL_DOWN|CTRL_ENTER);
			//AppData.LanguageId = LANGUANGE_CHINESE;
			DisplayLanguage();
			TestState++;
			break;
		case LANGUANGE_QUESTION:
         		switch(KeyPad.Keys)
         		{
            			case ENTER_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{
                   			AppGlobalFlg.LanguageSetFlg = TRUE;
    						DrvEepromWrite((UINT16)&EEAppGlobalFlg, (UINT8*)&AppGlobalFlg, sizeof(_AppGlobalFlg));
    						DrvEepromWrite((UINT16)&EEAppData, (UINT8*)&AppData, sizeof(_AppData));			
    						DelayXms( 2 );
    						DrvEepromRead((UINT16)&EEAppGlobalFlg, (UINT8*)&AppGlobalFlg, sizeof(_AppGlobalFlg));
    						if(AppGlobalFlg.LanguageSetFlg == TRUE)
    						{
    							OperatingState = POWER_UP;
              					TestState = POWER_UP_INITIALIZE;
    						}
    						else
    						{
    							OperatingState = EEPROM_ERROR;
      							TestState = ERROR_INIT;
    						}
               			}
               			Status.Bit.KeysReleased = FALSE;
               		break;
					
            			case DOWN_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{
    						AppData.LanguageId = LANGUANGE_ENGLISH;
    						DisplayLanguage();
    						AppControlStatus(CTRL_UP |CTRL_ENTER);
               			}
               			Status.Bit.KeysReleased = FALSE;
               			break;
						
            			case UP_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE) 
               			{      
    						AppData.LanguageId = LANGUANGE_CHINESE;
    						DisplayLanguage();
    						AppControlStatus(CTRL_DOWN|CTRL_ENTER);
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
void SerialNoInputState(void)
{

   	switch(TestState)
   	{
		case SERIALNO_INITIALIZE:
			CLEARSCREEN();
			AppControlIputInit(DICT_TEXT_INPUTSERIALNO);
			DisplayControlString(SerialNumberData, SERIALNUMBER, 2, DISPLAY_C);
			DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 150);
			TestState++;
			break;
		case SERIALNO_QUESTION:
         		switch(KeyPad.Keys)
         		{
						
            			case ENTER_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{
                            if(IputEditPostion == SERIALNUMBER)
                            {
                                DrvEepromWrite((UINT16)&EESerialNumberData, (UINT8*)SerialNumberData, sizeof(SerialNumberData));
                                TestState++;
                            }
                            else
                            {
                                IputEditPostion++;
                                DisplayControlString(SerialNumberData, SERIALNUMBER, 2, DISPLAY_C);
                            }
               			}
               			Status.Bit.KeysReleased = FALSE;
               		break;
					
            			case DOWN_ARROW_KEY:
               			if((Status.Bit.KeysReleased == TRUE)|| DrvTimer0CounterDone(TIMER0_MS_COUNTER_2))
               			{
               				if(SerialNumberData[IputEditPostion] == '0')
							SerialNumberData[IputEditPostion] = '9 ';
						else
							SerialNumberData[IputEditPostion]--;
						
						DisplayControlString(SerialNumberData, SERIALNUMBER, 2, DISPLAY_C);
						DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 150);
               			}
               			Status.Bit.KeysReleased = FALSE;
               			break;
						
            			case UP_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE) 
               			{                       
               				if(IputEditPostion)
               				{
               					IputEditPostion--;
							AppControlStatus(CTRL_UP|CTRL_DOWN|CTRL_ENTER);
               				}
						else
						{
							AppControlStatus(CTRL_DOWN|CTRL_ENTER);
						}

						DisplayControlString(SerialNumberData, SERIALNUMBER, 2, DISPLAY_C);
               			}                       
               			Status.Bit.KeysReleased = FALSE;
               			break;					
         		}
			break;
			
		case SERIALNO_COMPLETED:
			CLEARSCREEN();
			SysDisplayString_W(DICT_TEXT_INPUTSNDONE, 1, DISPLAY_C);
			TestState++;
			break;
		case SERIALNO_END:
			
			break;
   	}
}

void AppControlIputInit(const UINT16 TitleOffset)
{
	UINT8 Index;
       AppControlStatus( CTRL_DOWN |CTRL_ENTER );
	IputEditPostion = 0;
	SysDisplayString_W(TitleOffset, 1, DISPLAY_C);
}

void DisplayControlString(const CHAR *String, unsigned char StringLength, unsigned char row, unsigned char Mask)
{
	UINT8 ByMask;
	UINT8 ByColCount;
	UINT8 Index;
	CHAR TempFontBuffer[12];
	CHAR TempChar;
	
	ByColCount = 0;
	row = (row<<1) +1;;
	if(DISPLAY_C&Mask)
		ByColCount =(120-StringLength*6)>>1;  	// Centre  
	else if(DISPLAY_RIGHT&Mask)
		ByColCount =120-StringLength*6;     	// Right
	else if(DISPLAY_L&Mask)
		ByColCount =0; 					 	// Left	
		
	for(Index=0; Index<StringLength; Index++)
	{
		ByMask = (Index==IputEditPostion)? DISPLAY_I: DISPLAY_N;
		if(String[Index]>='0' && String[Index]<='9')
		{
			TempChar = String[Index]-FONT6X16_CHAR_OFFSET;
			memcpypgm2ram((void *)TempFontBuffer,(const rom char *)&Font6x16[TempChar],12);
			Display_Graphic_6X16(row,ByColCount,TempFontBuffer, ByMask);		
		}	
		ByColCount = ByColCount+6;
	}	
}


