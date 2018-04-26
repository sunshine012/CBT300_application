/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Structure definitions.
;
*******************************************************************/
#ifndef APPCURVEPN_H
#define APPCURVEPN_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#define NUM_OF_CURVES         4

#define CURVE_FLOODED         						0
#define CURVE_AGM        									1
#define CURVE_BELOW100_MOTORCYCLE    2
#define CURVE_ABOVE100_MOTORCYCLE		3


// Battery standards.         
#define BAT_STANDARD_CCA                  0  
#define BAT_STANDARD_CA                   1
#define BAT_STANDARD_MCA                  2
#define BAT_STANDARD_JIS                  3
#define BAT_STANDARD_SAE                  4
#define BAT_STANDARD_DIN                  5
#define BAT_STANDARD_IEC                  6
#define BAT_STANDARD_EN                   7

// Structure used for Curve data
typedef struct {
   UINT8  CurveNumber;           //curve number
   UINT8  BadCellCutoffCCA;      //badcell cutoff 15CCA
   UINT16 BadCellHighVoltage;    //badcell high voltage limit
   UINT16 BadCellLowVoltage;     //badcell low voltage limit
   UINT16 RechargeVoltage;       //battery recharge voltage
   UINT16 OkToTestVoltage;       //battery ok to test voltage
   UINT16 FullChargeVoltage;     //battery full charge voltage
   UINT16 SurfaceChargeVoltage;  //battery surface charge voltage
   UINT8  AboveRechargePct;      //conductance above recharge percent
   UINT8  BelowRechargePct;      //conductance below recharge percent
   UINT8  TempCompensationPct;   //temperature compensation percent
   UINT8  CCAFactorPct[8];       //CCA factor array
   UINT8  SOCCutoffPct;          //SOC percent cutoff
   UINT8  SOCControl0;           //SOC control 0
   UINT8  SOCControl1;           //SOC control 1
   UINT8  GoodPct[96];           //pass curve array
   UINT8  BadPct[96];            //fail curve array
   UINT16 CheckSum;              //curve check sum
}_CurveDataStruct;

// Structure used for part numbers
#define FIRST_JIS_INDEX       1
#define LAST_JIS_INDEX        9
#define JIS_NUM_ARRAY_SIZE    (LAST_JIS_INDEX+1)
#define DEFAULT_JIS_INDEX     1
#define STOCK_JIS_NOT_USED    0xFFFF

typedef struct {
   const CHAR   Text[13];              //part number text string
   UINT8        RatingFactor;          //rating factor
   UINT16       RatedCapacity;         //part number battery rated capacity
   UINT8        Curve;                 //part number curve number, 5-7, 8 curves max.
   UINT8        System;                //part number battery units, 2-4, 8 systems max.
   UINT8        Voltage;               //part number rated voltage, 0-1, 4 voltages max.
   UINT8        OkToTestVoltage;       //OK to test voltage
   UINT8        CheckSum;              //checksum
}_PartNumberStruct;



extern const rom _CurveDataStruct Curve[NUM_OF_CURVES];
extern const rom _PartNumberStruct JISNumbers[JIS_NUM_ARRAY_SIZE];

#endif
