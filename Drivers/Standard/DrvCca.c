/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          
 *
 * Designed by:   Kees Hemmes
 *
 * 
 *
 * Description:
 *
 * References:
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DrvAdc_18F67J10.h"
#include "DrvCca.h"
#include "DrvInt_18F67J10.h"
#include "DrvLoad.h"
#include "DrvTimer_18F67J10.h"

//#include "SysCalibrate.h"
//#include "SysSigProc.h"

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

UINT8        CcaIntCounter;
UINT16      CcaCycleCounter;
INT32      CcaVdiffHighSum;
INT32      CcaVdiffLowSum;
INT32      CcaIdiffHighSum;
INT32      CcaIdiffLowSum;
INT32      	CcaVdiff2;                   
INT32		CcaVdiff2L;
UINT16      CcaVdiffHighMax;
UINT16      CcaVdiffLowMax;
UINT16      CcaNoiseCounter;
_CcaState   CcaState;

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//   Notes:
//                                    V(IDiff)
//                                ----------
//                                 .2 * 10ohm
//      Capacity = 3.125 * ----------
//                                  V(VDiff)
//                               ----------             
//                              107.1(0.1*51*21)---  (R23/R28)*((R24+R30)/R30)*((R31+R27)/R31)
//      collect terms
//
//                                     V(IDiff)
//      Capacity = 167.34 * ----------
//                                     V(VDiff)
//
//
//                                    V(IDiff)
//                                ----------
//                                 .2 * 10ohm
//      Capacity = 3.125 * ----------
//                                  V(VDiff)
//                               ----------             
//                              5.1(0.1*51)---  (R23/R28)*((R24+R30)/R30)
//      collect terms
//
//                                     V(IDiff)
//      Capacity = 7.969 * ----------(7.96875)
//                                     V(VDiff)
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 10/15/15    KC         Developed
//

void DrvCcaIsr( void )
{
   UINT16 Sample;
   UINT8    i, Delta, Gain;
   _Bool    Slope1, Slope2;

   // Test if the start of a new cycle has been reached.
   if( CcaIntCounter == 0 )
   {
      // If so, determine if a specific action must be performed on the start
      // of a new cycle.

      // Test if the gaining has started.
      if( CcaCycleCounter == CCA_GAINING_START ) ///150
      {
         // If so, initialize the gaining process by resetting the maximum 
         // Vdiff measurement.
         CcaVdiffHighSum   = 0;
         CcaVdiffLowSum    = 0;
         CcaVdiffHighMax   = 0;
         CcaVdiffLowMax    = 0;
		  CcaVdiff2 = 0;
		  CcaVdiff2L = 0;
         CcaNoiseCounter   = 0;
         CcaState          = CCA_STATE_GAINING_BUSY;
      }
      else if( CcaCycleCounter == CCA_GAINING_END )//160
      {
         CcaState  = CCA_STATE_GAINING_READY;
      }
      // Test if the measurment phase has started.
      else if( CcaCycleCounter == CCA_MEASUREMENT_START )//170
      {
         // If so, reset all the Vdiff and Idiff measurements.
         CcaVdiffHighSum   = 0;
         CcaVdiffLowSum    = 0;
         CcaIdiffHighSum   = 0;
         CcaIdiffLowSum    = 0;
		  CcaVdiff2 = 0;
		  CcaVdiff2L = 0;				 
         CcaNoiseCounter   = 0;
         CcaState          = CCA_STATE_MEASUREMENT_BUSY;
      }
      // Test if the measurement has ended.
      else if( CcaCycleCounter == CCA_MEASUREMENT_END )//150+170
      {
         // If so, make sure the load is swithced off and disable the interrupt.
         LOAD_CONTROL_IO = LOAD_OFF;/// initral PMOST OFF
         DrvIntEnable( INT_ID_TIMER2, FALSE );

         CcaState  = CCA_STATE_MEASUREMENT_READY;
      }
   }

   if( CcaCycleCounter < CCA_MEASUREMENT_END ) {
      switch( CcaIntCounter )
      {
         case 0:  
            LOAD_CONTROL_IO = LOAD_ON;
            break;
         case  5: case  6: case 7: case 8: case 9:
         case 10: case 11: case 12: case 13: case 14:
         case 15: case 16: case 17:
            Sample             = DrvAdcRead( ADC_CHANNEL_VDIFF );
            CcaVdiffHighSum   += Sample; // counter 150 cycle
            Sample             = DrvAdcRead( ADC_CHANNEL_IDIFF );
            CcaIdiffHighSum   += Sample; // counter 150 cycle    
            Sample             = DrvAdcRead( ADC_CHANNEL_VDIFF1 );
			  CcaVdiff2 	+= Sample; // counter 150 cycle 		
            
            break;
         case 25:
            LOAD_CONTROL_IO    = LOAD_OFF;
            break;
         case 30: case 31: case 32: case 33: case 34:
         case 35: case 36: case 37: case 38: case 39:
         case 40: case 41: case 42:
            Sample             = DrvAdcRead( ADC_CHANNEL_VDIFF );
            CcaVdiffLowSum    += Sample;
            Sample             = DrvAdcRead( ADC_CHANNEL_IDIFF );
            CcaIdiffLowSum   += Sample;// it should be 0
             Sample            = DrvAdcRead( ADC_CHANNEL_VDIFF1 );
			  CcaVdiff2L 	+= Sample; // counter 150 cycle 	            
            break;
         case 43:                      // Remove system noise check
            break;
         default:
            // Do nothing
            break;   
      }
   }
   
   // Increment the int counter and test if the end of a cycle has been
   // reached.
   if( ++CcaIntCounter >= CCA_INTS_PER_CYCLE )
   {
      // If so, reset the int counter and increment the cycle counter.
      CcaIntCounter = 0;
      CcaCycleCounter++;
   }
}

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvCcaStart( void )
{
   CcaIntCounter     = 0;              //reset registers
   CcaCycleCounter   = 0;
   CcaVdiffHighSum   = 0;
   CcaVdiffLowSum    = 0;
   CcaIdiffHighSum   = 0;
   CcaIdiffLowSum    = 0;
   CcaVdiffHighMax   = 0;
   CcaVdiffLowMax    = 0;
	CcaVdiff2 = 0;
	CcaVdiff2L = 0;	 
   CcaState          = CCA_STATE_IDLE;

   //DrvGainSet(GAIN_2);                 //set initial gain
   LOAD_CONTROL_IO   = LOAD_OFF;
   IsrFunction = DrvCcaIsr;            //set the interrupt call back routine  200us timer
   DrvTimer2Init();                    //initialize timer 200us timer
   DrvIntEnable( INT_ID_TIMER2, TRUE );//enable the interrupt
}

//
// Function:      
// 
// Parameters:    None.
// Return Value:  None.
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
//

void DrvCcaStop( void )
{
   	DrvIntEnable( INT_ID_TIMER2, FALSE );
   	LOAD_CONTROL_IO = LOAD_OFF;
}

