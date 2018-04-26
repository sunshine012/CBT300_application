/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvCca.h
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: DrvCca.h $
 * $Archive: /MDXP600/192-000039 PCB/192-110276 Hella/Drivers/DrvCca.h $
 * $History: DrvCca.h $
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 5/29/12    Time: 6:02a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 10/03/11   Time: 4:14a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Abremen      Date: 4/19/11    Time: 8:38a
 * Created in $/MDXP600/192-000039 PCB/192-110240 MDX-645P_YUASA/Drivers
 * 
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 1-12-10    Time: 18:25
 * Created in $/MDXP600/192-000039 PCB/192-110223 MDX-645P KRAMP/Drivers/Standard
 * Added driver files from the master
 * 
 * *****************  Version 3  *****************
 * User: Rick         Date: 4/02/08    Time: 8:04a
 * Updated in $/MDXP600/192-000039 PCB/Master/Drivers/Standard
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 2/29/08    Time: 4:42p
 * Updated in $/MDXP600/192-000039 PCB/Master/Drivers/Standard
 * File comment format for Source Safe
 * 
 * *****************  Version 1  *****************
 * User: Rick         Date: 2/26/08    Time: 8:03a
 * Created in $/MDXP600/192-000039 PCB/Master/Drivers
 *
 * Description:
 *
 * References:
 *
*******************************************************************************/

#ifndef _DRV_CCA_H_
#define _DRV_CCA_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

typedef enum {
   CCA_STATE_IDLE                = 0,
   CCA_STATE_WARMINGUP_BUSY      = 1,
   CCA_STATE_WARMINGUP_READY     = 2,
   CCA_STATE_GAINING_BUSY        = 3,
   CCA_STATE_GAINING_READY       = 4,
   CCA_STATE_SETTLING_BUSY       = 5,
   CCA_STATE_SETTLING_READY      = 6,
   CCA_STATE_MEASUREMENT_BUSY    = 7,
   CCA_STATE_MEASUREMENT_READY   = 8
} _CcaState, *_CcaStatePtr;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
////////////////////////////////////////////////////////////////////////////////

// Cycle counter definitions.
#define CCA_START                0
#define CCA_WARMUP_START         CCA_START   //  0
#define CCA_WARMUP_LENGTH        150
#define CCA_WARMUP_END           (CCA_START + CCA_WARMUP_LENGTH )// 150+0
#define CCA_GAINING_START        CCA_WARMUP_END   //150
#define CCA_GAINING_LENGTH       10
#define CCA_GAINING_END          (CCA_GAINING_START + CCA_GAINING_LENGTH)//160
#define CCA_SETTLE_START         CCA_GAINING_END   //160
#define CCA_SETTLE_LENGTH        10
#define CCA_SETTLE_END           (CCA_SETTLE_START + CCA_SETTLE_LENGTH)//170
#define CCA_MEASUREMENT_START    CCA_SETTLE_END  //170
#define CCA_MEASUREMENT_LENGTH   150
#define CCA_MEASUREMENT_END      (CCA_MEASUREMENT_START + CCA_MEASUREMENT_LENGTH)//170+150=320

// General definitions.
#define CCA_INTS_PER_CYCLE   50

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////

extern UINT8      CcaIntCounter;
extern UINT16     CcaCycleCounter;
extern INT32     CcaVdiffHighSum;
extern INT32     CcaVdiffLowSum;
extern INT32     CcaIdiffHighSum;
extern INT32     CcaIdiffLowSum;
extern INT32      CcaVdiff2;                   
extern INT32	  CcaVdiff2L;
extern UINT16     CcaVdiffHighMax;
extern UINT16     CcaVdiffLowMax;
extern _CcaState  CcaState;

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

extern void	DrvCcaStart( void );
extern void     DrvCcaStop( void );
extern void     DrvCcaIsr( void );
//UINT16   DrvGetCcaNoiseCounter(void);
//void     DrvSetCcaNoiseCounter(UINT16 NoiseValue);

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
