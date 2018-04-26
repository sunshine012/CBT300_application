/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Calibration definitions.
;
*******************************************************************/
#ifndef APPcalibrat_H
#define APPcalibrat_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

typedef struct CalDataStruct{
    UINT8       Command;
    UINT8       Argument;
    UINT32      Address;
    UINT32      NumberOfBytes;
    UINT16		IntData;
    UINT32		LongData;
}_CalDataStruct;


//Test States
#define CALIBRATE_INIT           0
#define CALIBRATE_QUEST          1
#define CALIBRATE_VOLTS          2
#define CALIBRATE_CCA            3
#define CALIBRATE_APPLY                   		(BATTERY_TEST_DONE+1)
#define CALIBRATE_CHECK_VOLTAGES 		(CALIBRATE_APPLY+1)
#define CALIBRATE_CHECK_CCA_WAIT 		(CALIBRATE_APPLY+2)
#define CALIBRATE_CHECK_CCA_INIT 		(CALIBRATE_APPLY+3)
#define CALIBRATE_CHECK_CCA      		(CALIBRATE_APPLY+4)
#define CALIBRATE_CHECK_SCALE    		(CALIBRATE_APPLY+5)
#define CALIBRATE_CHECK_CCA_DONE 		(CALIBRATE_APPLY+6)
#define CALIBRATE_FAILED         			(CALIBRATE_APPLY+7)
#define CALIBRATE_COMPLETED         		(CALIBRATE_APPLY+8)
#define CALIBRATE_END         				(CALIBRATE_APPLY+9)


// Test state definitions
#define BATTERY_TEST_INITIALIZE         	(CALIBRATE_CCA)
#define BATTERY_TEST_CCA_INIT           	(BATTERY_TEST_INITIALIZE+1)
#define BATTERY_TEST_CCA                	(BATTERY_TEST_INITIALIZE+2)
#define BATTERY_TEST_SCALE              	(BATTERY_TEST_INITIALIZE+3)
#define BATTERY_TEST_DONE               	(BATTERY_TEST_INITIALIZE+4)
#define BATTERY_TEST_NOISE_WAIT         	(BATTERY_TEST_INITIALIZE+5) 

#define  CALIBRATION_INITIALIZE     0
#define  CALIBRATION_WAIT_COMMAND   (CALIBRATION_INITIALIZE+1)

#define  CAL_UPDATE_COMPLETE        0
#define  CAL_READ_VOLTAGE           (CAL_UPDATE_COMPLETE+1)
#define  CAL_READ_CAPACITY          (CAL_UPDATE_COMPLETE+2)
#define  CAL_BASE_ADDRESS           (CAL_UPDATE_COMPLETE+3)
#define  CAL_NUM_BYTES              (CAL_UPDATE_COMPLETE+4)
#define  CAL_MEMORY_UPLOAD          (CAL_UPDATE_COMPLETE+5)
#define  CAL_MEMORY_DOWNLOAD        (CAL_UPDATE_COMPLETE+6)
#define  CAL_FLASH_UPLOAD           (CAL_UPDATE_COMPLETE+7)
#define  CAL_FLASH_DOWNLOAD         (CAL_UPDATE_COMPLETE+8)
#define  CAL_FLASH_ERASE_SECTOR     (CAL_UPDATE_COMPLETE+9)
#define  CAL_SEND_FIRMWARE          (CAL_UPDATE_COMPLETE+10)
#define  CAL_SEND_SERIAL_NUMBER     (CAL_UPDATE_COMPLETE+11)
#define  CAL_SEND_RTC_DATA          (CAL_UPDATE_COMPLETE+12)
#define  CAL_SET_RTC_DATA           (CAL_UPDATE_COMPLETE+13)
#define  CAL_WATCHDOG               (CAL_UPDATE_COMPLETE+14)
#define  CAL_SEND_POD_EE_DATA       (CAL_UPDATE_COMPLETE+15)
#define  CAL_TOOL_ID                (CAL_UPDATE_COMPLETE+16)
#define  CAL_UNKNOWN                (CAL_UPDATE_COMPLETE+17)
#define  CAL_READ_OHMS              (CAL_UPDATE_COMPLETE+18)
#define  NUMBER_OF_COMMANDS         (CAL_READ_OHMS-CAL_UPDATE_COMPLETE)


#define CAL_RELAY0    MDX_TX1_RELAY0_IO           
#define CAL_RELAY1    MDX_RX1_RELAY1_IO

//Function prototypes
extern void CalState(void);
extern void AppCommissionTool(_Bool MessageDisplay);

#endif
