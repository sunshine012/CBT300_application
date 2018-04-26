////////////////////////////////////////////////////////////////////////////////
//
// AppMain.c
//
////////////////////////////////////////////////////////////////////////////////

//
// Required include files.
//

#include "DrvPic18f67J10.h"
#include <stdio.h>
#include <string.h>
#include "AppData.h"
#include "AppEEData.h"
#include "AppStates.h"
#include "AppStartUp.h"
#include "AppError.h"
#include "AppBatQuest.h"
#include "AppUtility.h"
#include "AppCalibrat.h"
#include "DatDictStandard.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DrvLoad.h"
#include "DrvConfigBoard.h"
#include "DrvAdc_18F67J10.h"
#include "DrvKey.h"
#include "DrvPan1026.h"
#include "DrvInt_18F67J10.h"
#include "DrvTimer_18F67J10.h"
#include "DrvUsart_18F67J10.h"
#include "DrvLCD_OPTO1140GG.h"
#include "DrvEeprom_25AA320.h"
#include "DrvSsp_18F67J10.h"
#include "SelfTest.h"
#include "SysFont6x8.h"
#include "SysDisplay.h"
#include "SysBluetooth.h"

//#include "SysBLE4_0.h"


////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

UINT8 RunApplication;


////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////
CHAR  SerialRxBuffer1[40];
CHAR  SerialRxBuffer2[160];


//#pragma udata

#define CAL_MODE       		MDX_CALMODE_IO
#define CalibrationInitial()  		(MDX_CALMODE_TRIS = TRIS_BIT_INPUT)
////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

void AppInit( void )
{
    DrvCBT300Init();
	DrvSsp1InitAsSpiMaster();
	DrvEepromInit();
    DrvLoadInit();
	DrvConfigBoardInit();
	DrvAdcInit();
	DrvKeyInit();
	DrvIntInit();
	Initial_LCD();		
   	DrvTimer0Init();
   	DrvTimer1Init();
   	DrvTimer2Init();
	CalibrationInitial();                  
   	CLRWDT(); 
   	EnableWatchDog(); 
}
//
// ProcessSerialBuffer1
//

void ProcessSerialBuffer1(CHAR* pBuffer)
{
   if(strcmppgm2ram((char*)pBuffer, "{BOOT}") == 0)
   {
        RunApplication = 2;
   }
   if((strcmppgm2ram((char*)pBuffer, "{CAL}") == 0) ||
       (strcmppgm2ram((char*)(pBuffer + 5), "CAL}") == 0))  
   {
        AppCommissionTool(TRUE);
   }
   DrvUsartReset(USART_PORT_1);       
}

//
// VariableInitialize
//
void VariableInitialize(void)				
{                                      
	EOLTestFlg = FALSE;
    DrvEepromRead((UINT16)&EEAppGlobalFlg, (UINT8*)&AppGlobalFlg, sizeof(_AppGlobalFlg));
    DrvEepromRead((UINT16)&EEAppData, (UINT8*)&AppData, sizeof(_AppData));          
   	if(AppGlobalFlg.LanguageSetFlg == TRUE)
   	{
   		OperatingState 	= POWER_UP;  
   		TestState 		= POWER_UP_INITIALIZE;
   	}
   	else
   	{
   		OperatingState 	= LANGUAGE_STATE;  			
   		TestState 		= LANGUANGE_INITIALIZE;	  
   	}
        //set things to zero
   	KeyPad.Keys 		= 0; 
   	Status.dw 		= 0;
   	ConfigData = DrvConfigBoardGet();
	DelayXms( 10 );
	ConfigData = DrvConfigBoardGet();
   	Status.Bit.KeysReleased  		= TRUE;
   	ConnectionFlag 				= FALSE;
	ConnectionCounter 			= 0;
	BTSystemConfig 	= OPERATE_SYSTEM_NONE;//OPERATE_SYSTEM_ANDROID; 
}

