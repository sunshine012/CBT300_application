/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Operating state definitions.
;
*******************************************************************/
#ifndef AppStartUp_H
#define AppStartUp_H


#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"


// Test state definitions
#define POWER_UP_INITIALIZE             0
#define POWER_UP_WAIT                      1
#define POWER_UP_END                        2


#define LANGUANGE_INITIALIZE       	0
#define LANGUANGE_QUESTION       	1

#define SERIALNO_INITIALIZE       		0
#define SERIALNO_QUESTION       		1
#define SERIALNO_COMPLETED       	2
#define SERIALNO_END       			3

extern const CHAR  CBT100TesteName[];
extern const CHAR  CBT300TesteName[];
extern const CHAR  Version[];

extern void PowerUpState(void);
extern void LanguageState(void);
extern void SerialNoInputState(void);
extern void AppControlIputInit(const UINT16 TitleOffset);
extern void DisplayControlString(const CHAR *String, unsigned char StringLength, unsigned char row, unsigned char Mask);

#endif
