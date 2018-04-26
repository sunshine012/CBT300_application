/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Error definitions.
;
*******************************************************************/
#ifndef APPBLUETOOTH_H
#define APPBLUETOOTH_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#define BLUETOOTH_INIT          			0
#define BLUETOOTH_STARTPAIR          		1
#define BLUETOOTH_PAIR_COMPLETE       	2
#define BLUETOOTH_REPAIR          		3
#define BLUETOOTH_SENDDATA          		4
#define BLUETOOTH_COMPLETED                	5
#define BLUETOOTH_SENDFAIL                	6
#define BLUETOOTH_PAIR_FAIL       		7
#define BLUETOOTH_END       				8

#define BLE_INIT          					0
#define BLE_INIT_WAIT          				1
#define BLE_ADVERTISE          				2
#define BLE_ADVERTISE_WAIT          		3
#define BLE_CONN_WAIT          		     	4
#define BLE_SEND_COMPLETED       		5
#define BLE_DISABLE          				6
#define BLE_END          					7


#define CBTBTVERSION          100  //1.00

typedef struct { 
   UINT8     Start1;                    //0x55
   UINT8     Start2;              	//0xAA
   UINT8     Length;              	//channel CD calibration factor
   UINT8     BTVersion;             	//G calibration offset
   UINT8     BatType;            	//channel AB calibration offset
   UINT8     BatRatingH;            	//channel CD calibration offset
   UINT8     BatRatingL;            	//channel CD calibration offset
   UINT8     MeasureVoltageH;   	//channel CD calibration offset
   UINT8     MeasureVoltageL;   	//channel CD calibration offset
   UINT8     MeasureCCAH;      	//channel CD calibration offset
   UINT8     MeasureCCAL;      	//channel CD calibration offset
   UINT8     BatReslut;            	//channel CD calibration offset
   UINT8     SerialNumber[10]; 	//Unit serial number
   UINT8     BatCounterH;         	//Unit serial number
   UINT8     BatCounterL;         	//Unit serial number
   UINT8     End1;                 	//calibration factor check sum
   UINT8     End2;                 	//calibration factor check sum
}_BTTestResultData;

//typedef struct { 
//   UINT8     Start1;                    //0x55
//   UINT8     Start2;              	//0xAA
//   UINT8     Length;              	//channel CD calibration factor
//   UINT8     BTVersion;             	//G calibration offset
//   UINT8     BatType;            	//channel AB calibration offset
//   UINT8     BatRatingH;            	//channel CD calibration offset
//   UINT8     BatRatingL;            	//channel CD calibration offset
//   UINT8     MeasureVoltageH;   	//channel CD calibration offset
//   UINT8     MeasureVoltageL;   	//channel CD calibration offset
//   UINT8     MeasureCCAH;      	//channel CD calibration offset
//   UINT8     MeasureCCAL;      	//channel CD calibration offset
//   UINT8     BatReslut;            	//channel CD calibration offset
//   UINT8     SerialNumber[6]; 	//Unit serial number
//   UINT8     BatCounterH;         	//Unit serial number
//   UINT8     BatCounterL;         	//Unit serial number
//}_BLETestResultData;

extern _BTTestResultData   BTTestResultData;
//extern _BLETestResultData  BLETestResultData;
//extern UINT8 InitialStartData[7];
//extern UINT8 BatteryStartData[7];
//extern UINT8 BatteryResultData[7];

extern UINT8 BATTERY_INITIAL_REQ[2];
extern UINT8 BATTERY_START_REQ[2];
extern UINT8 BATTERY_RESULT_REQ[2];

extern void BTSendData(void);
extern void BlueToothState(void);
//extern void BLEToothState(void);

#endif
