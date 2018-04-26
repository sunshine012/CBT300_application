/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Battery test definitions.
;
*******************************************************************/
#ifndef AppBattest_H
#define AppBattest_H

//#include "AppData.h"
#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#define TEST_COMPLETE_INIT               	0
#define TEST_COMPLETE_WAIT              	1
#define TEST_COMPLETE_REVIEW              	2
#define TEST_COMPLETE_END              		3
#define TEST_SELF_COMPLETE_END            	4


#define MCR400_FACTOR                   1000
#define MAX_MEASURED_CAPACITY           1500

/* number of samples for CCA measurement */
#define WARMUP_TIME             (1500 * 50)       //1.5 seconds at 5000Hz rate
#define GAIN_AJUST_TIME         (10 * 50)         //0.1 seconds at 5000Hz rate
#define GAIN_AJUST_SETTLE_TIME  (10 * 50)         //0.1 seconds at 5000Hz rate
#define CCA_RECORD_TIME             (150 * 50)        //1.5 seconds at 5000Hz rate

/* Battery Test Results */
#define NO_BATTERY_RESULTS             0xFF
#define CONDITION_GOOD                 0
#define CONDITION_GOOD_RECHARGE        1
#define CONDITION_CHARGE_RETEST        2
#define CONDITION_REPLACE              3
#define CONDITION_BADCELL              4

#define NON_MOTORCYCLE_JIS_LIST   0xFF
extern UINT16     BatCapacity2;

/* Battery test routine function prototypes */
extern void BatteryTestState(void);
extern void TestCompleteWait(void);
extern UINT16 GetCurvePercent(UINT8 *GoodPercent, UINT8 *BadPercent);
extern UINT8 BatteryConductanceTest(void);
extern UINT8 GetSOHPercent( UINT8 TestResultId, UINT8 CcaRelative, UINT16 Voltage, UINT8 AlgorithmId );

#endif
