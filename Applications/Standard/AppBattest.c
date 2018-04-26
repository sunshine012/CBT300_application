/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;  This module defines the battery testing state routine(s)
;
****************************************************************************/
#include <stdlib.h>         
#include <string.h>
#include "AppCurvePN.h"
#include "AppData.h"
#include "AppEEData.h"
#include "AppBattest.h"
#include "AppUtility.h"
#include "AppCalibrat.h"
#include "AppStates.h"
#include "AppBatQuest.h"
#include "AppBluetooth.h"
#include "AppCalibrat.h"
#include "DrvCca.h"
#include "DrvAdc_18F67J10.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvKey.h"
#include "DrvTimer_18F67J10.h"
#include "DrvUsart_18F67J10.h"
#include "DrvEeprom_25AA320.h"
#include "DatDictStandard.h"
#include "SelfTest.h"
#include "SysDisplay.h"
#include "SysVoltage.h"
#include "SysBluetooth.h"

UINT16     BatCapacity2;

/****************************************************************************

   This function calculates a 16 sum average of AB and CD voltages.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   10-10-01    CS          Developed

****************************************************************************/
//		    //MCR400 matching table
//const UINT16 MCR400Table[12] = {965,    //   0 -  127 CCA 
//                                969,    // 128 -  255 CCA
//                                979,    // 256 -  383 CCA
//                                1000,   // 384 -  511 CCA
//                                1010,   // 512 -  639 CCA
//                                1014,   // 640 -  767 CCA
//                                1016,   // 768 -  895 CCA
//                                1017,   // 896 - 1023 CCA
//                                1017,   //1024 - 1151 CCA
//                                1017,   //1152 - 1279 CCA
//                                1017,   //1280 - 1407 CCA
//                                1017    //1408 - 1535 CCA
//                               };
		    //MCR400 matching table
const UINT16 MCR400Table[12] = {984,    //   0 -  127 CCA 
                                990,    // 128 -  255 CCA
                                1012,    // 256 -  383 CCA
                                1023,   // 384 -  511 CCA
                                1036,   // 512 -  639 CCA
                                1042,   // 640 -  767 CCA
                                1044,   // 768 -  895 CCA
                                1046,   // 896 - 1023 CCA
                                1046,   //1024 - 1151 CCA
                                1046,   //1152 - 1279 CCA
                                1046,   //1280 - 1407 CCA
                                1046    //1408 - 1535 CCA
                               };
				
