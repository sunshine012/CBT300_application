/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;  This module defines the calibrate routine(s)
;
****************************************************************************/
#include <stdlib.h>         
#include <string.h>
#include "AppCalibrat.h"
#include "AppData.h"
#include "AppEEData.h"
#include "AppUtility.h"
#include "AppBatQuest.h"
#include "AppStates.h"
#include "AppCalibrat.h"
#include "AppBattest.h"
#include "AppStartUp.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvTimer_18F67J10.h"
#include "DrvEeprom_25AA320.h"
#include "DrvUsart_18F67J10.h"
#include "DrvPan1026.h"
#include "DrvKey.h"
#include "DrvLoad.h"
#include "DrvAdc_18F67J10.h"
#include "DatDictStandard.h"
#include "SysDisplay.h"
#include "SysVoltage.h"
#include "SysCalibrate.h"


#define CAL_VOLTAGE               1000           	//10.00 volts
#define CAL_CONDUCTANCE      500        	//500 CCA

_CalDataStruct    Cal;


void CalState(void)
{
	UINT8 TempValue;
	UINT8 * TempPtr;
	
   switch(TestState)
   {
      case CALIBRATE_INIT:
            DrvPan1026Off();
            CLEARSCREEN();
            /*********Calibration Please wait***********/
            SysDisplayString_W(DICT_TEXT_CALIBATION,1,DISPLAY_C);
            SysDisplayString_W(DICT_TEXT_PLEASEWAIT,2,DISPLAY_C);
            DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 2);// 2 second
            TestState++;
            DrvUsartDisable(USART_PORT_1);
            CLRWDT();
            break;

      case CALIBRATE_QUEST:
         if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
         {
	  		MDX_TX1_RELAY0_TRIS = TRIS_BIT_OUTPUT;
			MDX_RX1_RELAY1_TRIS = TRIS_BIT_OUTPUT;
			//default cal factors at start of test (not really needed, but good idea)
            CalFactor.CDVoltsOffset = 0;
            CalFactor.ABVoltsOffset = 0;
	     	CalFactor.GOffset		=  0;
            CalFactor.CDVoltsGain 	= CAL_BASE;
            CalFactor.ABVoltsGain 	= CAL_BASE;
	     	CalFactor.GGain          	= CAL_BASE;
            CAL_RELAY0 = 0;            //Set Relays for CD Volts  (0,0)
            CAL_RELAY1 = 0;            //
		    DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);// 1 second	
            TestState++;
         }
         CLRWDT();
         break;

      case CALIBRATE_VOLTS:
         if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
          {
              //CLEARSCREEN();
          	Battery.VoltsCD = SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 16);
			Battery.VoltsAB = SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 16);	
             CalFactor.CDVoltsGain = (UINT16)((UINT32)CAL_VOLTAGE * (UINT32)CAL_BASE / (UINT32)Battery.VoltsCD);
             CalFactor.ABVoltsGain = (UINT16)((UINT32)CAL_VOLTAGE * (UINT32)CAL_BASE / (UINT32)Battery.VoltsAB);
			//CalFactor.CDVoltsOffset =  Battery.VoltsCD-CAL_VOLTAGE
             CAL_RELAY0 = 1;                 //Set Relays for CCA  (1,0)
             DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);// 1 second
             TestState++;
          }
          CLRWDT(); 
          break;

      case CALIBRATE_CCA:
         if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
         {
				TestState++;
         }
         CLRWDT();
         break;

      case BATTERY_TEST_CCA_INIT:
      case BATTERY_TEST_CCA:
      case BATTERY_TEST_SCALE:
         BatteryTestState();           //test the battery
         break;

      case BATTERY_TEST_DONE:          //transmit the battery data
         CalFactor.GGain = (UINT16)((UINT32)CAL_CONDUCTANCE * (UINT32)CAL_BASE / (UINT32)Battery.CCA);
	  	CalFactor.GOffset = 0;
	  	CalFactor.ABVoltsOffset= 0;
	  	CalFactor.CDVoltsOffset= 0;
	  	CalFactor.SerialNumber = 0;
         CAL_RELAY0 = 0;               //Reset Relays to voltage measurement position.(0,0)
         TestState++; 
         break;

      case CALIBRATE_APPLY:
         CalFactor.CheckSum = CalFactorsCheckSum();
         if(CalFactor.CDVoltsGain < 9000 || CalFactor.CDVoltsGain > 11000 ||
            CalFactor.ABVoltsGain < 9000 || CalFactor.ABVoltsGain > 11000 ||
            CalFactor.GGain < 9000 || CalFactor.GGain > 11000)
         {
            	TestState = CALIBRATE_FAILED;
				
         	/*TempPtr=itoabase(CalFactor.CDVoltsGain, DisplayBuffer,5, 10);
		strcatpgm2ram((char *)DisplayBuffer, " :GCD ");	
		DisplayString_S(DisplayBuffer, 1, DISPLAY_C);
         	TempPtr=itoabase(CalFactor.ABVoltsGain, DisplayBuffer,5, 10);
		strcatpgm2ram((char *)DisplayBuffer, " :GCD ");	
		DisplayString_S(DisplayBuffer, 2, DISPLAY_C);
         	TempPtr=itoabase(CalFactor.GGain, DisplayBuffer,5, 10);
		strcatpgm2ram((char *)DisplayBuffer, " :GG ");	
		DisplayString_S(DisplayBuffer, 3, DISPLAY_C);	
		*/
		
         }
         else
         {
            DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 3);// 3 second
            TestState++;
         }
         CLRWDT();
         break;

      case CALIBRATE_CHECK_VOLTAGES:
        	 if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
         	{
				Battery.VoltsCD 	= SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 16);
				Battery.VoltsAB	= SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 16);	
            		if(Battery.VoltsCD >= 997 && Battery.VoltsCD <= 1003 &&
               		Battery.VoltsAB >= 997 && Battery.VoltsAB <= 1003)
            		{
               		TestState++;
		  		DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 3);// 3 second	   
               		CAL_RELAY0 = 1;         //Relays to cca position.   (0,1)
            		}					
            		else
            		{
               		TestState = CALIBRATE_FAILED;
            		}
			/*TempPtr=FormatVoltage(Battery.VoltsCD, tempBuffer);
			memset(DisplayBuffer,0x00,sizeof(DisplayBuffer));
			strcatpgm2ram((char *)DisplayBuffer,"CAL CD VOLT:");
			strcat((char *)DisplayBuffer,(char *)tempBuffer);
			DisplayString_S(DisplayBuffer,2,DISPLAY_C);
			TempPtr=FormatVoltage(Battery.VoltsAB, tempBuffer);
			memset(DisplayBuffer,0x00,sizeof(DisplayBuffer));
			strcatpgm2ram((char *)DisplayBuffer,"CAL AB VOLT:");
			strcat((char *)DisplayBuffer,(char *)tempBuffer);
			DisplayString_S(DisplayBuffer,3,DISPLAY_C);		*/	
					
         	}
         CLRWDT();  
         break;

      case CALIBRATE_CHECK_CCA_WAIT:
         if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
         {
            TestState++;
         }
         CLRWDT();
         break;

      case CALIBRATE_CHECK_CCA_INIT:
      case CALIBRATE_CHECK_CCA:
      case CALIBRATE_CHECK_SCALE:
         BatteryTestState();           //test the battery
         break;

      case CALIBRATE_CHECK_CCA_DONE:   //transmit the battery data
        if(Battery.CCA >= 495 && Battery.CCA <= 505)
         {
            	CLEARSCREEN();
		////********Calibration done***********/
            SysDisplayString_W(DICT_TEXT_CALIBATIONDONE,1,DISPLAY_C);
            TempPtr=FormatVoltage(Battery.VoltsCD, tempBuffer);
            memset(DisplayBuffer,0x00,sizeof(DisplayBuffer));
            strcatpgm2ram((char *)DisplayBuffer,"CAL CD VOLT:");
            strcat((char *)DisplayBuffer,(char *)tempBuffer);
            DisplayString_S(DisplayBuffer,3,DISPLAY_C);		
            TempPtr=itoabase(Battery.CCA, DisplayBuffer,4, 10);
            strcatpgm2ram((char *)DisplayBuffer, "CCA ");	
            DisplayString_S(DisplayBuffer, 4, DISPLAY_C);
            DrvEepromWrite((UINT16)&EECalFactor, (UINT8*)&CalFactor, sizeof(_CalFactorStruct));

    		/*memcpypgm2ram((void *)&Battery,(rom void *)&EEBatteryInit,sizeof(_BatteryData));
             	DrvEepromWrite((UINT16)EEBatteryAddress, (UINT8*)&Battery, sizeof(_BatteryData));
    		memcpypgm2ram((void *)&AppData,(rom void *)&EEAppDataInit,sizeof(_AppData));
             	DrvEepromWrite((UINT16)EEAppDataAddress, (UINT8*)&AppData, sizeof(_AppData));			
    		memcpypgm2ram((void *)&SerialNumberData,(rom void *)&EESerialNumberDataInit,sizeof(SerialNumberData));
             	DrvEepromWrite((UINT16)EESerialNumberDataAddress, (UINT8*)SerialNumberData, sizeof(SerialNumberData));
    		memcpypgm2ram((void *)&BTRemoteData,(rom void *)&EEBTRemoteDataInit,sizeof(_BTRemoteData));
             	DrvEepromWrite((UINT16)EEBTRemoteDataAddress, (UINT8*)&BTRemoteData, sizeof(_BTRemoteData));			
    		memcpypgm2ram((void *)&AppGlobalFlg,(rom void *)&EEAppGlobalFlgInit,sizeof(_AppGlobalFlg));
             	DrvEepromWrite((UINT16)EEAppGlobalFlgAddress, (UINT8*)&AppGlobalFlg, sizeof(_AppGlobalFlg));*/

		    DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);// 2 second        
            TestState = CALIBRATE_COMPLETED;
         }
         else
         {
		    TestState = CALIBRATE_FAILED;  
         }		 
         break;

      case CALIBRATE_FAILED:	  	
             CLEARSCREEN();
		////********Calibration was fail***********/
	       SysDisplayString_W(DICT_TEXT_CALIBATIONFAIL,1,DISPLAY_C);
         	TempPtr=itoabase(Battery.CCA, DisplayBuffer,4, 10);
			strcatpgm2ram((char *)DisplayBuffer, "CCA ");	
			DisplayString_S(DisplayBuffer, 4, DISPLAY_C);
	       TestState = CALIBRATE_END; 

         break;
      case CALIBRATE_COMPLETED:    
	       if(CBT300_CONFIG == ConfigData)
			{	
        	 	if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
         		{
					TestState = SERIALNO_INITIALIZE;
					OperatingState = SERIALNOINPUT_STATE;
        	 	}
	    	}
		 	else
		 	{
				TestState = CALIBRATE_END;
		 	}
         break;
      case CALIBRATE_END:
	  	
         break;		 
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// This function performs the tool calibration.
//
// Parameters Passed:   None
// Parameters Returned: None
//
// Notes:
//
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 01-31-08    RJ          Developed

