/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          DrvAdc_18F87J10.h
 *
 * Designed by:   Kees Hemmes
 *
 * *****************  Version 1  *****************
 * User: Bbroer       Date: 5/29/12    Time: 6:02a
 * Created in $/MDXP600/192-000039 PCB/192-110276 Hella/Drivers
 * 
 *
 * Description:
 *
 * References:
 *
*******************************************************************************/

#ifndef _DRV_ADC_18F67J10_H_
#define _DRV_ADC_18F67J10_H_

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

////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
////////////////////////////////////////////////////////////////////////////////

//
// I/O line definitions.
//

// I/O lines.
#define ADC_VDIFF2_IO         MDX_RF1_VDIFF2_IO
#define ADC_VDIFF1_IO         MDX_VDIFF1_IO
#define ADC_IDIFF_IO              MDX_IDIFF_IO
#define ADC_VREF_NEG_IO       MDX_D_GND_IO
#define ADC_VREF_POS_IO       MDX_VREF_POS_IO
#define ADC_AB_VOLTS_IO       MDX_ABVOLTS_TRIS
#define ADC_CD_VOLTS_IO       MDX_CDVOLTS_IO           

// I/O line direction bits.
#define ADC_VDIFF2_TRIS           MDX_RF1_VDIFF2_TRIS
#define ADC_VDIFF1_TRIS           MDX_VDIFF1_TRIS
#define ADC_IDIFF_TRIS             MDX_IDIFF_TRIS
#define ADC_VREF_NEG_TRIS      MDX_D_GND_TRIS
#define ADC_VREF_POS_TRIS      MDX_VREF_POS_TRIS
#define ADC_AB_VOLTS_TRIS      MDX_ABVOLTS_TRIS
#define ADC_CD_VOLTS_TRIS      MDX_CDVOLTS_TRIS

//
// Control registers status values.
// 

// ADCAL: A/D Calibration bit.
#define ADC_CALIBRATION       1        // Calibration is performed on next A/D conversion.
#define ADC_NORMAL            0        // Normal A/D converter operation (no calibration is performed).

// CHS3:CHS0: Analog Channel Select bits.
#define ADC_CHANNEL_0         0b0000   // Channel 00 (AN0).
#define ADC_CHANNEL_1         0b0001   // Channel 01 (AN1).
#define ADC_CHANNEL_2         0b0010   // Channel 02 (AN2).
#define ADC_CHANNEL_3         0b0011   // Channel 03 (AN3).
#define ADC_CHANNEL_4         0b0100   // Channel 04 (AN4).
#define ADC_CHANNEL_5         0b0101   // Unused.
#define ADC_CHANNEL_6         0b0110   // Channel 06 (AN6).
#define ADC_CHANNEL_7         0b0111   // Channel 07 (AN7).
#define ADC_CHANNEL_8         0b1000   // Channel 08 (AN8).
#define ADC_CHANNEL_9         0b1001   // Channel 09 (AN9).
#define ADC_CHANNEL_10        0b1010   // Channel 10 (AN10).
#define ADC_CHANNEL_11        0b1011   // Channel 11 (AN11).

#define ADC_CHANNEL_VDIFF	  	ADC_CHANNEL_6 	
#define ADC_CHANNEL_IDIFF          ADC_CHANNEL_1 	
#define ADC_CHANNEL_VREF_NEG  ADC_CHANNEL_2 	
#define ADC_CHANNEL_VREF_POS	ADC_CHANNEL_3 	
#define ADC_CHANNEL_AB_VOLTS  ADC_CHANNEL_4 	
#define ADC_CHANNEL_CD_VOLTS  ADC_CHANNEL_7 	
#define ADC_CHANNEL_VDIFF1	  		ADC_CHANNEL_0 	

#define ADC_CHANNEL_CD_VOLTS_AC (0x80 | ADC_CHANNEL_CD_VOLTS) 
// GO/DONE: A/D Conversion Status bit.
#define ADC_GO                1        // A/D conversion in progress.
#define ADC_DONE              0        // A/D Idle.

// ADON: A/D On bit.
#define ADC_ENABLE            1        // A/D converter module is enabled.
#define ADC_DISABLE           0        // A/D converter module is disabled.

// VCFG1: Voltage Reference Configuration bit (VREF- source).
#define ADC_VREF_NEG_AN2      1        // VREF- (AN2).
#define ADC_VREF_NEG_AVSS     0        // AVSS.

// VCFG0: Voltage Reference Configuration bit (VREF+ source).
#define ADC_VREF_POS_AN3      1        // VREF+ (AN3).
#define ADC_VREF_POS_AVDD     0        // AVDD.

// PCFG3:PCFG0: A/D Port Configuration Control bits.
#define ADC_INPUTS_0_TO_11    0b0011   // Assigned analog inputs: AN0-AN11.
#define ADC_INPUTS_0_TO_10    0b0100   // Assigned analog inputs: AN0-AN10.
#define ADC_INPUTS_0_TO_9     0b0101   // Assigned analog inputs: AN0-AN9.
#define ADC_INPUTS_0_TO_8     0b0110   // Assigned analog inputs: AN0-AN8.
#define ADC_INPUTS_0_TO_7     0b0111   // Assigned analog inputs: AN0-AN7.
#define ADC_INPUTS_0_TO_6     0b1000   // Assigned analog inputs: AN0-AN6.
#define ADC_INPUTS_0_TO_4     0b1001   // Assigned analog inputs: AN0-AN4.
#define ADC_INPUTS_0_TO_4b    0b1010   // Assigned analog inputs: AN0-AN4.
#define ADC_INPUTS_0_TO_3     0b1011   // Assigned analog inputs: AN0-AN3.
#define ADC_INPUTS_0_TO_2     0b1100   // Assigned analog inputs: AN0-AN2.
#define ADC_INPUTS_0_TO_1     0b1101   // Assigned analog inputs: AN0-AN1.
#define ADC_INPUTS_0_TO_0     0b1110   // Assigned analog inputs: AN0.
#define ADC_INPUTS_NONE       0b1111   // No analog inputs assigned.