/****************************************************************************

   This function performs the battery test operations.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:
                                    V(IDiff)
                                ----------
                                 .2 * 10ohm
      Capacity = 3.125 * ----------
                                  V(VDiff)
                               ----------
                              	107.1
      collect terms

                                     V(IDiff)
      Capacity = 167.34 * ----------
                                     V(VDiff)

//                                    V(IDiff)
//                                ----------
//                                 .2 * 10ohm
//      Capacity = 3.125 * ----------
//                                  V(VDiff)
//                               ----------             
//                              5.1(0.1*51)---  (R23/R28)*((R24+R30)/R30)
//      collect terms
//
//                                     V(IDiff)
//      Capacity = 7.968 * ----------(79.6875)
//                                     V(VDiff)

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   10-01-01    CS          Developed
   05-13-02    KD          Added rating and units to display line 2

****************************************************************************/
void BatteryTestState(void)
{
   UINT32 Capacity;
   UINT32 DisplayCapacity;
   UINT8 	TempValue;
   UINT16 TempCcaRelative;

   
   switch(TestState)
   {
      case BATTERY_TEST_INITIALIZE:
	CLEARSCREEN();
	SysDisplayString_W(DICT_TEXT_TESTINGBATTERY, 1, DISPLAY_C);
	SysDisplayString_W(DICT_TEXT_PLEASEWAIT, 2, DISPLAY_C);
	
	Battery.VoltsCD = SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 16);
	//Battery.VoltsAB = SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 16);
	
	DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);
            TestState++;                     
         break;

      case CALIBRATE_CHECK_CCA_INIT:
      case BATTERY_TEST_CCA_INIT:      //load counter for CCA test  
      if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
       {  
       	DrvCcaStart(); 
         	TestState++;                  //move to next test state
      	}
	 break;
      case CALIBRATE_CHECK_CCA:
      case BATTERY_TEST_CCA:           //run the Micro 400 type test
      		TestState++;
         break;

      case CALIBRATE_CHECK_SCALE:
      case BATTERY_TEST_SCALE:  
	   if( CcaState == CCA_STATE_MEASUREMENT_READY )
   	   {   
   	   		DrvCcaStop(); 
         	Battery.CCA = 0;
         	if(CcaVdiffLowSum > CcaVdiffHighSum)  
         	{      //////////////////////////////////////calculate CCA                                             
            		Capacity = (CcaIdiffHighSum-0)*159;//IDiff times scaler, ideal 167
            		Capacity /= (CcaVdiffLowSum- CcaVdiffHighSum); //MHOs = IDiff divided by VDiff
            		Capacity *= (UINT32)CalFactor.GGain;
            		Capacity /= 10000;
					//Capacity +=CalFactor.GOffset;
					Battery.CCA = Capacity;
            		if(Battery.VoltsCD > 550)         //save cca if above 5.5V and positive
            		{                          //check capacity value against limit
						if(Battery.CCA > MAX_MEASURED_CAPACITY)
               		{
                  			Battery.CCA = MAX_MEASURED_CAPACITY;   //limit to maximum
               		}

						if(CcaVdiff2 >  CcaVdiff2L)
						{
							CcaVdiff2 = CcaVdiff2 - CcaVdiff2L;
            				Capacity = (CcaIdiffLowSum - 0 )*8;   //7.968
            				Capacity /= CcaVdiff2;
            				Capacity *= (UINT32)CalFactor.GGain;
            				Capacity /= 10000;
							//Capacity +=(CalFactor.GOffset/8);
							BatCapacity2 = Capacity;
						}
						
						if(OperatingState != CALIBRATE)
						{
         					Battery.CCA = ((UINT32)Battery.CCA * MCR400Table[Battery.CCA >> 7]) /1000;
							if(Battery.CCA < 150)
							{
								Battery.CCA = ((UINT32)BatCapacity2 *95)/100;// Battery.CCA*0.95
							}
						}
            		}
         	}
		
         	TestState++;                 
	      }
         break;
		 
      case BATTERY_TEST_DONE:
			
         Battery.Result = BatteryConductanceTest();
	   TempCcaRelative = (UINT16)((((UINT32)Battery.CCA) * 100) / (UINT32)Battery.RatedCCA);
	  Battery.SOH = GetSOHPercent(Battery.Result, TempCcaRelative, Battery.VoltsCD, Battery.AlgorithmId); 

	  
         if(BAT_TYPE_AGM == Battery.BatteryTypeId)
         {
		 DisplayCapacity = (UINT32)Battery.CCA *83;
		 Battery.CCA 	= DisplayCapacity /100;
         }

	   			if(EOLTestFlg == FALSE)
	   			{
		 			if(Battery.Counter == 0xFFFF)
		 			{
		 				Battery.Counter = 0;
		 			}
		 			else
		 			{
		 				Battery.Counter ++;
		 			}
	   	 		}
		
				if(CONDITION_BADCELL == Battery.Result )
				{
						Battery.CCA 	= 0;
				}
				
       DrvEepromWrite((UINT16)&EEBattery, (UINT8*)&Battery, sizeof(_BatteryData));
       MDX_DELAY_10MS(5); 
					
		 StartBatteryTestFlg = TRUE;
        OperatingState = TEST_COMPLETE;
        TestState = TEST_COMPLETE_INIT;

         break;

	default:
		break;
   }
}

//
//
//

