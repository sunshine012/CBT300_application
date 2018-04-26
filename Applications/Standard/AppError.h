/*******************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     Error definitions.
;
*******************************************************************/
#ifndef APPERROR_H
#define APPERROR_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"


#define MAX_CHECK_CONN_VOLT 1650//1536    	// max. voltage for check connection routine
#define MIN_CHECK_CONN_VOLT 50      		// min. voltage for check connection routine

#define ERROR_INIT          	0
#define ERROR_WAIT          	1

// Error handling routine function prototypes
extern UINT8 CheckConnection(void);
extern void ErrorState(void);

#endif
