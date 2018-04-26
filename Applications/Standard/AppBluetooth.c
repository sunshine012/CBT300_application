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
#include "AppBluetooth.h"
#include "SysBluetooth.h"
#include "SysDisplay.h"
//#include "SysBLE4_0.h"
#include "DatDictStandard.h"
#include "DrvLCD_OPTO1140GG.h"
#include "SelfTest.h"
#include "DrvTimer_18F67J10.h"
#include "DrvEeprom_25AA320.h"
#include "AppBattest.h"

_BTTestResultData   BTTestResultData;
//UINT8 InitialStartData[7]={0x55, 0xAB, 0X01, 0X10,0X10, 0X10,0X10};
//UINT8 BatteryStartData[7]={0x55, 0xAD, 0X01, 0X10,0X10, 0X10,0X10};
//UINT8 BatteryResultData[7]={0x55, 0xAE, 0X01, 0X10,0X10, 0X10,0X10};

UINT8 BATTERY_INITIAL_REQ[2] = {0x55, 0xAB};
UINT8 BATTERY_START_REQ[2] = {0x55, 0xAD};
UINT8 BATTERY_RESULT_REQ[2] = {0x55, 0xAE};


void BTSendData(void)
{
	UINT8  i = 0;
	BTTestResultData.Start1 	=0x55;
	BTTestResultData.Start2 	=0xAA;
	BTTestResultData.End1	=0x55;
	BTTestResultData.End2	=0xBB;

	// Read EEPROM Battery Reslut Data
	// Read SerialNumer
	BTTestResultData.BatCounterL  	= (UINT8)(Battery.Counter&0xFF);	
	BTTestResultData.BatCounterH 	= (UINT8)((Battery.Counter>>8)&0xFF);
	BTTestResultData.BatType		= Battery.BatteryTypeId;
	BTTestResultData.BTVersion  	= CBTBTVERSION;
	BTTestResultData.BatRatingL	= (UINT8)(Battery.RatedCCA&0xFF);
	BTTestResultData.BatRatingH	= (UINT8)((Battery.RatedCCA>>8)&0xFF);	
	BTTestResultData.BatReslut	= Battery.Result;
	BTTestResultData.MeasureCCAL	=(UINT8)(Battery.CCA&0xFF);
	BTTestResultData.MeasureCCAH	=(UINT8)((Battery.CCA>>8)&0xFF);
	BTTestResultData.MeasureVoltageL	= (UINT8)(Battery.VoltsCD&0xFF);
	BTTestResultData.MeasureVoltageH	= (UINT8)((Battery.VoltsCD>>8)&0xFF);
	BTTestResultData.Length		= sizeof(_BTTestResultData);

	for(i=0; i<10; i++)
	{
		BTTestResultData.SerialNumber[i] = SerialNumberData[i];
	}

}

//void BLESendData(void)
//{
//	BLETestResultData.Start1 	=0x55;
//	BLETestResultData.Start2 	=0xAA;
//
//	// Read EEPROM Battery Reslut Data
//	// Read SerialNumer
//	BLETestResultData.BatCounterL  	= (UINT8)(Battery.Counter&0xFF);	
//	BLETestResultData.BatCounterH 	= (UINT8)((Battery.Counter>>8)&0xFF);
//	BLETestResultData.BatType		= Battery.BatteryTypeId;
//	BLETestResultData.BTVersion  	= CBTBTVERSION;
//	BLETestResultData.BatRatingL	= (UINT8)(Battery.RatedCCA&0xFF);
//	BLETestResultData.BatRatingH	= (UINT8)((Battery.RatedCCA>>8)&0xFF);	
//	BLETestResultData.BatReslut	= Battery.Result;
//	BLETestResultData.MeasureCCAL	=(UINT8)(Battery.CCA&0xFF);
//	BLETestResultData.MeasureCCAH	=(UINT8)((Battery.CCA>>8)&0xFF);
//	BLETestResultData.MeasureVoltageL	= (UINT8)(Battery.VoltsCD&0xFF);
//	BLETestResultData.MeasureVoltageH	= (UINT8)((Battery.VoltsCD>>8)&0xFF);
//	BLETestResultData.Length		= sizeof(_BLETestResultData);
//	BLETestResultData.SerialNumber[0] = (SerialNumberData[0]-0x30)*10 + (SerialNumberData[1]-0x30);//  Month
//	BLETestResultData.SerialNumber[1] = (SerialNumberData[2]-0x30)*10 + (SerialNumberData[3]-0x30);//  Year
//	BLETestResultData.SerialNumber[2] = (UINT8)(SerialNumberData[4]-0x30);// location
//	BLETestResultData.SerialNumber[3] = (UINT8)(SerialNumberData[5]-0x30);//
//	BLETestResultData.SerialNumber[4] = (UINT8)((SerialNumberData[6]-0x30)*10 + (SerialNumberData[7]-0x30));//
//	BLETestResultData.SerialNumber[5] = (UINT8)((SerialNumberData[8]-0x30)*10 + (SerialNumberData[9]-0x30));//
//}

void DisplayRePair(void)
{
    	/*********Display Battery Type***********/
	SysDisplayString_W(BatResultSendDICT[AppData.BTRePairId], 2, DISPLAY_C);
}

void BlueToothState(void)
{
	switch(TestState)
	{
		case BLUETOOTH_INIT:
			BTSendData();
			SysInitBlueToothRadio();
            DrvTimer0SetCounter(TIMER0_SEC_COUNTER_2, 1);
			TestState++;
			break;

        case BLUETOOTH_STARTPAIR:
            if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_2))
                TestState = BLUETOOTH_INIT;
            break;
            
		case BLUETOOTH_PAIR_COMPLETE:
			if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
			{
				DrvPan1026Off();
				OperatingState = BT_CONNECT;	
				TestState = BLUETOOTH_REPAIR;
				CLEARSCREEN();
				AppControlStatus(CTRL_DOWN|CTRL_ENTER);
				AppData.BTRePairId = BT_REPAIR_YES;
				DisplayRePair();
				SysDisplayString_W(DICT_TEXT_BTPAIRFAILREPAIR, 1, DISPLAY_C);
				DrvPan1026Init();			
			}
			break;
		case BLUETOOTH_REPAIR:
			switch(KeyPad.Keys)
         		{
            			case ENTER_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{
                  				//DrvEepromWrite((UINT16)EEAppDataAddress+5, (UINT8*)&AppData.BTRePairId, sizeof(AppData.BTRePairId));
                  				if(AppData.BTRePairId == BT_REPAIR_YES)
                  				{
                  					OperatingState = BT_CONNECT;
                  					TestState = BLUETOOTH_INIT; 
								    CLEARSCREEN();		
                  				}
								else
								{
                  					OperatingState = TEST_COMPLETE;
                  					TestState = TEST_COMPLETE_REVIEW;
								}
               			}
               			Status.Bit.KeysReleased = FALSE;
               		    break;
					
            			case DOWN_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{
							AppData.BTRePairId= BT_REPAIR_NO;
							DisplayRePair();
							AppControlStatus(CTRL_UP|CTRL_ENTER);
               			}
               			Status.Bit.KeysReleased = FALSE;
               			break;
						
            			case UP_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE) 
               			{                       
							AppData.BTRePairId = BT_REPAIR_YES;
							DisplayRePair();
							AppControlStatus(CTRL_DOWN|CTRL_ENTER);
						}                       
               			Status.Bit.KeysReleased = FALSE;
               			break;					
         		}
			break;
		case BLUETOOTH_END:
			
			break;

		default:

			break;
	}

}