////////////////////////////////////////////////////////////////////////////////
//
// main functions.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef USE_BOOT_LOADER
UINT8 AppMain( UINT8 Data )
{
#else
void AppMain( void )
{
   UINT8    Data = 0xAA;
#endif

	CHAR     Char;
	CHAR*    pBuffer1;


    RunApplication = Data;
    AppInit();
	CLRWDT();
	VariableInitialize();
	if(CBT300_CONFIG == ConfigData)
	{	
		DelayXms( 10 );	
		DrvUsartInit( USART_PORT_2, USART_BAUD_RATE_115200, SerialRxBuffer2, sizeof(SerialRxBuffer2) );
        memset(SerialRxBuffer2, 0x00, sizeof(SerialRxBuffer2));
		DrvPan1026Init();
	}
	
	CLRWDT();
	CLEARSCREEN();

	DrvUsartInit( USART_PORT_1, USART_BAUD_RATE_57600, SerialRxBuffer1, sizeof(SerialRxBuffer1) ); 
    memset(SerialRxBuffer1, 0x00, sizeof(SerialRxBuffer1));
    pBuffer1 = SerialRxBuffer1;

   	if(!CAL_MODE)    
   	{                      
  		OperatingState = CALIBRATE;
  		TestState = CALIBRATE_INIT;
   	}
   	else if(VerifyCalFactors())
   	{
  		OperatingState = EEPROM_ERROR;
  		TestState = ERROR_INIT;
   	}
   	else if(CalFactor.GGain == CAL_BASE && 
           	CalFactor.ABVoltsGain == CAL_BASE && CalFactor.CDVoltsGain == CAL_BASE)
   	{
  		OperatingState = DEFAULT_CAL_ERROR;
		TestState = ERROR_INIT;
   	}

	DrvTimer0SetCounter(TIMER0_MS_COUNTER_1, 20);//20 ms
    while(RunApplication == 0xAA)
    {
        if(DrvUsartByteReady(USART_PORT_1))  //serial port 1 monitor
        {
            if(DrvUsartReadByte(USART_PORT_1, &Char))
            {
                *pBuffer1++ = Char;
                if(Char == '}')         //check for stop character
                {
                    *pBuffer1 = '\0';     //add string terminator
                    DrvUsartSendData(USART_PORT_1, SerialRxBuffer1, sizeof(SerialRxBuffer1));
                    ProcessSerialBuffer1(SerialRxBuffer1);
                    pBuffer1 = SerialRxBuffer1;
                }
                if(pBuffer1 > (SerialRxBuffer1 + sizeof(SerialRxBuffer1)))
                    pBuffer1 = SerialRxBuffer1;
            }  
        }       

			if(CBT300_CONFIG == ConfigData && BTSystemConfig != OPERATE_SYSTEM_NONE && DrvUsartByteReady(USART_PORT_2))
			{        
              if(AppCheckSerialPort(SerialRxBuffer2, (BTState >= BTReady)?BLUETOOTH_DATA_SPECIAL : BLUETOOTH_DATA_NORMAL)
                    &(USART_STATUS_BUFFER_ERROR | USART_STATUS_TIMEOUT))
              {
      				if(SysProcessBluetoothCommand(SerialRxBuffer2) == 1)
					{
                        memset(SerialRxBuffer2, 0x00, sizeof(SerialRxBuffer2));	
      				}	  
              }
			}
		
			if(DrvTimer0CounterDone(TIMER0_MS_COUNTER_1))
			{
				DrvTimer0SetCounter(TIMER0_MS_COUNTER_1, 20);//20MS
				ReadKeys();
			
         		if(BATTERY_RATING == OperatingState ||BATTERY_TYPE== OperatingState ||
                   BAT_NUMBER_STATE == OperatingState)
         		{ 
            		if(CheckConnection())
            		{
                		ConnectionFlag = TRUE;
    					ConnectionCounter ++;
    					if(30 == ConnectionCounter)//
    					{
    						ConnectionCounter = 0;
    						SysClear_Line(2);
    						AppControlStatus(CTRL_NONE);
    						SysDisplayString_W(DICT_TEXT_CHECKCONNECT,1,DISPLAY_C);
    					}
            		}
            		else if(ConnectionFlag)
            		{
                        ConnectionFlag 	= FALSE;
                        if(CBT300_CONFIG == ConfigData)
                        {		
                            OperatingState 	= BAT_NUMBER_STATE;
                            TestState 		= BATTERY_NUMBER_INITIALIZE;
                        }
                        else
                        {
                            OperatingState = BATTERY_TYPE;
                            TestState = BATTERY_TYPE_INITIALIZE;
                        }
            		}
	            }
                RunOperatingState();          //Execute current state
	        }	
            
        	CLRWDT();
    	}
#ifdef USE_BOOT_LOADER
   DisableWatchDog();                  //Disable the watchdog
   //INTCONbits.GIEH = INT_DISABLE;      //Disable all high priority interrupts &
   //INTCONbits.GIEL = INT_DISABLE;      //all low priority interrupts before returning
                                       //to bootloader.  Bootloader does not use any
                                       //interrupts.
   RunApplication = 2;
   return(RunApplication);             //return the return type of serial boot loader
#endif    
}
	
void main( void )
{
#ifdef USE_BOOT_LOADER
    AppMain(0xAA);
#else
    AppMain();
#endif
}

