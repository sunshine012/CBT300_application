/*******************************************************************************
 *
 * Platform:      184-000385
 * Module:        System
 * File:          SysVoltage.c
 *
 * Designed by:   King Chen
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
#include "SysVoltage.h"
#include "AppData.h"

////////////////////////////////////////////////////////////////////////////////
//
// Functions prototypes.
//
////////////////////////////////////////////////////////////////////////////////

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

//
//
//

////////////////////////////////////////////////////////////////////////////////
//
// Gobal functions.
//
////////////////////////////////////////////////////////////////////////////////

//
//
//

/////////////////////////////////////////////////////////////////////////////////////
//
//  Routine scales the passed A/D reading value(s) into voltage.
//
//  Parameters: A/D channel, number of A/D readings, sum of A/D readings   
//  Return Value: Scaled channel voltage
// 
//  Revision History:
//  Date        Initials    Reason
//  ========    ========    ======
//  11/08/07    RJ          Developed
//  06/24/08    RJ          Added check for negative numbers.  Any number less than
//                          is forced to zero
//
UINT16 SysScaleVoltage(UINT32 AtoDReadings, UINT16 NumSamples, UINT8 channel)
{
   UINT16   ChannelScale;
   UINT16   ChannelGain;
   INT16    ChannelOffset;
          
   switch(channel)                     //load channel parameters
   {
      case ADC_CHANNEL_VDIFF:
         ChannelScale = ADC_VDIFF_SCALE;
         ChannelGain = 10000;
         ChannelOffset = 0;
         break;

      case ADC_CHANNEL_IDIFF:
         ChannelScale = ADC_IDIFF_SCALE;
         ChannelGain = 10000;
         ChannelOffset = 0;
         break;

      case ADC_CHANNEL_AB_VOLTS:
         ChannelScale = ADC_AB_SCALE;
         ChannelGain = CalFactor.ABVoltsGain;
         ChannelOffset = CalFactor.ABVoltsOffset;
         break;
         
      case ADC_CHANNEL_CD_VOLTS:
         ChannelScale = ADC_CD_SCALE;
         ChannelGain = CalFactor.CDVoltsGain;
         ChannelOffset = CalFactor.CDVoltsOffset;
         break;
         
      case ADC_CHANNEL_CD_VOLTS_AC:
         ChannelScale = ADC_CD_SCALE;
         ChannelGain = CalFactor.CDVoltsGain;
         ChannelOffset = 0;
         break;
         
      default:
         ChannelScale = 0;
         ChannelGain = 10000;
         ChannelOffset = 0;
   }   
                                       //scale per channel
   AtoDReadings *= (UINT32)ChannelScale; 
   AtoDReadings /= ((UINT32)NumSamples * ADC_SCALE_DIVISOR);
   AtoDReadings *= (UINT32)ChannelGain;
   AtoDReadings /= (UINT32)10000;
   AtoDReadings += (INT32)ChannelOffset;

   if((INT32)AtoDReadings < 0)         //limit to positive value
      AtoDReadings = 0;

   return((UINT16)AtoDReadings);       //return the scaled voltage channel
}

/////////////////////////////////////////////////////////////////////////////////////
//
//  Routine reads the passed A/D channel the number of times passed and then scales
//  the channel into a voltage.
//
//  Parameters: A/D channel, number of A/D readings
//  Return Value: Scaled channel voltage
// 
//  Revision History:
//  Date        Initials    Reason
//  ========    ========    ======
//  11/08/07    RJ          Developed
//
UINT16 SysGetVoltage(UINT8 channel, UINT16 NumSamples)
{
   UINT16   i;
   UINT32   sum = 0;
          
   for(i = 0; i < NumSamples; i++)
      sum += DrvAdcRead(channel);      //running sum of channel A/D values
                                       //scale readings into voltage
   return(SysScaleVoltage(sum, NumSamples, channel));
}
