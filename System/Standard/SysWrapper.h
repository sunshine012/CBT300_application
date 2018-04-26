/*******************************************************************************
 *
 * Platform:      184-000218
 * Module:        System
 * File:          SysWrapper.h
 *
 * Designed by:   Rick Johnson
 *
 * $Workfile: SysWrapper.h $
 * $Archive: /EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS550-Tester/Sources/System/SysWrapper.h $
 * $History: SysWrapper.h $
 * 
 * *****************  Version 1  *****************
 * User: Jpeterson    Date: 8/11/15    Time: 10:34a
 * Created in $/EECS-550/347 PCB (Tester)/192-110561 Standard App/EECS550-Tester/Sources/System
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
 * References:
 *
*******************************************************************************/

#ifndef _SYS_WRAPPER_H_
#define _SYS_WRAPPER_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

//#include "DrvTypeDefs.h"
//#include "DrvUsart_MK20.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct WrapperFrameData{
   UINT16            PID;
   UINT16            PayloadLength;
   UINT8             PayloadStart;
}_WrapperFrameData;

typedef struct WrapperFrameDataTx{
   UINT8             Delimiter;
   _WrapperFrameData Data;
}_WrapperFrameDataTx;

typedef struct WrapperFrameDataRx{
   UINT8             Delimiter;
   UINT16            PacketId;
   UINT16            DataLength;
   UINT8             DataStart;
}_WrapperFrameDataRx;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
////////////////////////////////////////////////////////////////////////////////

#define DATA_LINK_ESCAPE                           0x10
#define END_OF_TEXT                                0x03
#define END_OF_MESSAGE                             0x1003

#define ACK                                        0x06
#define NAK                                        0x15

#define WRAPPED_MESSAGE_NO_ERROR                   0x00
#define WRAPPED_MESSAGE_ERROR_1                    0x01
#define WRAPPED_MESSAGE_ERROR_2                    0x02
#define WRAPPED_MESSAGE_ERROR_3                    0x03

#define BYTE_SWAP_UINT16(a) (UINT16)((((UINT16)(a)&0xFF00)>>8) | \
                                    (((UINT16)(a)&0x00FF)<<8))

#define BYTE_SWAP_UINT32(a) (UINT32)((((UINT32)(a)&0xFF000000)>>24) | \
                                     (((UINT32)(a)&0x00FF0000)>>8) | \
                                     (((UINT32)(a)&0x0000FF00)<<8) | \
                                     (((UINT32)(a)&0x000000FF)<<24))

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

////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes.
//
////////////////////////////////////////////////////////////////////////////////

void SysWrapperInit(void);
void SysWrapperWrapMessage(UINT8* pData, UINT16 DataLength, UINT16 PacketId, _UsartPort Port);
_WrapperFrameData* SysWrapperUnwrapMessage(UINT8* pBuffer);
_WrapperFrameData* SysWrapperGetFrameData(void);
UINT8 SysWrapperGetMultipleMessagesFlag(void);
UINT8 SysWrapperGetMessageFlag(void);
_WrapperFrameData* SysWrapperGetNextMessage(void);
UINT8* SysWrapperGetBuffer(void);
UINT16 SysWrapperGetMessageLength(void);
UINT8 SysWrapperGetErrorCode(void);
//UINT8 SysWrapperWriteFrameHeader(UINT16 DataLength, UINT16 PacketId, _UsartPort Port);
//UINT8 SysWrapperWritePayload(UINT8* pData, UINT16 Length, UINT8 CkSum, _UsartPort Port);

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
