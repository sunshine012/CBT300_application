////////////////////////////////////////////////////////////////////////////////
//
// File                     : DatDictStandard.c
//
// Note:
// This file is generated automatically. Do not make manual changes to
// this file. These changes will be lost the next time this file is
// generated.
//
// Build Time: 9/4/2017 14:24:13
// Built By:   Dictionay and Font Generator  V 1.2.4.0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Included files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"
#include "DatDictAsian.h"


////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////
//
// Simpilified Chinese string offsets.
//
const far rom UINT16 DictSCOffsets[] = {
	0, //GoodBattery
	10, //GoodRecharge
	24, //ChargeRetest
	38, //ReplaceBattery
	48, //BADCELL
	66, //BatteryTest
	76, //TestingBattery
	90, //PleaseWait
	98, //CheckConnect
	112, //InnerError
	122, //InputCCAValue
	140, //CalibationDONE
	150, //CalibationFail
	160, //Agm
	168, //RegularFlooded
	180, //BatteryType
	190, //InputRating
	202, //Calibation
	208, //Language
	214, //English
	220, //Chinese
	226, //InputSerialNo
	238, //InitialBT
	250, //BTReady
	260, //BTPairDone
	274, //BTSendData
	290, //BTPairFailRePair
	312, //SendDataComplete
	322, //SendDataFail
	332, //ResendLastData
	352, //Yes
	356, //No
	360, //InputSNDone
	376, //SendBTData
	388, //PleaseConnect
	396, //ServiceRequired
	408, //CancelPairing
	418, //Android
	424, //IOS
	430, //OperateSystem
	444, //BLEInitial
	458, //BLEReady
	474, //BLESendCompleted
	490, //BLEConnectCompleted
	506, //BLEFailReconnect
	528, //BatteryRefNb
	538, //BluetoothReady
	548, //PressEnterCancel
};

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////
/*
const far rom DATA_PTR DictAsianLanguages[] =
{
   (DATA_PTR)DictAEOffsets,
   (DATA_PTR)DictSCOffsets,
   (DATA_PTR)DictJPOffsets,
   (DATA_PTR)DictKrOffsets
};
*/

const far rom WCHAR DictAsianStrings[] ={


	/*********** Chinese ***********/

	// 0  GoodBattery
	128, 129, 130, 131,  0, // Cn
	// 10  GoodRecharge
	130, 131, 45, 132, 133, 128,  0, // Cn
	// 24  ChargeRetest
	133, 128, 134, 135, 136, 137,  0, // Cn
	// 38  ReplaceBattery
	138, 139, 128, 129,  0, // Cn
	// 48  BADCELL
	140, 141, 128, 129, 45, 142, 138, 139,  0, // Cn
	// 66  BatteryTest
	128, 129, 136, 137,  0, // Cn
	// 76  TestingBattery
	143, 144, 136, 137, 128, 129,  0, // Cn
	// 90  PleaseWait
	145, 146, 147,  0, // Cn
	// 98  CheckConnect
	148, 136, 128, 129, 149, 150,  0, // Cn
	// 112  InnerError
	151, 152, 153, 154,  0, // Cn
	// 122  InputCCAValue
	155, 156, 128, 129, 67, 67, 65, 157,  0, // Cn
	// 140  CalibationDONE
	158, 159, 160, 161,  0, // Cn
	// 150  CalibationFail
	158, 159, 162, 163,  0, // Cn
	// 160  Agm
	65, 71, 77,  0, // Cn
	// 168  RegularFlooded
	164, 165, 166, 128, 129,  0, // Cn
	// 180  BatteryType
	128, 129, 167, 168,  0, // Cn
	// 190  InputRating
	155, 156, 169, 170, 157,  0, // Cn
	// 202  Calibation
	158, 159,  0, // Cn
	// 208  Language
	171, 172,  0, // Cn
	// 214  English
	173, 171,  0, // Cn
	// 220  Chinese
	174, 175,  0, // Cn
	// 226  InputSerialNo
	155, 156, 176, 177, 178,  0, // Cn
	// 238  InitialBT
	179, 180, 181, 182, 183,  0, // Cn
	// 250  BTReady
	182, 183, 184, 185,  0, // Cn
	// 260  BTPairDone
	182, 183, 186, 187, 188, 160,  0, // Cn
	// 274  BTSendData
	182, 183, 143, 189, 190, 191, 192,  0, // Cn
	// 290  BTPairFailRePair
	186, 187, 162, 163, 44, 193, 194, 186, 187, 63,  0, // Cn
	// 312  SendDataComplete
	189, 190, 160, 161,  0, // Cn
	// 322  SendDataFail
	189, 190, 162, 163,  0, // Cn
	// 332  ResendLastData
	189, 190, 195, 196, 136, 137, 191, 192, 63,  0, // Cn
	// 352  Yes
	197,  0, // Cn
	// 356  No
	198,  0, // Cn
	// 360  InputSNDone
	176, 177, 178, 155, 156, 188, 160,  0, // Cn
	// 376  SendBTData
	189, 190, 191, 192, 199,  0, // Cn
	// 388  PleaseConnect
	145, 149, 150,  0, // Cn
	// 396  ServiceRequired
	145, 200, 201, 202, 203,  0, // Cn
	// 408  CancelPairing
	204, 205, 186, 187,  0, // Cn
	// 418  Android
	206, 207,  0, // Cn
	// 424  IOS
	208, 209,  0, // Cn
	// 430  OperateSystem
	210, 211, 201, 212, 167, 168,  0, // Cn
	// 444  BLEInitial
	179, 180, 181, 66, 76, 69,  0, // Cn
	// 458  BLEReady
	66, 76, 69, 159, 213, 184, 185,  0, // Cn
	// 474  BLESendCompleted
	66, 76, 69, 189, 190, 188, 160,  0, // Cn
	// 490  BLEConnectCompleted
	66, 76, 69, 149, 150, 160, 161,  0, // Cn
	// 506  BLEFailReconnect
	149, 150, 162, 163, 214, 193, 194, 149, 150, 63,  0, // Cn
	// 528  BatteryRefNb
	128, 129, 168, 178,  0, // Cn
	// 538  BluetoothReady
	182, 183, 184, 185,  0, // Cn
	// 548  PressEnterCancel
	215, 216, 217, 204, 205,  0, // Cn
};

// Add termination character. Otherwise the last string will be incorrect
//CHAR TerminationChar1[] = {0};