void TestCompleteWait(void)
{
	unsigned char *temp;
	unsigned char tempchar = 0;
	UINT16 TempContance;

   switch(TestState)
   {
	 case TEST_COMPLETE_INIT:
   
	CLEARSCREEN();
	tempchar = Battery.Result;
	SysDisplayString_W(BatteryResultDICT[tempchar], 1, DISPLAY_C);
	
   	temp = FormatVoltage(Battery.VoltsCD, tempBuffer);
	DisplayBuffer[0] = 0x00;
	strcatpgm2ram((char *)DisplayBuffer, " ");
	strcat((char *)DisplayBuffer, (char *)tempBuffer);
	DisplayString_S(DisplayBuffer, 3, DISPLAY_N);

	if(CONDITION_BADCELL != Battery.Result )
	{
   		temp=itoabase(Battery.CCA, DisplayBuffer,4, 10);
		strcatpgm2ram((char *)DisplayBuffer, "CCA ");
		DisplayString_S(DisplayBuffer, 3, DISPLAY_R);
	}
	// display Battery Name
//	if(Battery.BatJISIndex != 0xFF)
	if(Battery.BatJISIndex < JIS_NUM_ARRAY_SIZE && Battery.BatJISIndex > 0)
	{
   		strcpypgm2ram((char *)DisplayBuffer, " ");
		strcatpgm2ram((char *)DisplayBuffer,(const rom char*)(JISNumbers[Battery.BatJISIndex].Text));
		DisplayString_S(DisplayBuffer, 4, DISPLAY_N);
		// display Battery Rating
   		temp=itoabase(Battery.RatedCCA, DisplayBuffer,4, 10);
		strcatpgm2ram((char *)DisplayBuffer, "CCA ");
		DisplayString_S(DisplayBuffer, 4, DISPLAY_R);
//   		temp=itoabase(Battery.AlgorithmId, DisplayBuffer,4, 10);
//		strcatpgm2ram((char *)DisplayBuffer, "ALG ");
//		DisplayString_S(DisplayBuffer, 4, DISPLAY_R);		
	}
	else
	{
   		strcpypgm2ram((char *)DisplayBuffer, " INVID NB");
		DisplayString_S(DisplayBuffer, 4, DISPLAY_N);	
		// display Battery Rating
   		temp=itoabase(Battery.RatedCCA, DisplayBuffer,4, 10);
   		strcpypgm2ram((char *)DisplayBuffer, " ");
		strcatpgm2ram((char *)DisplayBuffer, "CCA ");
		DisplayString_S(DisplayBuffer, 4, DISPLAY_R);
	}
 	SPPBatteryTestState = BATTERY_STATE_FINISH;
	TestState = TEST_COMPLETE_END;
	
	break;
 	case TEST_COMPLETE_WAIT:
	switch(KeyPad.Keys)
       {
            case ENTER_KEY:
               if(Status.Bit.KeysReleased == TRUE)
               {
						if(CBT300_CONFIG == ConfigData)
						{
							CLEARSCREEN();  
                  		OperatingState = BAT_RESULT_SEND_QUESTION;
                  		TestState = BAT_RESULT_SEND_INITIALIZE;              
						}
						else if(CBT100_COMFIG == ConfigData)
						{

						}
               }                      
               Status.Bit.KeysReleased = FALSE;
               break;

            case DOWN_ARROW_KEY:
               if(Status.Bit.KeysReleased == TRUE) 
               {                      

               }                       
               Status.Bit.KeysReleased = FALSE;
               break;				
            case UP_ARROW_KEY:
               if(Status.Bit.KeysReleased == TRUE)
               {                      

               }                       
               Status.Bit.KeysReleased = FALSE;
               break;
         }
		
	break;	
 	case TEST_COMPLETE_REVIEW:

	CLEARSCREEN();
	tempchar = Battery.Result;
	SysDisplayString_W(BatteryResultDICT[tempchar], 1, DISPLAY_C);
	
   	temp = FormatVoltage(Battery.VoltsCD, tempBuffer);
	DisplayBuffer[0] = 0x00;
	strcatpgm2ram((char *)DisplayBuffer, " ");
	strcat((char *)DisplayBuffer, (char *)tempBuffer);
	DisplayString_S(DisplayBuffer, 3, DISPLAY_N);
	
	if(CONDITION_BADCELL != Battery.Result )
	{
   		temp=itoabase(Battery.CCA, DisplayBuffer,4, 10);
		strcatpgm2ram((char *)DisplayBuffer, "CCA ");
		DisplayString_S(DisplayBuffer, 3, DISPLAY_R);
	}

//	if(Battery.BatJISIndex != NON_MOTORCYCLE_JIS_LIST)
	if(Battery.BatJISIndex < 61 && Battery.BatJISIndex > 0)
	{
		// display Battery Number
   		strcpypgm2ram((char *)DisplayBuffer, " ");
		strcatpgm2ram((char *)DisplayBuffer,(const rom char*)(JISNumbers[Battery.BatJISIndex].Text));
		DisplayString_S(DisplayBuffer, 4, DISPLAY_N);
		// display Battery Rating
   		temp=itoabase(Battery.RatedCCA, DisplayBuffer,4, 10);
		strcatpgm2ram((char *)DisplayBuffer, "CCA ");
		DisplayString_S(DisplayBuffer, 4, DISPLAY_R);
	}
	else
	{
   		strcpypgm2ram((char *)DisplayBuffer, " INVID NB");
		DisplayString_S(DisplayBuffer, 4, DISPLAY_N);	
		// display Battery Rating
   		temp=itoabase(Battery.RatedCCA, DisplayBuffer,4, 10);
   		strcpypgm2ram((char *)DisplayBuffer, " ");
		strcatpgm2ram((char *)DisplayBuffer, "CCA ");
		DisplayString_S(DisplayBuffer, 4, DISPLAY_N);
	}	
	
	TestState = TEST_COMPLETE_END;
	break;
 	case TEST_COMPLETE_END:

	break;
	
 	case TEST_SELF_COMPLETE_END:

		switch(KeyPad.Keys)
       	{	
       		case ENTER_KEY:
			       if(Status.Bit.KeysReleased == TRUE) 
               	{ 
							CLEARSCREEN();
             				OperatingState = VOLTAGE_TEST;
             				TestState = VOLTAGE_TEST_INIT;
			       }
				Status.Bit.KeysReleased = FALSE;
			break;
			
			default:
				break;
		}
	break;
   	}

}


