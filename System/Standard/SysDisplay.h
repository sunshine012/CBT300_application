/******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:          SysDisplay
 *
 * Designed by:   King Chen
 *
 *
 * Description:
 *
 * Contains all required definitions for the keys module 
 * 
 * References:
 *
 * None.
 *
*******************************************************************************/

#ifndef _SYS_DISPLAY_H_
#define _SYS_DISPLAY_H_

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

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////


#define CTRL_NONE                      0b00000000
#define CTRL_UP                        0b00000001
#define CTRL_DOWN                      0b00000010
#define CTRL_ENTER                     0b00000100
#define CTRL_BACK                      0b00001000
#define CTRL_PRINT                     0b00010000
#define CTRL_MENU                      0b00100000        
////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function protoypes.
//
////////////////////////////////////////////////////////////////////////////////

//extern const CHAR  TestShow[15];


extern void SysClear_Line(unsigned char Line);
extern void SysClear_Line_S(unsigned char Line);
extern void SysDisplayString_W(unsigned int DICTOffs, unsigned char Row, unsigned char byFlag);
extern void SysDisplayString(unsigned char *string, unsigned char row, unsigned char Mask);
extern void DisplayString_S(const unsigned char *string, unsigned char row, unsigned char Mask);
extern void AppControlStatus(unsigned char Mask);
extern void SysDisplayLogo128X8(UINT8 row,const UINT8 * DataBuffer);

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif

