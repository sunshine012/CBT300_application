////////////////////////////////////////////////////////////////////////////////
//
// File                     : Font6X16.h
// Font                     : Font6X16
// Format                   : Standard horizontal
// Created on               : 2007-11-12 14:39:17
//         with             : Fcg50
//         version          : 0.0.5.0
//         by               : khemmes
//
// Note:                                                               
// This file is generated automatically. Do not make manual changes to 
// this file. These changes will be lost the next time this file is    
// generated.                                                          
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DAT_FONT6X16_H_
#define _DAT_FONT6X16_H_

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

////////////////////////////////////////////////////////////////////////////////
//
// Defines.
//
////////////////////////////////////////////////////////////////////////////////

#define FONT6X16_WIDTH                               6
#define FONT6X16_HEIGHT                             16
#define FONT6X16_BYTES_PER_CHAR                     12
#define FONT6X16_CHAR_OFFSET                        32
#define FONT6X16_CHAR_COUNT                         95
#define FONT6X16_UNDERLINE                  0b01000000

#define FONT6X16_UPARROW                          0x10
#define FONT6X16_DOWNARROW                        0x11
#define FONT6X16_LEFTARROW                        0x12
#define FONT6X16_RIGHTARROW                       0x13
#define FONT6X16_PRINTER                          0x14
#define FONT6X16_ENTER                            0x15
#define FONT6X16_MENU                             0x16
#define FONT6X16_NOTOKLEFT                        0x17
#define FONT6X16_NOTOKRIGHT                       0x18
#define FONT6X16_OKLEFT                           0x19
#define FONT6X16_OKRIGHT                          0x1A
#define FONT6X16_DEGREE                           0x1B
#define FONT6X16_INTERNALBATTERYFULL              0x1C
#define FONT6X16_OSLASHLEFTHALF                   0x1D
#define FONT6X16_OSLASHRIGHTHALF                  0x1E
#define FONT6X16_BLOCK                            0x1F

////////////////////////////////////////////////////////////////////////////////
//
// Externals.
//
////////////////////////////////////////////////////////////////////////////////

extern const far rom UINT8 Font6x16[ FONT6X16_CHAR_COUNT ][ FONT6X16_BYTES_PER_CHAR ];

#endif