/****************************************************************************

   This routine reads curve and calculates good, OK and bad percents.

   Parameters Passed:   Pointer to good, OK and bad percentages
   Parameters Returned: Normalized voltage

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   10-05-01    CS          Developed
   05-19-03    CS          Modified to get OK percent

****************************************************************************/
UINT16 GetCurvePercent(UINT8 *GoodPercent, UINT8 *BadPercent)
{
   UINT16 Voltage, Index;

   Voltage = Battery.VoltsCD;          //Normalize voltage

   if(Voltage < 800)            //voltage less than 8.00volts, clamp to
   {                                   //minimum percent
      *GoodPercent = GlobalDataBuffer.CurveData.GoodPct[0];
      *BadPercent = GlobalDataBuffer.CurveData.BadPct[0];
   }
   else if(Voltage > 1275)
   {                                   //voltage greater than 12.75volts, clamp to
                                       //maximum percent
      *GoodPercent = GlobalDataBuffer.CurveData.GoodPct[95];
      *BadPercent = GlobalDataBuffer.CurveData.BadPct[95];
   }
   else                                //otherwise lookup percent in table
   {
      Index = (Voltage - 800) / 5;
      *GoodPercent = GlobalDataBuffer.CurveData.GoodPct[Index];
      *BadPercent = GlobalDataBuffer.CurveData.BadPct[Index];
   }

   return Voltage;
}

/****************************************************************************

   This routine calculates the battery condition, good, OK-Replace Soon,
   good recharge, Charge-Replace Soon, replace, badcell or charge and retest.

   Parameters Passed:   None
   Parameters Returned: battery test decision

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   07-26-00    RJ          Developed
   05-19-03    CS          Added OK-Replace Soon and Charge-Replace Soon

****************************************************************************/
UINT8 BatteryConductanceTest(void)
{
   UINT8  GoodPercent, BadPercent;
   UINT16 OKToTestVoltage;
   UINT16 Voltage;
   UINT16 Conductance;
   UINT8 Index,Temp;

   memcpypgm2ram((CHAR *)&GlobalDataBuffer.CurveData,&Curve[Battery.AlgorithmId], sizeof(_CurveDataStruct));
//   memcpypgm2ram((CHAR *)&GlobalDataBuffer.CurveData,&Curve[Battery.BatteryTypeId], sizeof(_CurveDataStruct));

   OKToTestVoltage = GlobalDataBuffer.CurveData.OkToTestVoltage;

   Conductance = (UINT16)((((UINT32)Battery.CCA) * 100) / (UINT32)Battery.RatedCCA);

   if(Conductance > 255)
      Battery.Conductance = 255;       //limit conductance to 255%
   else
      Battery.Conductance = Conductance;
                                       //Get good, OK and bad percents
                                       //and normalize voltage
   Voltage = GetCurvePercent(&GoodPercent, &BadPercent);

   if(Battery.Conductance >= GoodPercent)      
   {                                   //good or good recharge
      if((Voltage >= GlobalDataBuffer.CurveData.FullChargeVoltage) ||
         (Voltage >= GlobalDataBuffer.CurveData.RechargeVoltage &&
          Battery.Conductance >= GlobalDataBuffer.CurveData.AboveRechargePct) ||
         (Voltage >= GlobalDataBuffer.CurveData.BadCellHighVoltage &&
          Battery.Conductance > GlobalDataBuffer.CurveData.BelowRechargePct))
      {
         	return(CONDITION_GOOD);       //good battery
      }
      else if((Voltage < GlobalDataBuffer.CurveData.BadCellHighVoltage) &&
              (Voltage > GlobalDataBuffer.CurveData.BadCellLowVoltage))
      {
         	return(CONDITION_BADCELL);
      }
      else if(Voltage >= GlobalDataBuffer.CurveData.BadCellHighVoltage &&
				Voltage < GlobalDataBuffer.CurveData.RechargeVoltage)
//              Voltage < GlobalDataBuffer.CurveData.OkToTestVoltage)
      	{
				//return(CONDITION_CHARGE_RETEST);
				return(CONDITION_GOOD_RECHARGE);//good recharge
      	}
//      else if((Voltage >= GlobalDataBuffer.CurveData.OkToTestVoltage &&
//              Voltage < GlobalDataBuffer.CurveData.RechargeVoltage) ||
//              (Voltage >= GlobalDataBuffer.CurveData.RechargeVoltage &&
//              Voltage < GlobalDataBuffer.CurveData.FullChargeVoltage && 
//              Battery.Conductance < GlobalDataBuffer.CurveData.AboveRechargePct))
//      {                                //good recharge
//         return(CONDITION_GOOD_RECHARGE);
//      }
   }                                   //check for replace battery
   if((Voltage > OKToTestVoltage) && (Battery.Conductance < BadPercent))
   {
      return(CONDITION_REPLACE);       //replace
   }
                                       //return charge and retest if none of the
   return(CONDITION_CHARGE_RETEST);    //other conditions are true
}

