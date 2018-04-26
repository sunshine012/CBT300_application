/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Utility definitions.
;
*******************************************************************/
#ifndef AppUtility_H
#define AppUtility_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

//#define AB_SCALE            1645        // max. voltage for channel AB is 16.45volts   4.098/(332K/(1M+332K))=16.45V
//#define CD_SCALE            1645        // max. voltage for channel CD is 16.45volts  4.098/(332K/(1M+332K))=16.45V

#define CAL_BASE            10000       // calibration factor base
#define AD_MAX               1023        // A/D maximum counts

// Utility routine function prototypes
extern UINT8 VerifyCalFactors (void);
extern CHAR* itoabase(UINT16 number, CHAR *string, UINT8 JustifySize, UINT8 Base);
extern CHAR* FormatVoltage(UINT16 Value, CHAR* string);
extern void RightJustify(CHAR* string, UINT8 size);
extern UINT8 CalFactorsCheckSum(void);

#endif
