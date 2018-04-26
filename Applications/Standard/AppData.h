/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          AppData.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: AppData.h $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Application/AppData.h $
 * $History: AppData.h $
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 5/29/12    Time: 6:00a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Application
 * 
 *
 * Description:
 *
 * References:
 *
*******************************************************************************/

#ifndef _APP_DATA_H_
#define _APP_DATA_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "AppCurvePN.h"
#include "DrvKey.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////
#define BTADDRESSLENGTH     6
#define BTLINKKEYLENGTH     16

#define BT_SEND_DATA_COMPLETED_NO     FALSE
#define BT_SEND_DATA_COMPLETED_YES     TRUE

typedef struct { 
   UINT16    GGain;                       //G calibration factor
   UINT16    ABVoltsGain;              //channel AB calibration factor
   UINT16    CDVoltsGain;              //channel CD calibration factor
   INT16     GOffset;                     //G calibration offset
   INT16     ABVoltsOffset;            //channel AB calibration offset
   INT16     CDVoltsOffset;            //channel CD calibration offset
   UINT8     SerialNumber;             	   //+ - flg of VCD offset
   UINT8     CheckSum;                 //calibration factor check sum
}_CalFactorStruct;

typedef struct { 
   UINT8    LanguageSetFlg: 	2;                    // LanguagSetFlg
   UINT8    EOLFlg: 			2;
   UINT8    Space1: 		    1;                      
   UINT8    Space2: 			1;
   UINT8    Space3: 			2;
}_AppGlobalFlg;

typedef struct { 
   UINT8    BlueToothConnected;                    //BlueToothConnected
   UINT8    LanguageId;
   UINT8    BTRePairId;
   UINT8    OperateSystemId;
}_AppData;

typedef struct { 
   UINT8    RemoteBDAdress[BTADDRESSLENGTH];           //Remote address
   UINT8 	  RemoteLinkKey[BTLINKKEYLENGTH];              //Remote Link-key
   UINT8	  PairFlg; 
}_BTRemoteData;

typedef struct {
   UINT8   BatteryTypeId;
   UINT8   Result;
   UINT16 RatedVoltage;                //battery rated voltage value
   UINT16 RatedCCA;                    //battery rated capactiy value
   UINT16 VoltsAB;                     //battery test channel AB voltage measurement
   UINT16 VoltsCD;                     //battery test channel CD voltage measurement
   UINT16 CCA;                         //battery test capacity measurement
   UINT16 Conductance;  
   UINT16 Counter;
   UINT8   AlgorithmId;
   UINT8   SOH;
   UINT8   SOC;
   UINT8  BatJISIndex;         //battery JIS or stock number index	 
} _BatteryData;

                                       /* Structure used for the keypad bits */
typedef struct {
   UINT8 Keys;
}_Key;

typedef union {                        //union to access the keys as a byte
   UINT8 Keys;                         //or by individual bits
   _Key Key;
}_KeyPad;

typedef struct {
   UINT8 KeysReleased         	: 1;     //no keys depressed
   UINT8 Space       			: 1;     //16ms task routines need attention
   UINT8 V2lowForCCA          	: 1;     //serial message received
   UINT8 TxProcessingRequired : 1;     //process transmit buffer
   UINT8 DisplayRipple        		: 1;     //Display ripple, frequency,max and min
   UINT8 ShowMP               	: 1;     //show multiprecision
   UINT8 Retesting            		: 1;     //Retesting Flag
   UINT8 AutoTest             		: 1;     //Auto Test flag
}_StatusBits;

typedef union {                        //union to access the status as a byte
   UINT8       dw;                     //or by individual bits
   _StatusBits Bit;
}_StatusReg;

typedef union {                        //union to access the status as a byte
	_CurveDataStruct CurveData;
   	UINT8       DataGlobalBuffer[sizeof(_CurveDataStruct)];                     //or by individual bits
}_DataGlobalBuffer;

typedef UINT8 _State;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