///////////////////////////////////////////////////////////////////////////////////////
//
// Parameters Passed:   Test result, percent capacity, test voltage, Temperature selection
//                      Algorithm used
//
// Parameters Returned: Bitmap column (percent)
//
// Notes:
//
//                             Percent_CCA * 85
// DividingLine = ----------------------------------------------
//                CurveTempCompFactor * Curve @ Measured_Voltage
//
// 
//
//                                           +
//                                           +
//                                           +
//                                           +
//                                           +
//  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  0                                        3                                                                             1
//                          |--------------->7                                                                             1
//                          |                                                                                              9
//  Percent = slope * DividingLine + b       (pixel 37)                                                                    
//
// Mapping function for the ramp bitmap, bitmap is 120 pixels wide
//
//    Good / Good Recharge
//                119 - 37   82              119 - 37                    37 * 15     6970     6415
//       slope => -------- = --    Offset => -------- * 85 + b = 40  b = -------  -  ----  =  ----
//                100 - 85   15              100 - 85                       15        15       15
//
//    Charge & Retest
//                 36 - 0    36              36 - 0                         36 * 70      2520
//       slope => -------- = --    Offset => ------- * 70 + b = 0     b = - -------  = - ----
//                 85 - 70   15              85 - 70                           15         15
//
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 03-27-08    RJ          Developed
//
UINT8 GetSOHPercent( UINT8 TestResultId, UINT8 CcaRelative, UINT16 Voltage, UINT8 AlgorithmId )
{
   INT32 Percent;
   UINT8 GraphColumn;
   UINT8 CurvePassValue;
   
   if(Voltage < 1100)
      Voltage = 1100;
   if(Voltage > 1275)
      Voltage = 1275;   
   
   memcpypgm2ram((CHAR *)&GlobalDataBuffer.CurveData,&Curve[AlgorithmId], sizeof(_CurveDataStruct));

   CurvePassValue = GlobalDataBuffer.CurveData.GoodPct[(Voltage - 800) / 5];
   if(CurvePassValue == 0)             //going to divide by curve value                 
      CurvePassValue = 1;              //so don't let value equal zero
                                       //compute percent
   Percent = (CcaRelative * (UINT32)85) / CurvePassValue;
                                       //check if temp compensated

   switch( TestResultId )
   {                                   //coordinate mapping for bitmap
      case CONDITION_GOOD:
      case CONDITION_GOOD_RECHARGE:
         Percent = ((82 * Percent) - 6415) / 15;
         if(Percent < 37)
            Percent = 37;		 
         break;

      case CONDITION_CHARGE_RETEST:
         Percent = ((36 * Percent) - 2520) / 15;
         if(Percent > 37)
            Percent = 37;		 
         break;

      case CONDITION_REPLACE:
      case CONDITION_BADCELL:
                                       //-lint drop thru
      default:
         Percent = 0;
	break;
   }
   
   if( Percent < 0 )
      Percent = 0;
   else if(Percent > 120)
      Percent = 120;   

   Percent = (Percent *100)/120;
   return( (UINT8)Percent );
}


