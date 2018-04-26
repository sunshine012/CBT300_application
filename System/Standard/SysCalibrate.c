/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        System
 * File:          SysCalibrate.c
 *
 * Designed by:   Rick Johnson
 *
 * $Workfile: SysCalibrate.c $
 * $Archive: /MDXP600/192-000039 PCB/192-110598 MDX-658P CY/System/Standard/SysCalibrate.c $
 * $History: SysCalibrate.c $
 * 
 * *****************  Version 1  *****************
 * User: Akallas      Date: 2/17/16    Time: 4:55p
 * Created in $/MDXP600/192-000039 PCB/192-110598 MDX-658P CY/System/Standard
 * 
 * *****************  Version 2  *****************
 * User: Bpierce      Date: 5/24/12    Time: 9:35a
 * Updated in $/MDXP600/192-000039 PCB/192-110188 MDX-650 CY/System/Standard
 * 
 * *****************  Version 1  *****************
 * User: Bpierce      Date: 5/18/12    Time: 9:13a
 * Created in $/MDXP600/192-000039 PCB/192-110340 MDX-650 CY/System/Standard
 * 
 * *****************  Version 1  *****************
 * User: Lgiron       Date: 4/30/10    Time: 8:32a
 * Created in $/MDXP600/192-000039 PCB/192-110188 MDX-650 CY/System/Standard
 * 
 * *****************  Version 3  *****************
 * User: Rick         Date: 4/02/08    Time: 8:04a
 * Updated in $/MDXP600/192-000039 PCB/Master/System/Standard
 * 
 * *****************  Version 2  *****************
 * User: Rick         Date: 2/29/08    Time: 4:42p
 * Updated in $/MDXP600/192-000039 PCB/Master/System/Standard
 * File comment format change for Source Safe
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


#include <string.h>


#include "DrvEeprom_25AA320.h"
#include "DrvUsart_18F67J10.h"
#include "DrvTimer_18F67J10.h"

#include "SysCalibrate.h"

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

#pragma code

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

/****************************************************************************

   This function verifies the word sized checksum, ie. 16bit checksum
   If check sum is incorrect the routine returns -1. If the checksum is 
   correct the routine returns 0.

   Parameters Passed:   pointer to Array, size of array
   Parameters Returned: 0 checksum valid, -1 checksum invalid

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-08-07    RJ          Developed

****************************************************************************/
INT16 SysVerifyByteChecksum(const void* Array, UINT8 size)
{
   UINT8 i = 0;
   UINT8 sum = 0;
   
   size--;                             //back up over checksum
   while(i < size)
   {
      sum += *((UINT8*)Array + i);     //add up the bytes
      i++;                             //check if the sum matches the stored sum
   }                                   //return 0 if sums match otherwise
                                       //return -1 if sums are different
   return((sum == *((UINT8*)Array + i)) ? 0 : -1);
}

/****************************************************************************

   This function returns the tester serial number.

   Parameters Passed:   None
   Parameters Returned: Serial number

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   02-01-08    RJ          Developed

****************************************************************************/
/*UINT32 SysGetSerialNumber(void)
{
   DrvEepromRead((UINT16)&EECalFactors.SerialNumber, (UINT8*)&CalFactor.SerialNumber, sizeof(CalFactor.SerialNumber));
   return(CalFactor.SerialNumber);
}*/

/****************************************************************************

   This function load the calibration factor structure from EE prom to ram
   and verifies the checksum is correct.

   Parameters Passed:   None
   Parameters Returned: TRUE if checksum is correct
                        FALSE if checksum is incorrect

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   02-01-08    RJ          Developed

****************************************************************************/
/*_Bool SysLoadCalFactors(void)
{
   DrvEepromRead((UINT16)&EECalFactor, (UINT8*)&CalFactor, sizeof(_CalFactorStruct));
   if(SysVerifyByteChecksum((const void*)&CalFactor, sizeof(_CalFactorStruct)) != 0)
      return(FALSE);
   else
      return(TRUE);
}*/

/****************************************************************************

   This function reads the memory and sends the data to the host.  The base
   address and the number of bytes to read have already been set.

   Parameters Passed:   Start Address and number of bytes to read
   Parameters Returned: Current memory Address

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed
   02-28-08    RJ          Modified to return address so Mapple would function
                           properly

****************************************************************************/
UINT32 SysMemoryUpLoad(UINT32 Address, UINT32 NumberOfBytes)
{
   UINT32   i;
   CHAR     Data[2];

   for(i = 0; i < (NumberOfBytes/2); i++)
   {                                   //read memory location
      //DrvEepromRead(Address++, &Data, 1);
                                       //send data
      //DrvUsartSendByte( USART_PORT_1, Data );
      DrvEepromRead(Address, Data, 2);
      Address += 2;
      DrvUsartSendData( USART_PORT_1, Data, 2);
   }
   if(NumberOfBytes % 2)    // one byte residue
   {
       DrvEepromRead(Address++, Data, 1);
       DrvUsartSendByte( USART_PORT_1, Data[0]);
   }
   return(Address);
}

