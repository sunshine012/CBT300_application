////////////////////////////////////////////////////////////////////////////////
//
// File                     : DatDictStandard.c
// Language                 : 
// Language id              : Jp
// Created on               : 2018-02-05 13:20:14
//         with             : DET-50
//         version          : 4.0.1.10 (Debug Build)
//         by               : che
//
// Note:                                                               
// This file is generated automatically. Do not make manual changes to 
// this file. These changes will be lost the next time this file is    
// generated.                                                          
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Included files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DatDictStandard.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

//
// English US string offsets.
//

const far rom UINT16 DictUsOffsets[] = {
     0, // GOOD BATTERY
    13, // GOOD RECHARGE
    27, // CHARGE RETEST
    41, // REPLACE BATTERY
    57, // BAD CELL
    66, // BATTERY TEST
    79, // TESTING BAT
    91, // PLEASE WAIT
   103, // CHECK CONNECTION
   120, // INNER ERROR
   132, // INPUT CCA
   142, // CALIBATION DONE
   158, // CALIBATION FAIL
   174, // AGM
   178, // REGULAR FLOODED
   194, // BATTERY TYPE
   207, // INPUT RATING
   220, // CALIBATION
   231, // LANGUAGE
   240, // ENGLISH
   248, // CHINESE
   256, // SERIAL NUMBER
   270, // INITIAL BT
   281, // BT READY
   290, // BT PAIR DONE
   303, // BT SENDING DATA
   319, // PAIR FAIL,REPAIR?
   503, // SEND COMPLETED
   337, // SEND FAIL
   347, // RESEND LAST DATA?
   365, // YES
   369, // NO
   372, // INPUT SN DONE
   386, // SEND DATA TO BT?
   403, // PLEASE CONNECT
   418, // SERVICE REQUIRED
   435, // CANCEL PAIRING
   450, // ANDROID
   458, // IOS
   462, // OPERATE SYSTEM
   477, // INITIAL BLE
   489, // BLE READY
   499, // BLE SEND COMPLETED
   518, // CONNECT COMPLETED
   536, // CONN FAIL,RECONN?
   554, // BATTERY REF#
   567, // BLUETOOTH READY
   583, // PRESS ENTER CANCEL
   602, // UPDATE COMPLETE
   618, // RESTART TOOL
   631  // PROGRAMING
};

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////
/*
const far rom DATA_PTR DictStandardLanguages[] =
{
  (DATA_PTR)DictUsOffsets,
};
*/
const far rom CHAR DictStandardStrings[] =
{
  /*     0 */ 'G','O','O','D',' ','B','A','T','T','E','R','Y','\000','G','O','O','D',' ','R','E','C','H','A','R','G',
  /*    25 */ 'E','\000','C','H','A','R','G','E',' ','R','E','T','E','S','T','\000','R','E','P','L','A','C','E',' ','B',
  /*    50 */ 'A','T','T','E','R','Y','\000','B','A','D',' ','C','E','L','L','\000','B','A','T','T','E','R','Y',' ','T',
  /*    75 */ 'E','S','T','\000','T','E','S','T','I','N','G',' ','B','A','T','\000','P','L','E','A','S','E',' ','W','A',
  /*   100 */ 'I','T','\000','C','H','E','C','K',' ','C','O','N','N','E','C','T','I','O','N','\000','I','N','N','E','R',
  /*   125 */ ' ','E','R','R','O','R','\000','I','N','P','U','T',' ','C','C','A','\000','C','A','L','I','B','A','T','I',
  /*   150 */ 'O','N',' ','D','O','N','E','\000','C','A','L','I','B','A','T','I','O','N',' ','F','A','I','L','\000','A',
  /*   175 */ 'G','M','\000','R','E','G','U','L','A','R',' ','F','L','O','O','D','E','D','\000','B','A','T','T','E','R',
  /*   200 */ 'Y',' ','T','Y','P','E','\000','I','N','P','U','T',' ','R','A','T','I','N','G','\000','C','A','L','I','B',
  /*   225 */ 'A','T','I','O','N','\000','L','A','N','G','U','A','G','E','\000','E','N','G','L','I','S','H','\000','C','H',
  /*   250 */ 'I','N','E','S','E','\000','S','E','R','I','A','L',' ','N','U','M','B','E','R','\000','I','N','I','T','I',
  /*   275 */ 'A','L',' ','B','T','\000','B','T',' ','R','E','A','D','Y','\000','B','T',' ','P','A','I','R',' ','D','O',
  /*   300 */ 'N','E','\000','B','T',' ','S','E','N','D','I','N','G',' ','D','A','T','A','\000','P','A','I','R',' ','F',
  /*   325 */ 'A','I','L',',','R','E','P','A','I','R','?','\000','S','E','N','D',' ','F','A','I','L','\000','R','E','S',
  /*   350 */ 'E','N','D',' ','L','A','S','T',' ','D','A','T','A','?','\000','Y','E','S','\000','N','O','\000','I','N','P',
  /*   375 */ 'U','T',' ','S','N',' ','D','O','N','E','\000','S','E','N','D',' ','D','A','T','A',' ','T','O',' ','B',
  /*   400 */ 'T','?','\000','P','L','E','A','S','E',' ','C','O','N','N','E','C','T','\000','S','E','R','V','I','C','E',
  /*   425 */ ' ','R','E','Q','U','I','R','E','D','\000','C','A','N','C','E','L',' ','P','A','I','R','I','N','G','\000',
  /*   450 */ 'A','N','D','R','O','I','D','\000','I','O','S','\000','O','P','E','R','A','T','E',' ','S','Y','S','T','E',
  /*   475 */ 'M','\000','I','N','I','T','I','A','L',' ','B','L','E','\000','B','L','E',' ','R','E','A','D','Y','\000','B',
  /*   500 */ 'L','E',' ','S','E','N','D',' ','C','O','M','P','L','E','T','E','D','\000','C','O','N','N','E','C','T',
  /*   525 */ ' ','C','O','M','P','L','E','T','E','D','\000','C','O','N','N',' ','F','A','I','L',',','R','E','C','O',
  /*   550 */ 'N','N','?','\000','B','A','T','T','E','R','Y',' ','R','E','F','#','\000','B','L','U','E','T','O','O','T',
  /*   575 */ 'H',' ','R','E','A','D','Y','\000','P','R','E','S','S',' ','E','N','T','E','R',' ','C','A','N','C','E',
  /*   600 */ 'L','\000','U','P','D','A','T','E',' ','C','O','M','P','L','E','T','E','\000','R','E','S','T','A','R','T',
  /*   625 */ ' ','T','O','O','L','\000','P','R','O','G','R','A','M','I','N','G','\000'
};
