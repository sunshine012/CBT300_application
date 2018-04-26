////////////////////////////////////////////////////////////////////////////////
//
// File                     : Font6x8.c
// Font                     : Font6x8
// Format                   : Midtronics
// Created on               : 2007-09-05 11:17:38
//         with             : Fcg50
//         version          : 0.0.4.0
//         by               : khemmes
//
// Note:                                                               
// This file is generated automatically. Do not make manual changes to 
// this file. These changes will be lost the next time this file is    
// generated.                                                          
//
////////////////////////////////////////////////////////////////////////////////

#include "SysFont6x8.h"

////////////////////////////////////////////////////////////////////////////////
//
// Font definition.
//
////////////////////////////////////////////////////////////////////////////////
/*
const rom unsigned char Font6x8_Number[ 10 ][ FONT6X8_BYTES_PER_CHAR ] = 
{
  { 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 0
  { 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, // 1
  { 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 2
  { 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00 }, // 3
  { 0x1F, 0x10, 0x10, 0x7C, 0x10, 0x00 }, // 4
  { 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 5
  { 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00 }, // 6
  { 0x01, 0x01, 0x71, 0x0D, 0x03, 0x00 }, // 7
  { 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 8
  { 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00 }, // 9
};
*/

const rom unsigned char Font6x8[ FONT6X8_CHAR_COUNT ][ FONT6X8_BYTES_PER_CHAR ] = 
{
  { 0x30, 0x3C, 0x3E, 0x3C, 0x30, 0x00 }, // UpAarrow
  { 0x06, 0x1E, 0x3E, 0x1E, 0x06, 0x00 }, // DownArrow
  { 0x08, 0x1C, 0x1C, 0x3E, 0x3E, 0x00 }, // LeftArrow
  { 0x3E, 0x3E, 0x1C, 0x1C, 0x08, 0x00 }, // RightArrow
  { 0x14, 0x36, 0x77, 0x36, 0x14, 0x00 }, // UpDownArrow
  { 0x10, 0x38, 0x7C, 0x10, 0x1F, 0x00 }, // Enter
  { 0x3E, 0x41, 0x55, 0x55, 0x41, 0x3E }, // Menu
  { 0x7F, 0x7B, 0x41, 0x7F, 0x7F, 0x00 }, // Switch1
  { 0x7F, 0x45, 0x55, 0x51, 0x7F, 0x00 }, // Switch2
  { 0x7F, 0x5D, 0x55, 0x41, 0x7F, 0x00 }, // Switch3
  { 0x7F, 0x71, 0x77, 0x41, 0x7F, 0x00 }, // Switch4
  { 0x7F, 0x51, 0x55, 0x45, 0x7F, 0x00 }, // Switch5
  { 0x00, 0x06, 0x09, 0x09, 0x06, 0x00 }, // Degree
  { 0x08, 0x10, 0x20, 0x18, 0x06, 0x01 }, // Ok
  { 0x22, 0x14, 0x08, 0x14, 0x22, 0x00 }, // NotOk
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, // Block
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Reserved10
  { 0x00, 0x06, 0x5F, 0x06, 0x00, 0x00 }, // ExclamationMark
  { 0x00, 0x03, 0x00, 0x03, 0x00, 0x00 }, // DoubleQoute
  { 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, // PoundSign
  { 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, // DollarSign
  { 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, // Percent
  { 0x36, 0x49, 0x56, 0x20, 0x58, 0x00 }, // Empersand
  { 0x00, 0x00, 0x04, 0x03, 0x00, 0x00 }, // Quote
  { 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, // LeftParentheses
  { 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, // RightParentheses
  { 0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x00 }, // Asterix
  { 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, // Plus
  { 0x00, 0x00, 0xA0, 0x60, 0x00, 0x00 }, // Comma
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, // Minus
  { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 }, // Period
  { 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, // Slash
  { 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 0
  { 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, // 1
  { 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 2
  { 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00 }, // 3
  { 0x1F, 0x10, 0x10, 0x7C, 0x10, 0x00 }, // 4
  { 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 5
  { 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00 }, // 6
  { 0x01, 0x01, 0x71, 0x0D, 0x03, 0x00 }, // 7
  { 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 8
  { 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00 }, // 9
  { 0x00, 0x00, 0x6C, 0x6C, 0x00, 0x00 }, // Colon
  { 0x00, 0x00, 0xAC, 0x6C, 0x00, 0x00 }, // SemiColon
  { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, // LeftAngleBracket
  { 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, // EqualSign
  { 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 }, // RightAngleBracket
  { 0x02, 0x01, 0x51, 0x09, 0x06, 0x00 }, // QuestionMark
  { 0x3C, 0x42, 0x5A, 0x5A, 0x4C, 0x00 }, // AtSymbol
  { 0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00 }, // A
  { 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, // B
  { 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, // C
  { 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // D
  { 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, // E
  { 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, // F
  { 0x3E, 0x41, 0x49, 0x49, 0x3A, 0x00 }, // G
  { 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, // H
  { 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, // I
  { 0x30, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // J
  { 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, // K
  { 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, // L
  { 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00 }, // M
  { 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, // N
  { 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // O
  { 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, // P
  { 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, // Q
  { 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, // R
  { 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, // S
  { 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00 }, // T
  { 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // U
  { 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, // V
  { 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, // W
  { 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, // X
  { 0x07, 0x08, 0x70, 0x08, 0x07, 0x00 }, // Y
  { 0x61, 0x51, 0x49, 0x45, 0x43, 0x00 }, // Z
  { 0x00, 0x7F, 0x41, 0x41, 0x00, 0x00 }, // LeftSquareBracket
  { 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, // BackSlash
  { 0x00, 0x41, 0x41, 0x7F, 0x00, 0x00 }, // RightSquareBracket
  { 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, // 
  { 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }  // Underscore
};
