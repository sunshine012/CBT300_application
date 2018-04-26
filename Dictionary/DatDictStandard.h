////////////////////////////////////////////////////////////////////////////////
//
// File                     : DatDictStandard.h
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

#ifndef _DAT_DICT_STANDARD_H_
#define _DAT_DICT_STANDARD_H_

////////////////////////////////////////////////////////////////////////////////
//
// Included files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

//#pragma romdata _DictStandard_

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

// Constants.
#define DICT_STANDARD_LANGUAGE_COUNT    1
#define DICT_STANDARD_INDEX_OFFSET     0

// Languages.
#define DICT_LANGUAGE_ENGLISH_US        0

// Texts.
#define DICT_TEXT_GOODBATTERY                              (DICT_STANDARD_INDEX_OFFSET +  0) // GOOD BATTERY
#define DICT_TEXT_GOODRECHARGE                             (DICT_STANDARD_INDEX_OFFSET +  1) // GOOD RECHARGE
#define DICT_TEXT_CHARGERETEST                             (DICT_STANDARD_INDEX_OFFSET +  2) // CHARGE RETEST
#define DICT_TEXT_REPLACEBATTERY                           (DICT_STANDARD_INDEX_OFFSET +  3) // REPLACE BATTERY
#define DICT_TEXT_BADCELL                                  (DICT_STANDARD_INDEX_OFFSET +  4) // BAD CELL
#define DICT_TEXT_BATTERYTEST                              (DICT_STANDARD_INDEX_OFFSET +  5) // BATTERY TEST
#define DICT_TEXT_TESTINGBATTERY                           (DICT_STANDARD_INDEX_OFFSET +  6) // TESTING BAT
#define DICT_TEXT_PLEASEWAIT                               (DICT_STANDARD_INDEX_OFFSET +  7) // PLEASE WAIT
#define DICT_TEXT_CHECKCONNECT                             (DICT_STANDARD_INDEX_OFFSET +  8) // CHECK CONNECTION
#define DICT_TEXT_INNERERROR                               (DICT_STANDARD_INDEX_OFFSET +  9) // INNER ERROR
#define DICT_TEXT_INPUTCCAVALUE                            (DICT_STANDARD_INDEX_OFFSET + 10) // INPUT CCA
#define DICT_TEXT_CALIBATIONDONE                           (DICT_STANDARD_INDEX_OFFSET + 11) // CALIBATION DONE
#define DICT_TEXT_CALIBATIONFAIL                           (DICT_STANDARD_INDEX_OFFSET + 12) // CALIBATION FAIL
#define DICT_TEXT_AGM                                      (DICT_STANDARD_INDEX_OFFSET + 13) // AGM
#define DICT_TEXT_REGULARFLOODED                           (DICT_STANDARD_INDEX_OFFSET + 14) // REGULAR FLOODED
#define DICT_TEXT_BATTERYTYPE                              (DICT_STANDARD_INDEX_OFFSET + 15) // BATTERY TYPE
#define DICT_TEXT_INPUTRATING                              (DICT_STANDARD_INDEX_OFFSET + 16) // INPUT RATING
#define DICT_TEXT_CALIBATION                               (DICT_STANDARD_INDEX_OFFSET + 17) // CALIBATION 
#define DICT_TEXT_LANGUAGE                                 (DICT_STANDARD_INDEX_OFFSET + 18) // LANGUAGE
#define DICT_TEXT_ENGLISH                                  (DICT_STANDARD_INDEX_OFFSET + 19) // ENGLISH
#define DICT_TEXT_CHINESE                                  (DICT_STANDARD_INDEX_OFFSET + 20) // CHINESE
#define DICT_TEXT_INPUTSERIALNO                            (DICT_STANDARD_INDEX_OFFSET + 21) // SERIAL NUMBER
#define DICT_TEXT_INITIALBT                                (DICT_STANDARD_INDEX_OFFSET + 22) // INITIAL BT
#define DICT_TEXT_BTREADY                                  (DICT_STANDARD_INDEX_OFFSET + 23) // BT READY
#define DICT_TEXT_BTPAIRDONE                               (DICT_STANDARD_INDEX_OFFSET + 24) // BT PAIR DONE
#define DICT_TEXT_BTSENDDATA                               (DICT_STANDARD_INDEX_OFFSET + 25) // BT SENDING DATA
#define DICT_TEXT_BTPAIRFAILREPAIR                         (DICT_STANDARD_INDEX_OFFSET + 26) // PAIR FAIL,REPAIR?
#define DICT_TEXT_SENDDATACOMPLETE                         (DICT_STANDARD_INDEX_OFFSET + 27) // SEND COMPLETED
#define DICT_TEXT_SENDDATAFAIL                             (DICT_STANDARD_INDEX_OFFSET + 28) // SEND FAIL
#define DICT_TEXT_RESENDLASTDATA                           (DICT_STANDARD_INDEX_OFFSET + 29) // RESEND LAST DATA?
#define DICT_TEXT_YES                                      (DICT_STANDARD_INDEX_OFFSET + 30) // YES
#define DICT_TEXT_NO                                       (DICT_STANDARD_INDEX_OFFSET + 31) // NO
#define DICT_TEXT_INPUTSNDONE                              (DICT_STANDARD_INDEX_OFFSET + 32) // INPUT SN DONE
#define DICT_TEXT_SENDBTDATA                               (DICT_STANDARD_INDEX_OFFSET + 33) // SEND DATA TO BT?
#define DICT_TEXT_PLEASECONNECT                            (DICT_STANDARD_INDEX_OFFSET + 34) // PLEASE CONNECT
#define DICT_TEXT_SERVICEREQUIRED                          (DICT_STANDARD_INDEX_OFFSET + 35) // SERVICE REQUIRED
#define DICT_TEXT_CANCELPAIRING                            (DICT_STANDARD_INDEX_OFFSET + 36) // CANCEL PAIRING
#define DICT_TEXT_ANDROID                                  (DICT_STANDARD_INDEX_OFFSET + 37) // ANDROID
#define DICT_TEXT_IOS                                      (DICT_STANDARD_INDEX_OFFSET + 38) // IOS
#define DICT_TEXT_OPERATESYSTEM                            (DICT_STANDARD_INDEX_OFFSET + 39) // OPERATE SYSTEM
#define DICT_TEXT_BLEINITIAL                               (DICT_STANDARD_INDEX_OFFSET + 40) // INITIAL BLE
#define DICT_TEXT_BLEREADY                                 (DICT_STANDARD_INDEX_OFFSET + 41) // BLE READY
#define DICT_TEXT_BLESENDCOMPLETED                         (DICT_STANDARD_INDEX_OFFSET + 42) // BLE SEND COMPLETED
#define DICT_TEXT_BLECONNECTCOMPLETED                      (DICT_STANDARD_INDEX_OFFSET + 43) // CONNECT COMPLETED
#define DICT_TEXT_BLEFAILRECONNECT                         (DICT_STANDARD_INDEX_OFFSET + 44) // CONN FAIL,RECONN?
#define DICT_TEXT_BATTERYREFNB                             (DICT_STANDARD_INDEX_OFFSET + 45) // BATTERY REF#
#define DICT_TEXT_BLUETOOTHREADY                           (DICT_STANDARD_INDEX_OFFSET + 46) // BLUETOOTH READY
#define DICT_TEXT_PRESSENTERCANCEL                         (DICT_STANDARD_INDEX_OFFSET + 47) // PRESS ENTER CANCEL
#define DICT_TEXT_UPDATECOMPLETE                           (DICT_STANDARD_INDEX_OFFSET + 48) // UPDATE COMPLETE
#define DICT_TEXT_RESTARTTOOL                              (DICT_STANDARD_INDEX_OFFSET + 49) // RESTART TOOL
#define DICT_TEXT_PROGRAMING                               (DICT_STANDARD_INDEX_OFFSET + 50) // PROGRAMING

////////////////////////////////////////////////////////////////////////////////
//
// External declerations.
//
////////////////////////////////////////////////////////////////////////////////

extern const far rom DATA_PTR DictStandardLanguages[];
extern const far rom CHAR     DictStandardStrings[];
extern const far rom UINT16 DictUsOffsets[];
////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