void AppCommissionTool(_Bool MessageDisplay)
{
   UINT16            i;
   UINT8             data;
   UINT8             Gain; 
   UINT32            Capacity;
   UINT8             buffer[16];

#define Voltage   i

   TestState = CALIBRATION_INITIALIZE;
   while(1)                            //calibration task
   {
      switch(TestState)
      {
         case CALIBRATION_INITIALIZE:
            Clear_Screen();
                        //clear screen and display the results
            if( MessageDisplay )
            {
                SysDisplayString_W(DICT_TEXT_PROGRAMING,1,DISPLAY_C);
                SysDisplayString_W(DICT_TEXT_PLEASEWAIT,2,DISPLAY_C);
            }
            SysSendOk();               //acknowledge
            DrvLoadOff();
            TestState++;
            DrvUsartInit( USART_PORT_1, USART_BAUD_RATE_57600,(GlobalDataBuffer.DataGlobalBuffer), 200 );
            break;

         default:                      //check if start command   
            do{
               DrvUsartReset(USART_PORT_1);       
               while(DrvUsartByteReady( USART_PORT_1) == FALSE)
                  CLRWDT();            //wait until data ready
                                       //read data
               DrvUsartReadByte( USART_PORT_1, &data );
            }while(data != 0xFF);
                                       //read and save command
            while(DrvUsartByteReady( USART_PORT_1) == FALSE)
               ;                       //wait until data ready
                                       //read data
            DrvUsartReadByte( USART_PORT_1, &Cal.Command );
                                       
            switch(Cal.Command)        //check command received
            {
               case CAL_UPDATE_COMPLETE:
                                       //clear screen and display the results
                    SysDisplayString_W(DICT_TEXT_UPDATECOMPLETE,1,DISPLAY_C);
                    SysDisplayString_W(DICT_TEXT_RESTARTTOOL,2,DISPLAY_C);
                    break;
      
               case CAL_READ_VOLTAGE:  //read the voltages AB, CD and CB
                  /*if(SysLoadCalFactors() == FALSE)
                  {
                     AppDisplayMessage(DICT_TEXT_ERROR, MESSAGE_ID_CAL_FACTOR_ERROR, 3);
                                       //bad command
                     SysCommandError();
                     TestState = CALIBRATION_INITIALIZE;   
                  }
                  else
                  {
                     memset(buffer, 0x00, sizeof(buffer));
                     Voltage = SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 100);         
                     memcpy(buffer, (void*)&Voltage, 2);
                     Voltage = SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 100);         
                     memcpy(buffer+2, (void*)&Voltage, 2);                
                     Voltage = SysGetVoltage(ADC_CHANNEL_CB_VOLTS, 100);         
                     memcpy(buffer+4, (void*)&Voltage, 2);
                     DrvUsartSendData( USART_PORT_1, buffer, 8 );
                     AppDisplayMessage(DICT_TEXT_CALIBRATION, MESSAGE_ID_WAITING_FOR_COMMAND, 3);
                  }*/
                  break;

               case CAL_READ_CAPACITY: //read the capacity
                  /*if(SysLoadCalFactors() == FALSE)
                  {                    //calibration factors check sum error
                     AppDisplayMessage(DICT_TEXT_CALIBRATION, MESSAGE_ID_CAL_FACTOR_ERROR, 3);
                                       //bad command
                     SysCommandError();
                     TestState = CALIBRATION_INITIALIZE;   
                  }
                  else
                  {
                     DrvCcaStart();    //initialize for the CCA test
                     while(CcaState != CCA_STATE_MEASUREMENT_READY)
                     {                 //draw bar
                        SysGraphicBar(5, 14, 100, 
                                      (UINT8)((UINT16)CcaCycleCounter * 100 / CCA_MEASUREMENT_END));
                     }
                     DrvCcaStop();     //clean up after CCA test, disable load etc.
                     Capacity = SysCalculateCCA(CcaIdiffHighSum - CcaIdiffLowSum, 
                                                CcaVdiffHighSum - CcaVdiffLowSum,
                                                DrvGainGet());
                     memset(buffer, 0x00, sizeof(buffer));
                     memcpy(buffer+6, (void*)&Capacity, 2);
                     DrvUsartSendData( USART_PORT_1, buffer, 8 );
                     AppDisplayMessage(DICT_TEXT_CALIBRATION, MESSAGE_ID_WAITING_FOR_COMMAND, 3);
                  }*/
                  break;
      
               case CAL_BASE_ADDRESS:  //set the base address
                  Cal.Address = 0;
                  for(i = 0; i < 4; i++)
                  {
                     Cal.Address <<= 8;
                     while(DrvUsartByteReady( USART_PORT_1) == FALSE)
                        ;              //wait until data ready
                                       //read data
                     DrvUsartReadByte( USART_PORT_1, &data );
                     Cal.Address |= (UINT32)data;
                  }
                  SysSendOk();         //acknowledge
                  break;
      
               case CAL_NUM_BYTES:     //set the number of bytes high byte
                  Cal.NumberOfBytes = 0;
                  for(i = 0; i < 4; i++)
                  {
                     Cal.NumberOfBytes <<= 8;
                     while(DrvUsartByteReady( USART_PORT_1) == FALSE)
                        ;              //wait until data ready
                                       //read data
                     DrvUsartReadByte( USART_PORT_1, &data );
                     Cal.NumberOfBytes |= (UINT32)data;
                  }
                  SysSendOk();         //acknowledge
                  break;
            
               case CAL_MEMORY_UPLOAD: //transmit memory to host
                  Cal.Address = SysMemoryUpLoad(Cal.Address, Cal.NumberOfBytes);   
                  break;
      
               case CAL_MEMORY_DOWNLOAD:
                                       //load memory from host
                  Cal.Address = SysMemoryDownLoad(Cal.Address, Cal.NumberOfBytes); 
                  SysSendOk();         //acknowledge
                  break;
      
               case CAL_FLASH_UPLOAD:  //transmit flash to host
                  /*Cal.Address = SysFlashMemoryUpLoad(Cal.Address, Cal.NumberOfBytes);
                  SysDictSelect( DICT_ID_STANDARD, DATA_LOCATION );
                  SysDictSelectLanguage( DICT_LANGUAGE_ENGLISH_US );
                  MessageDisplay = TRUE;*/
                  break;

               case CAL_FLASH_DOWNLOAD://load flash from host
                  /*Cal.Address = SysFlashMemoryDownLoad(Cal.Address, Cal.NumberOfBytes);
                  SysSendOk();         //acknowledge*/
                  break;
         
               case CAL_FLASH_ERASE_SECTOR:
                                       //erase sector
                  /*MessageDisplay = FALSE;
                  DrvFlashSectorErase(FLASH_ADDRESS_TO_SECTOR(Cal.Address));
                  SysSendOk();         //acknowledge*/
                  break;
         
               case CAL_SEND_FIRMWARE: //send the firmware version
                  /*strcpypgm2ram((char*)buffer, FirmwareVersion);
                  DrvUsartSendData(USART_PORT_1, buffer, strlen((char*)buffer) + 1);*/
                  break;
         
               case CAL_SEND_SERIAL_NUMBER:
                                       //send the serial number
                  //SysSendSerialNumber();
                  break;
         
               case CAL_SEND_RTC_DATA: //send RTC data
                  //SysRTCMemoryUpLoad(Cal.NumberOfBytes);   
                  break;
         
               case CAL_SET_RTC_DATA:  //set time
                  //Cal.Address = SysRTCMemoryDownLoad(Cal.Address, Cal.NumberOfBytes);
                  //SysSendOk();         //acknowledge
                  break;

               case CAL_WATCHDOG:
                  //Reset();

               case CAL_TOOL_ID:       //send tool ID number
                  //SysSendToolID();
                  break;
         
               default:                //bad command
                  SysCommandError();
                  TestState = CALIBRATION_INITIALIZE;   
            }
            break;
      }
      CLRWDT();                        //reset the internal software watchdog
   }
   
#undef Voltage   
}