/****************************************************************************

   This function writes the memory with the data sent from the host.  The base
   address and the number of bytes to read have already been set.

   Parameters Passed:   Start Address and number of bytes to write
   Parameters Returned: Current memory Address

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
UINT32 SysMemoryDownLoad(UINT32 Address, UINT32 NumberOfBytes)
{
   UINT16   i;
   UINT8    Data[EE_PAGE_SIZE];

   memset(Data, 0xFF, EE_PAGE_SIZE);
   for(i = 0; i < NumberOfBytes; i++)
   {                                   
      while(DrvUsartByteReady( USART_PORT_1) == FALSE)
         ;                             //wait until byte ready
                                       //read data
      DrvUsartReadByte( USART_PORT_1, &Data[i] );
   }
                                       //write the data to memory
   DrvEepromWrite(Address, Data, NumberOfBytes);
   Address += NumberOfBytes;           //auto increment the address
   return(Address);
}

/****************************************************************************

   This function writes the memory with the data sent from the host.  The base
   address and the number of bytes to read have already been set.

   Parameters Passed:   Start Address and number of bytes to write
   Parameters Returned: Current memory Address

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
/*UINT32 SysFlashMemoryDownLoad(UINT32 Address, UINT32 NumberOfBytes)
{
   UINT32   i;
   UINT8    Data[EE_PAGE_SIZE];

   memset(Data, 0xFF, EE_PAGE_SIZE);
   for(i = 0; i < NumberOfBytes; i++)
   {                                   
      while(DrvUsartByteReady( USART_PORT_1) == FALSE)
         ;                             //wait until byte ready
                                       //read data
      DrvUsartReadByte( USART_PORT_1, &Data[i] );
   }
   DrvFlashPageWrite( Address, Data, NumberOfBytes );
   Address += NumberOfBytes;           //auto increment the address
   return(Address);
}*/

/****************************************************************************

   This function reads the memory and sends the data to the host.  The base
   address and the number of bytes to read have already been set.

   Parameters Passed:   Start Address and number of bytes to read
   Parameters Returned: Current memory Address

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed
   02-28-08    RJ          Modified to return address so Mapple would function
                           properly

****************************************************************************/
/*UINT32 SysFlashMemoryUpLoad(UINT32 Address, UINT32 NumberOfBytes)
{
   UINT32   i;
   UINT8    data;

   for(i = 0; i < NumberOfBytes; i++)
   {                                   //read memory location and
                                       //increment address
      DrvFlashRead( Address++, &data, sizeof(data) );
                                       //send data
      DrvUsartSendByte( USART_PORT_1, data );
   }
   return(Address);
}*/

/****************************************************************************

   This function writes the memory with the data sent from the host.  The base
   address and the number of bytes to read have already been set.

   Parameters Passed:   Start Address and number of bytes to write
   Parameters Returned: Current memory Address

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
/*UINT32 SysRTCMemoryDownLoad(UINT32 Address, UINT32 NumberOfBytes)
{
   UINT16         i;
   _DateTime      DateTime;
   UINT8          buffer[8];

   for(i = 0; i < NumberOfBytes; i++)
   {                                   
      while(DrvUsartByteReady( USART_PORT_1) == FALSE)
         ;                             //wait until byte ready
                                       //read data
      DrvUsartReadByte( USART_PORT_1, &buffer[i] );
   }
   i = 0;
   DateTime.Seconds = buffer[i++];     //seconds
   DateTime.Minutes = buffer[i++];     //minutes
   DateTime.Hours = buffer[i++];       //hours
   DateTime.Day = buffer[i++];         //day
   DateTime.Date = buffer[i++];        //date
   DateTime.Month = buffer[i++];       //month
   DateTime.Year = buffer[i] + 2000;   //year offset by 2000    
                                       
   DrvRtcSetDateTime( &DateTime );     //write the data to RTC memory
                                       
   Address += NumberOfBytes;           //auto increment the address
   return(Address);
}*/

/****************************************************************************

   This function reads the memory and sends the data to the host.  The base
   address and the number of bytes to read have already been set.

   Parameters Passed:   number of bytes to read
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
/*void SysRTCMemoryUpLoad(UINT32 NumberOfBytes)
{
   UINT16         i = 0;
   _DateTime      DateTime;
   UINT8          buffer[8];

   DrvRtcGetDateTime( &DateTime );     //read date and time

   buffer[i++] = DateTime.Seconds;     //seconds
   buffer[i++] = DateTime.Minutes;     //minutes
   buffer[i++] = DateTime.Hours;       //hours
   buffer[i++] = DateTime.Day;         //day
   buffer[i++] = DateTime.Date;        //date
   buffer[i++] = DateTime.Month;       //month
   buffer[i] = DateTime.Year - 2000;   //year offset by 2000

   for(i = 0; i < NumberOfBytes; i++)
   {                                   //send memory location
      DrvUsartSendByte( USART_PORT_1, buffer[i] );
   }
}*/

/****************************************************************************

   This function sends the "OK" acknowledgement.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
void SysSendOk(void)
{                                      //send OK
   DrvUsartSendByte(USART_PORT_1, 'O');
   DrvUsartSendByte(USART_PORT_1, 'K');
}

/****************************************************************************

   This function sends the tool ID number

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
/*void SysSendToolID(void)
{
   DrvUsartSendByte(USART_PORT_1, MDX_ID);
}*/

/****************************************************************************

   This function sends the error acknowledgement, "--" and then waits .5seconds
   before re-initializing.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
void SysCommandError(void)
{
   DrvUsartSendByte(USART_PORT_1, '-');
   DrvUsartSendByte(USART_PORT_1, '-');
   DrvTimer0SetCounter( TIMER0_SEC_COUNTER_1, 1 );
   while(Timer0SecCounter1)
   {                                   //wait delay time
      CLRWDT();                        //reset the internal software watchdog
   }
}

/****************************************************************************

   This function sends the product calibration structure out the serial port.

   Parameters Passed:   None
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   11-03-07    RJ          Developed

****************************************************************************/
/*void SysSendSerialNumber(void)
{
   SysLoadCalFactors();                //load cal factor structure from EE prom
                                       //transmit the structure
   DrvUsartSendData(USART_PORT_1, (UINT8*)&CalFactor, sizeof(_CalFactorStruct));
}*/