// ADFM: A/D Result Format Select bit.
#define ADC_RIGHT_JUSTIFY     1        // Right justified.
#define ADC_LEFT_JUSTIFY      0        // Left justified.

// ACQT2:ACQT0: A/D Acquisition Time Select bits.
#define ADC_AD_TIME_0TAD      0b000    // 0 TAD.
#define ADC_AD_TIME_2TAD      0b001    // 2 TAD.
#define ADC_AD_TIME_4TAD      0b010    // 4 TAD.
#define ADC_AD_TIME_6TAD      0b011    // 6 TAD.
#define ADC_AD_TIME_8TAD      0b100    // 8 TAD.
#define ADC_AD_TIME_12TAD     0b101    // 12 TAD.
#define ADC_AD_TIME_16TAD     0b110    // 16 TAD.
#define ADC_AD_TIME_20TAD     0b111    // 20 TAD.

// ADCS2:ADCS0: A/D Conversion Clock Select bits.
#define ADC_CLOCK_FRC         		0b111    // FRC (clock derived from A/D RC oscillator).
#define ADC_CLOCK_FOSC_64     	0b110    // FOSC/64.
#define ADC_CLOCK_FOSC_16     	0b101    // FOSC/16.
#define ADC_CLOCK_FOSC_4      	0b100    // FOSC/4.
#define ADC_CLOCK_FRC2        	0b011    // FRC (clock derived from A/D RC oscillator).
#define ADC_CLOCK_FOSC_32     	0b010    // FOSC/32.
#define ADC_CLOCK_FOSC_8      	0b001    // FOSC/8.
#define ADC_CLOCK_FOSC_2      	0b000    // FOSC/2.

//
// General ADC definitions.
//

#define  ADC_VREF				        3   // The ADC reference voltage
#define  ADC_MAX_STEP			  1023	// Maximum step of steps in the AD conversion.
#define  ADC_SCALE_FACTOR	   100000	// Factor to convert a scale value to a workable number.
#define  ADC_SCALE_DIVISOR	     1000	// Divides a scaled voltage to a 10mV value.

//
// ADC channel scale values.
//
// The calculated scales below are multiplied by ADC_SCALE_FACTOR to get a 
// workable number for calculations. Scaled voltages must be divided by 
// ADC_SCALE_DIVISOR to get a 10mV value. To get a voltage in mV from the
// ADC output use the following formula:
//
// 			Voltage (in mV) = ADCoutput * ADC_XX_SCALE / ADC_SCALE_FACTOR
//
// Vref+ / Vref-: 
// Gain		= 1                  = 1                     = 1
// Vmax  	= Vref / Gain 			= 3 / 1 				      = 3V
// Scale 	= Vmax / MaxStep 		= 3 / 1023 			      = 0.00293
//
// AB: 
// Gain		= R20 / (R16 + R20)	= 11 / (100 + 11)	      = 0.24925
// Vmax  	= Vref / Gain 			= 3 / 0.2492 				= 12.036V
// Scale 	= Vmax / MaxStep 		= 12.036 / 1023 			= 0.01177
//

// CD:
// Gain		= R21 / (R17 + R21)	= 11 / (100 + 11)	      = 0.24925
// Vmax 	   = Vref / Gain 			= 3 / 0.2492 				= 12.036V
// Scale 	= Vmax / MaxStep 		= 12.036 / 1023 			= 0.01177
//


#define  ADC_VDIFF_SCALE	        29
#define  ADC_IDIFF_SCALE	       1471
#define  ADC_VREF_NEG_SCALE	 293
#define  ADC_VREF_POS_SCALE	 293
#define  ADC_AB_SCALE		       2959//1177
#define  ADC_CD_SCALE	              2959// 1177
#define  ADC_VDIFF1_SCALE	        29

// Idiff: 
//
// The curent is measured as voltage over R40. For the measured voltage the 
// following scaling is applied:
// Gain		=  R15/ (R18 + R15)	= 2.49 /(10 + 2.49) 	= 0.19936
// Vmax  	= Vref / Gain 			= 3 / 0.19936				= 15.0481V
// Scale 	= Vmax / MaxStep 		= 15.0481V / 1023 		= 0.01471
// 
// The current is calculated as follows:
// I = VR40 / R40 = VR40 / 0.1 = 10 * VR40
//
// Vdiff: 
//
// 
// Gain 	     = 0.1*51*21= 107.1
// Vmax  	= Vref / Gain 			= 3 / 107.1  				= 0.02280V
// Scale 	= Vmax / MaxStep 		=  0.02280V / 1023 			= 0.00027

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

///////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

extern void		DrvAdcInit( void );
extern UINT16 	DrvAdcRead( UINT8 channel );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