/* Voltage definitions */
#define _10MILLIVOLTS   1
#define _50MILLIVOLTS   5
#define _90MILLIVOLTS   9
#define _100MILLIVOLTS  10
#define _150MILLIVOLTS  15
#define _200MILLIVOLTS  20
#define _250MILLIVOLTS  25
#define _300MILLIVOLTS  30
#define _400MILLIVOLTS  40
#define _500MILLIVOLTS  50
#define _600MILLIVOLTS  60
#define _700MILLIVOLTS  70
#define _750MILLIVOLTS  75
#define _800MILLIVOLTS  80
#define _900MILLIVOLTS  90
#define _1VOLT          100
#define _1_25VOLT       125
#define _2VOLTS         (2 * _1VOLT)
#define _3VOLTS         (3 * _1VOLT)
#define _4VOLTS         (4 * _1VOLT)
#define _5VOLTS         (5 * _1VOLT)
#define _6VOLTS         (6 * _1VOLT)
#define _7VOLTS         (7 * _1VOLT)
#define _8VOLTS         (8 * _1VOLT)
#define _9VOLTS         (9 * _1VOLT)
#define _10VOLTS        (10 * _1VOLT)
#define _11VOLTS        (11 * _1VOLT)
#define _12VOLTS        (12 * _1VOLT)
#define _13VOLTS        (13 * _1VOLT)
#define _14VOLTS        (14 * _1VOLT)
#define _15VOLTS        (15 * _1VOLT)
#define _16VOLTS        (16 * _1VOLT)
#define _17VOLTS        (17 * _1VOLT)
#define _18VOLTS        (18 * _1VOLT)
#define _19VOLTS        (19 * _1VOLT)
#define _20VOLTS        (20 * _1VOLT)
#define _24VOLTS        (24 * _1VOLT)
#define _25VOLTS        (25 * _1VOLT)
#define _26VOLTS        (26 * _1VOLT)
#define _27VOLTS        (27 * _1VOLT)
#define _28VOLTS        (28 * _1VOLT)
#define _29VOLTS        (29 * _1VOLT)
#define _30VOLTS        (30 * _1VOLT)
#define _35VOLTS        (35 * _1VOLT)
#define _36VOLTS        (36 * _1VOLT)

#define LANGUANGE_CHINESE 		0
#define LANGUANGE_ENGLISH 		1

#define BT_REPAIR_NO     			 	0
#define BT_REPAIR_YES                   		1

#define BLE_RECONN_NO     			 	0
#define BLE_RECONN_YES                   		1

#define CBT300_CONFIG          0x00
#define CBT100_COMFIG          0x04

#define BLUETOOTH_DATA_NORMAL   0
#define BLUETOOTH_DATA_SPECIAL  1

#define SERIALNUMBER  10

#define BT_DEVICE_RECORDED_NUM_MAX      10

#ifndef ON
#define ON                 1
#endif

#ifndef OFF
#define OFF                0
#endif





////////////////////////////////////////////////////////////////////////////////
//
// External declerations.
//
////////////////////////////////////////////////////////////////////////////////
extern UINT8 StartBatteryTestFlg;
extern UINT8 SPPBatteryTestState;

extern _AppData AppData;
extern UINT8 ConfigData;
extern _AppGlobalFlg AppGlobalFlg;
extern _CalFactorStruct CalFactor;
extern  _BatteryData Battery;
extern _BTRemoteData BTRemoteData;
extern _DataGlobalBuffer   GlobalDataBuffer;

extern UINT8               EOLTestFlg; 
extern UINT8 			BTSystemConfig;

extern UINT8               TestState;                   //current tool test mode state
extern UINT8               OperatingState;           //current tool operating state

extern UINT8               LastKeysPressed;          //used in key debounce routine
extern UINT8               KeyDebounceCounter;       //counter used to debounce the keypad

extern _KeyPad             KeyPad;                   //debounced keypad port

extern _StatusReg          Status;                   //register status flags
extern UINT8               ConnectionFlag;
extern UINT8               ConnectionCounter;

extern unsigned char                tempBuffer[21];           //buffer to hold various strings
extern unsigned char                DisplayBuffer[21];

extern CHAR  SerialRxBuffer1[40];
extern CHAR  SerialRxBuffer2[160];

extern UINT16 BatteryTypeDICT[2];
extern UINT16 BatResultSendDICT[2];
extern UINT16 OperateSystemDICT[2];
extern UINT16 LanguageDICT[2];
//extern UINT8  BatteryTypeIndex;
extern UINT16 BatteryResultDICT[5];
extern UINT8 TempBTBuffer[128];  
extern UINT8 WrapperBuffer[128];  
extern UINT8 SerialNumberData[SERIALNUMBER+1];

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif

