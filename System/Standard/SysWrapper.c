/****************************************************************************
 *
 * Platform:      184-000218
 * Module:        System
 * File:          SysWrapper.c
 *
 * Designed by:   Rick Johnson
 *
 * $Workfile: SysWrapper.c $
 * $Archive: /EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS550-Tester/Sources/System/SysWrapper.c $
 * $History: SysWrapper.c $
 * 
 * *****************  Version 1  *****************
 * User: Jpeterson    Date: 8/11/15    Time: 10:34a
 * Created in $/EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS550-Tester/Sources/System
 * 
 * *****************  Version 2  *****************
 * User: Jpeterson    Date: 7/10/15    Time: 11:09a
 * Updated in $/EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS550/Sources/System
 * 
 * *****************  Version 1  *****************
 * User: Jpeterson    Date: 6/16/15    Time: 4:21p
 * Created in $/EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS550/Sources/System
 * 
 * *****************  Version 1  *****************
 * User: Jpeterson    Date: 6/12/15    Time: 10:09a
 * Created in $/EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS-550 TESTER/Sources/System
 * 
 * *****************  Version 1  *****************
 * User: Jpeterson    Date: 6/11/15    Time: 3:08p
 * Created in $/EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS-550 TESTER/Sources/System
 * 
 * Description:
 *
 *    This module defines the wrapper
 *
 * Notes:
 *
****************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>


#include "SysEEData.h"
#include "SysWrapper.h"
#include "SysBluetooth.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct _WrapperMessageStatus{
   _WrapperFrameData*   pFrameData;
   struct{
      UINT8             Spare : 7;
      UINT8             WrappedMessage : 1;
   }Flags;
}_WrapperMessageStatus;

UINT8                   WrapperErrorCode;
UINT16                  WrapperNumberCharacters;
_WrapperMessageStatus   WrapperStatus;
_WrapperFrameData*      WrapperNextMessage;

UINT8                   WrapperBufferSize;
UINT8                   WrapperBuffer[256];

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
// Function:      
// 
// Parameters:    data buffer length
//                packet id
//                serial port id
// Return Value:  Sum of bytes 1 and 2
// 
// Description:   Generates the header per the Serial protocol specification
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
//

UINT8 WriteFrameHeader(UINT16 DataLength, UINT16 PacketId, _UsartPort Port)
{
   UINT8    CkSum = 0;

                                       //set DLE character
   //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
   WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
                                       //send packet ID character and add to checksum tab
   //DrvUsartSendByte( Port, PacketId / 256 );
   WrapperBuffer[WrapperBufferSize++] = PacketId / 256;
   CkSum += (PacketId / 256);
   if((PacketId / 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
   //DrvUsartSendByte( Port, PacketId % 256);
   WrapperBuffer[WrapperBufferSize++] = PacketId % 256;
   CkSum += (PacketId % 256);
   if((PacketId % 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
                                       //send message length
   //DrvUsartSendByte( Port, DataLength / 256 );
   WrapperBuffer[WrapperBufferSize++] = DataLength / 256;
   CkSum += (DataLength / 256);
   if((DataLength / 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
   //DrvUsartSendByte( Port, DataLength % 256 );
   WrapperBuffer[WrapperBufferSize++] = DataLength % 256;
   CkSum += (DataLength % 256);
   if((DataLength % 256) == DATA_LINK_ESCAPE)
   {
      //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }
      
   return(CkSum);
}

//
// Function:      
// 
// Parameters:    pointer to data
//                data buffer length
//                current checksum
//                serial port id
// Return Value:  Sum of bytes 1 - (n-4) excluding DLE characters
// 
// Description:   adds data to buffer and computes sum of bytes
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
//

UINT8 WritePayload(UINT8* pData, UINT16 Length, UINT8 CkSum, _UsartPort Port)
{
   UINT16   i;

   for(i = 0; i < Length; i++, pData++)
   {
      //DrvUsartSendByte( Port, *pData );
      WrapperBuffer[WrapperBufferSize++] = *pData;
      CkSum += *pData;                 //compute checksum
      if (*pData == DATA_LINK_ESCAPE)
      {
         //DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
         WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
      }
   }
   return(CkSum);                      //return checksum
}

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:      
// 
// Parameters:    None
// Return Value:  None
// 
// Description:   Initializes the local XBee variables
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 01/02/12    RJ          Developed
//
void SysWrapperInit(void)
{
   WrapperNextMessage = NULL;
   WrapperStatus.Flags.WrappedMessage = FALSE;
   WrapperStatus.pFrameData = NULL;
   WrapperErrorCode = WRAPPED_MESSAGE_NO_ERROR;
   WrapperNumberCharacters = 0;
}

//
// Function:      
// 
// Parameters:    pointer to data buffer
//                data buffer length
//                packet id
//                serial port id
// Return Value:  None
// 
// Description:   Wraps passed data buffer per Serial protocol specification and send out the serial port
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
//
void SysWrapperWrapMessage(UINT8* pData, UINT16 DataLength, UINT16 PacketId, _UsartPort Port)
{
   UINT8    CkSum;
   
   //clear wrapper buffer
   memset(WrapperBuffer, 0x00, 128);
   WrapperBufferSize = 0;

   CkSum = WriteFrameHeader(DataLength, PacketId, Port);
   CkSum = WritePayload(pData, DataLength, CkSum, Port);

   CkSum = 0xFF - CkSum;
   DrvUsartSendByte( Port, CkSum );    //send checksum
   //WrapperBuffer[WrapperBufferSize++] = CkSum;
   if (CkSum == DATA_LINK_ESCAPE)
   {
      DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
      //WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   }

                                       //send DLE and ETX characters to signify end of transmission
   DrvUsartSendByte( Port, DATA_LINK_ESCAPE );
   //WrapperBuffer[WrapperBufferSize++] = DATA_LINK_ESCAPE;
   DrvUsartSendByte( Port, END_OF_TEXT );
   //WrapperBuffer[WrapperBufferSize++] = END_OF_TEXT;

   //put code here to send buffer over bluetooth
   SysBTSendData(WrapperBuffer, WrapperBufferSize);
   
}

//
// Function:      
// 
// Parameters:    pointer to data buffer
// Return Value:  pointer to frame data
// 
// Description:   Unwraps message in the SST remote protocol format.  Passed buffer
//                points to the unwrapped payload upon return.
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 10/31/12    RJ          Developed
//
_WrapperFrameData* SysWrapperUnwrapMessage(UINT8* pBuffer)
{
   UINT8    CkSum = 0;
   UINT16   i;
   UINT8*   ClearedFrame;
   UINT8*   ptr;

   WrapperErrorCode = WRAPPED_MESSAGE_NO_ERROR;
                                       //point to beginning of frame
   ptr = pBuffer;
                                       //Single DLE starts a frame
   if(*ptr == DATA_LINK_ESCAPE)
   {
      ptr++;                           //DLE detected - go to next character
      if(*ptr == DATA_LINK_ESCAPE)
      {                           //     // 2 DLE to start buffer - must be midframe
         WrapperNextMessage = NULL;
         WrapperStatus.Flags.WrappedMessage = FALSE;
         WrapperErrorCode = WRAPPED_MESSAGE_ERROR_3;
         WrapperNumberCharacters = 0;      
         WrapperStatus.pFrameData = NULL;
      }
      else                             //PID is non DLE character - packet is valid
      {
         ClearedFrame = ptr;
         WrapperStatus.pFrameData = (_WrapperFrameData*)ClearedFrame;
         WrapperStatus.pFrameData->PID = BYTE_SWAP_UINT16(WrapperStatus.pFrameData->PID);
         WrapperStatus.pFrameData->PayloadLength = BYTE_SWAP_UINT16(WrapperStatus.pFrameData->PayloadLength);
         WrapperStatus.Flags.WrappedMessage = TRUE;
                                       //Checksum includes the Packet ID, Size, and payload
      
         for(i = 0; i < (WrapperStatus.pFrameData->PayloadLength + 4); i++)
         {        
            if (*ptr == DATA_LINK_ESCAPE) 
            {
               if (*ptr++ == DATA_LINK_ESCAPE)
                  CkSum += *ptr;       //if it matches DLE, it must be followed by DLE
               else 
                  WrapperErrorCode = WRAPPED_MESSAGE_ERROR_3;
            }
            else
               CkSum += *ptr;          //compute checksum
            *ClearedFrame++ = *ptr++;
         }

         CkSum = 0xFF - CkSum;
         if(CkSum == *ptr++)           //verify checksum
         {                                
            WrapperNumberCharacters = WrapperStatus.pFrameData->PayloadLength;
         }
         else
         {                             //incorrect checksum
            WrapperErrorCode = WRAPPED_MESSAGE_ERROR_2;
            WrapperNumberCharacters = WrapperStatus.pFrameData->PayloadLength;
         }
         if(BYTE_SWAP_UINT16(*((UINT16*)ptr)) == END_OF_MESSAGE && *(ptr + 2) == DATA_LINK_ESCAPE)
            WrapperNextMessage = (_WrapperFrameData*)(ptr + 2);
         else
            WrapperNextMessage = NULL;
      }
   }
   else 
   {                                   //incorrect start of frame
      WrapperStatus.Flags.WrappedMessage = FALSE;
      WrapperErrorCode = WRAPPED_MESSAGE_ERROR_1;
      WrapperNumberCharacters = 0;      
      WrapperStatus.pFrameData = NULL;
   }
   return(WrapperStatus.pFrameData);
}

//
// Function:      
// 
// Parameters:    None
// Return Value:  wrapper message flag
// 
// Description:   Indicates if last message received was a wrapped wrapper message.
//                TRUE indicates XBee API message
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 01/02/12    RJ          Developed
//
UINT8 SysWrapperGetMessageFlag(void)
{
   UINT8 temp;

   temp = WrapperStatus.Flags.WrappedMessage;
   WrapperStatus.Flags.WrappedMessage = FALSE;
   return(temp);
}

//
// Function:      
// 
// Parameters:    None
// Return Value:  next message
// 
// Description:   
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 01/02/12    RJ          Developed
//
_WrapperFrameData* SysWrapperGetNextMessage(void)
{
   return(WrapperNextMessage);
}

//
// Function:      
// 
// Parameters:    None
// Return Value:  pointer to wrapper data buffer
// 
// Description:   Gets the wrapper data buffer address
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 10/31/12    RJ          Developed
//
_WrapperFrameData* SysWrapperGetFrameData(void)
{
   return(WrapperStatus.pFrameData);
}

//
// Function:      
// 
// Parameters:    None
// Return Value:  received Wrapper payload length
// 
// Description:   Gets the last received API message length
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 10/31/12    RJ          Developed
//
UINT16 SysWrapperGetMessageLength(void)
{
   return(WrapperNumberCharacters);
}

//
// Function:      
// 
// Parameters:    None
// Return Value:  Wrapper error code
// 
// Description:   Gets the last error code and clears the error code
//                
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 10/31/12    RJ          Developed
//
UINT8 SysWrapperGetErrorCode(void)
{
   UINT8 temp;

   temp = WrapperErrorCode;            //save error code
                                       //clear error code
   WrapperErrorCode = WRAPPED_MESSAGE_NO_ERROR;
   return(temp);                       //return last error code
}
