/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        Drivers
 * File:          SysCalibrate.h
 *
 * Designed by:   Rick Johnson
 *
 * $Workfile: SysCalibrate.h $
 * $Archive: /MDXP600/192-000039 PCB/192-110598 MDX-658P CY/System/Standard/SysCalibrate.h $
 * $History: SysCalibrate.h $
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
 * Contains all required definitions for the calibrate module 
 * 
 * References:
 *
 * None.
 *
*******************************************************************************/

#ifndef _SYS_CALIBRAT_H_
#define _SYS_CALIBRAT_H_

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
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

#define MDX_ID                      10
#define EE_PAGE_SIZE                64

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// External declerations.
//
////////////////////////////////////////////////////////////////////////////////
		  			  


////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

INT16 SysVerifyByteChecksum(const void* Array, UINT8 size);
//UINT32 SysGetSerialNumber(void);
//_Bool SysLoadCalFactors(void);
UINT32 SysMemoryUpLoad(UINT32 Address, UINT32 NumberOfBytes);
UINT32 SysMemoryDownLoad(UINT32 Address, UINT32 NumberOfBytes);
//UINT32 SysFlashMemoryDownLoad(UINT32 Address, UINT32 NumberOfBytes);
//UINT32 SysFlashMemoryUpLoad(UINT32 Address, UINT32 NumberOfBytes);
//UINT32 SysRTCMemoryDownLoad(UINT32 Address, UINT32 NumberOfBytes);
//void SysRTCMemoryUpLoad(UINT32 NumberOfBytes);
void SysSendOk(void);
//void SysSendToolID(void);
void SysCommandError(void);
//void SysSendSerialNumber(void);

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////


#endif
