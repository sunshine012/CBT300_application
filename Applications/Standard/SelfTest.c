
#include "AppUtility.h"
#include "SelfTest.h"
#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DrvInt_18F67J10.h"
#include "DrvUsart_18F67J10.h"
#include "DrvKey.h"
#include "DrvLCD_OPTO1140GG.h"
#include "SysDisplay.h"
#include "DrvTimer_18F67J10.h"
#include "DrvAdc_18F67J10.h"
#include "DrvLoad.h"
#include <string.h>
#include "AppStates.h"
#include "AppData.h"
#include "SysVoltage.h"
#include "DrvPan1026.h"
#include "SysBluetooth.h"
#include "DatDictStandard.h"
#include "AppUtility.h"
//#include "SysBLE4_0.h"
#include "AppBatQuest.h"


#define SELFTEST_TEST_ENABLED

#ifdef SELFTEST_TEST_ENABLED

const far rom CHAR SelfTest_SerialBuffer1[]="UART1test";
const far rom CHAR SelfTest_SerialBuffer2[]="UART2test";

UINT8 TempBTTest[]="BT TEST";
UINT8 TempBTWait[]="PLEASE WAIT";
UINT8 TempBTTestCompleted[]="TEST COMPLETED";
UINT8 TempVOLTTest[]="VOLT TEST";
UINT8 TempLCDTest[]="LCD TEST";
UINT8 TempLCDTestResult1[]="IS THE SAMPLE?";
UINT8 TempLCDTestResult2[]="YES:SW3; NO:SW2";
UINT8 TempStateTestResult[2][5]={"PASS","FAIL"};
UINT8 TempKeyTest[]="KEY TEST";
UINT8 PressKey[3][12]={"PRESS:SW1","PRESS:SW2","PRESS:SW3"};
UINT8 TestKeyState;
const rom UINT8 TempBLETest[]="IOS BLE TEST";

void Uart_Port1_Test(void)
{
	CHAR TempBuffer[50];
	UINT8 Length;
	memcpypgm2ram( TempBuffer, SelfTest_SerialBuffer1, sizeof(SelfTest_SerialBuffer1) );
	Length = sizeof(SelfTest_SerialBuffer1);
	DrvUsartSendData(USART_PORT_1, TempBuffer, Length);

}

void Uart_Port2_Test(void)
{
	CHAR TempBuffer[50];
	UINT8 Length;
	memcpypgm2ram( TempBuffer, SelfTest_SerialBuffer2, sizeof(SelfTest_SerialBuffer2) );
	Length = sizeof(SelfTest_SerialBuffer2);
	DrvUsartSendData(USART_PORT_2, TempBuffer, Length);

}


