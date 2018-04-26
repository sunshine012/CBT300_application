	/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          
 *
 * Designed by:   Kees Hemmes
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

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DrvAdc_18F67J10.h"

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
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 07/08/01    CHE         Developed
// 12/12/07    RJ          Changed the ADCS for 32MHz clock
//

void DrvAdcInit( void ) 
{
   ADC_VDIFF1_TRIS    	= TRIS_BIT_INPUT;
   ADC_IDIFF_TRIS    	= TRIS_BIT_INPUT;
   ADC_VDIFF2_TRIS    	= TRIS_BIT_INPUT;
   ADC_VREF_NEG_TRIS = TRIS_BIT_INPUT;
   ADC_VREF_POS_TRIS = TRIS_BIT_INPUT;
   ADC_AB_VOLTS_TRIS = TRIS_BIT_INPUT;
   ADC_CD_VOLTS_TRIS = TRIS_BIT_INPUT;

   ADCON0bits.ADON   = ADC_DISABLE;

   ADCON0bits.GO     = ADC_DONE;
   ADCON0bits.CHS    = ADC_CHANNEL_0;
   ADCON0bits.ADCAL  = ADC_NORMAL;

   ADCON1bits.PCFG   = ADC_INPUTS_0_TO_8;
   ADCON1bits.VCFG0  = ADC_VREF_POS_AN3;
   ADCON1bits.VCFG1  = ADC_VREF_NEG_AN2;

   ADCON2bits.ADCS   = ADC_CLOCK_FOSC_32;
   ADCON2bits.ACQT   = ADC_AD_TIME_2TAD;
   ADCON2bits.ADFM   = ADC_RIGHT_JUSTIFY;

   ADCON0bits.ADON   = ADC_ENABLE;

   // Setup ADC for auto caibration and start dummy conversion.
   ADCON0bits.ADCAL  	= ADC_CALIBRATION;
   ADCON0bits.GO     	= ADC_GO ;
   
   // Wait until dummy conversion is completed.
   while( ADCON0bits.GO != ADC_DONE );

   //Note FOSC/8 does not work at all        
   ADCON2bits.ADCS   = ADC_CLOCK_FRC2;
   ADCON2bits.ADCS   = ADC_CLOCK_FOSC_32;
   //End of work around for A/D errata
   // Return to normal operation mode.
   ADCON0bits.ADCAL  = ADC_NORMAL;
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
// 12/12/07    RJ          Added work around for A/D
//

UINT16 DrvAdcRead( UINT8 Channel )
{        
   // Setup channel and start conversion.
   ADCON0bits.CHS   = Channel;
   ADCON0bits.GO    = ADC_GO ;
   
   // Wait until conversion is completed.
   while( ADCON0bits.GO != ADC_DONE ); 

   //Work around for A/D errata for FOSC/16, FOSC/32 & FOSC/64
   //Note FOSC/8 does not work at all        
   ADCON2bits.ADCS   = ADC_CLOCK_FRC2;
   ADCON2bits.ADCS   = ADC_CLOCK_FOSC_32;
   //End of work around for A/D errata

   // Return conversion result.
   return( ADRES );
}

