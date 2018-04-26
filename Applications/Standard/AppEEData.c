////////////////////////////////////////////////////////////////////////////////
//
// AppEEData.c
//
////////////////////////////////////////////////////////////////////////////////

//
// Required include files.
//

#include "AppEeData.h"
#include "AppData.h"
#include "AppBatQuest.h"
#include "AppBattest.h"



////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////

/************************************************************************/
#pragma romdata EE_RESERVED1                       //RESERVED SECTION 1
const rom UINT8 ReservedSection1[16] = {0};        //bootloader use

/************************************************************************/
#pragma romdata EECAL_FACTORS                      //CAL FACTOR SEGMENT
const rom _CalFactorStruct  EECalFactor = {
                                                10000,     //G calibration factor
                                                10000,     //channel AB calibration factor
                                                10000,     //channel CD calibration factor 
                                                    0,     //G calibration offset
                                                    0,     //channel AB calibration offset 
                                                    0,     //channel CD calibration offset 
                                                    0,     //Unit serial number
                                                   165     //calibration checksum
                                            };     //structure to hold calfactor data  


/************************************************************************/
#pragma romdata EE_GlobalFlg             // Global flags
const rom _AppGlobalFlg EEAppGlobalFlg = {
                                            FALSE,  //LanguageSetFlg
                                            FALSE,  //EOLFlg
                                            0,      // Space1
                                            0,      // Space2
                                            0       // Space3
    						            };

/************************************************************************/
#pragma romdata EE_AppData             // Global flags

const rom _AppData EEAppData = {    
                                    0,                               //BlueToothConnected
                                    LANGUANGE_CHINESE,   //Language
                                    BAT_RESULT_SEND_YES,  // Default select YES send BT data
                                    OPERATE_SYSTEM_ANDROID  //OperateSystemId
				               };

/************************************************************************/
#pragma romdata EE_AppSNum             // Global flags

const rom UINT8 EESerialNumberData[SERIALNUMBER+1]="0216300000";

/************************************************************************/
#pragma romdata EE_BatteryData                       // Battery Data
const rom _BatteryData EEBattery = {
                                        BAT_TYPE_REGULARFLOODED,       
                                        CONDITION_GOOD, //Battery result
                                           0,        //rated voltage
                                         500,        //rated CCA
                                           0,        //Volts AB
                                           0,        //Volts CD
                                           0,        //CCA
                                           0,         //Conductance
                                           0,         //Battery Counter
                                           0,            //AlgorithmId
                                           0,            //SOH
                                           0,            //SOC
                                           1             //BatJISIndex 
                                      };

/************************************************************************/
#pragma romdata EE_BoolthData
const rom _BTRemoteData EEBTRemoteData = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	  0x00, 0x00, 0x00, 0x00},
	  FALSE
};

/************************************************************************/
#pragma romdata EE_EEDATA
const rom UINT8 EESpareBlock[ 0x9F0 ] = {0x00};

/************************************************************************/
#pragma romdata EE_RESERVED2                       //RESERVED SECTION 2
const rom UINT8 ReservedSection2[16] = {0};        //application use

#pragma code