void KeyTestState(void)
{
  	switch(TestState)
   	{
	 case KEY_TEST_INIT:
   
	CLEARSCREEN();
	DisplayString_S(TempKeyTest,2,DISPLAY_C);
	DisplayString_S(PressKey[0],3,DISPLAY_C);
	AppControlStatus(CTRL_UP|CTRL_DOWN|CTRL_ENTER);
	TestKeyState =0;
	TestState++;
	break;
 	case KEY_TEST_WAIT:
	switch(KeyPad.Keys)
       {                                    
            case ENTER_KEY:
               if(Status.Bit.KeysReleased == TRUE)
               {
               	if(TestKeyState ==2)
               	{               
                  		CLEARSCREEN();
                  		OperatingState = LCD_TEST;
                  		TestState = LCD_TEST_INIT;
               	}
               }                      
               Status.Bit.KeysReleased = FALSE;
               break;

            case DOWN_ARROW_KEY:
               if(Status.Bit.KeysReleased == TRUE) 
               {  
               	if(TestKeyState ==1)
               	{               
               		SysClear_Line_S(3);
				DisplayString_S(PressKey[2],3,DISPLAY_C);
				TestKeyState++;
               	}			
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;				
            case UP_ARROW_KEY:
               if(Status.Bit.KeysReleased == TRUE)
               {   
               	if(TestKeyState ==0)
               	{
               		SysClear_Line_S(3);
				DisplayString_S(PressKey[1],3,DISPLAY_C);
				TestKeyState++;
               	}
               }                       
               Status.Bit.KeysReleased = FALSE;
               break;
         }
	break;	
	}
}


void LcdTestState(void)
{
  	switch(TestState)
   	{
	 	case LCD_TEST_INIT:
   
			CLEARSCREEN();
			DisplayString_S(TempLCDTest,2,DISPLAY_C);
			DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);
			TestState++;
			break;
 		case LCD_TEST_WAIT:
			if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
			{
				Full_Screen();
				TestState++;
				DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);
			}
			break;
 		case LCD_TEST_CLEAN:
			if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
			{
				CLEARSCREEN();
				TestState++;
				DisplayString_S(TempLCDTest,1,DISPLAY_C);
				DisplayString_S(TempLCDTestResult1,2,DISPLAY_C);
				DisplayString_S(TempLCDTestResult2,3,DISPLAY_C);
				AppControlStatus(CTRL_DOWN|CTRL_ENTER);
			}
			break;			
		case LCD_TEST_RESULT:
			
			switch(KeyPad.Keys)
       		{                                    
            			case ENTER_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{                  				
                  				DisplayString_S(TempStateTestResult[TESTRESULT_PASS],4,DISPLAY_C);
						if(CBT300_CONFIG == ConfigData)// CBT-300 Test
						{
							DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);
							TestState++;
						}
						else // CBT-100 Test completed
						{
							TestState = LCD_TEST_CBT100_END;
						}
						AppControlStatus(CTRL_NONE);
               			}                      
               			Status.Bit.KeysReleased = FALSE;
               			break;
            			case DOWN_ARROW_KEY:
               			if(Status.Bit.KeysReleased == TRUE) 
               			{                      
						DisplayString_S(TempStateTestResult[TESTRESULT_FAIL],4,DISPLAY_C);

						if(CBT300_CONFIG == ConfigData)// CBT-300 Test
						{
							DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 1);
							TestState++;
						}
						else // CBT-100 Test completed
						{
							TestState = LCD_TEST_CBT100_END;
						}
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
 		case LCD_TEST_END:
			if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
			{
				CLEARSCREEN();
                  		OperatingState = BLUETOOTH_TEST;
                  		TestState = BT_TEST_INITIALIZE;			
			}
			break;
		case LCD_TEST_CBT100_END:

			break;
		
   	}	

}


void VoltageTestState(void)
{
	UINT8 byResult = 0;
	UINT8 * TempPtr;
	UINT16 SampleVAB;
	UINT16 SampleVCD;
	
  	switch(TestState)
   	{
	 	case VOLTAGE_TEST_INIT:
   
		CLEARSCREEN();
		DisplayString_S(TempVOLTTest,1,DISPLAY_C);
		AppControlStatus(CTRL_ENTER);
		DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 800);
		TestState++;
			break;
 		case VOLTAGE_TEST_WAIT:
		if(DrvTimer0CounterDone(TIMER0_MS_COUNTER_2))
		{
			DrvTimer0SetCounter(TIMER0_MS_COUNTER_2, 800);
    			SampleVCD=SysGetVoltage(ADC_CHANNEL_CD_VOLTS, 16);
			TempPtr=FormatVoltage(SampleVCD, tempBuffer);
			memset(DisplayBuffer,0x00,sizeof(DisplayBuffer));
			strcatpgm2ram((char *)DisplayBuffer,"CD VOLT:");
			strcat((char *)DisplayBuffer,(char *)tempBuffer);
			DisplayString_S(DisplayBuffer,2,DISPLAY_C);
		
    			SampleVAB=SysGetVoltage(ADC_CHANNEL_AB_VOLTS, 16);
			TempPtr=FormatVoltage(SampleVAB, tempBuffer);
			memset(DisplayBuffer,0x00,sizeof(DisplayBuffer));
			strcatpgm2ram((char *)DisplayBuffer,"AB VOLT:");
			strcat((char *)DisplayBuffer,(char *)tempBuffer);
			DisplayString_S(DisplayBuffer,3,DISPLAY_C);	

   			TempPtr=itoabase(Battery.CCA, DisplayBuffer,4, 10);
			strcatpgm2ram((char *)DisplayBuffer, "CCA ");	
			DisplayString_S(DisplayBuffer, 4, DISPLAY_C);
			
		}
			
			switch(KeyPad.Keys)
       		{                                    
            			case ENTER_KEY:
               			if(Status.Bit.KeysReleased == TRUE)
               			{
                  				CLEARSCREEN();
                  				OperatingState = KEY_TEST;
                  				TestState = KEY_TEST_INIT;
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
   	}	
}


void BTTestState(void)
{
  	switch(TestState)
   	{
	 	case BT_TEST_INITIALIZE:
		CLEARSCREEN();
		SysDisplayString(TempBTTest,1,DISPLAY_C);
		SysDisplayString(TempBTWait,2,DISPLAY_C);
		BTSystemConfig = OPERATE_SYSTEM_ANDROID;
		EOLTestFlg = TRUE;
		DrvPan1026Init();
		DelayXms( 10 );
	       SysInitBlueToothRadio();	
		TestState++;
			break;
			
 		case BT_TEST_WAIT:
			
		break;
	   case BT_TEST_COMPLETED:
		CLEARSCREEN();
		SysDisplayString(TempBTTest,1,DISPLAY_C);
		SysDisplayString(TempBTTestCompleted,2,DISPLAY_C);
		DrvPan1026Off();
		DelayXms( 30 );
		BTSystemConfig = OPERATE_SYSTEM_NONE;
		DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 3);//3S
		TestState++;
		break;
 	   case BT_TEST_END:
//		if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
//		{			
//            		OperatingState = BLE_TEST_STATE;
//            		TestState = BLE_TEST_INITIALIZE;
//		}			
		break;		
   	}	
}

//void BLETestState(void)
//{
//  	switch(TestState)
//   	{
//	 	case BLE_TEST_INITIALIZE:
//		BTSystemConfig = OPERATE_SYSTEM_IOS;
//		CLEARSCREEN();
//		memcpypgm2ram( tempBuffer, TempBLETest, sizeof(TempBLETest) );
//		SysDisplayString(tempBuffer,1,DISPLAY_C);
//		SysDisplayString(TempBTWait,2,DISPLAY_C);
//		EOLTestFlg = TRUE;
//		
//		DrvPan1026Init();
//		DelayXms( 10 );
//	       SysInitBLERadio();	
//		TestState++;
//			break;
//			
// 		case BLE_TEST_WAIT:
//			
//		break;
//	   case BLE_TEST_COMPLETED:
//		CLEARSCREEN();
//		memcpypgm2ram( tempBuffer, TempBLETest, sizeof(TempBLETest) );
//		SysDisplayString(tempBuffer,1,DISPLAY_C);
//		SysDisplayString(TempBTTestCompleted,2,DISPLAY_C);
//         	DrvTimer0SetCounter(TIMER0_SEC_COUNTER_1, 2);//2S 
//		TestState = BLE_TEST_CLOSE_BLE;
//		
//		break;
// 	   case BLE_TEST_CLOSE_BLE:
//		if(DrvTimer0CounterDone(TIMER0_SEC_COUNTER_1))
//		{			
//			DrvPan1026Off();
//			TestState = BLE_TEST_END;
//		}			
//		break;
// 	   case BLE_TEST_END:			
//		break;		
//   	}	
//}

#endif

