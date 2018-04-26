/****************************************************************************
;
;  Copyright (c) Midtronics 2006
;
;     This module defines the constant string data
;
;     Algorithm tracking is: 271-Z000173-A
;	Revised by KingChen 03/25/2016
****************************************************************************/
#include "AppCurvePN.h"

const rom _CurveDataStruct Curve[NUM_OF_CURVES] = {
                               {  0,                  //curve number 071-2TA106-A   (REGULAR 12V)
                                   15,                 //badcell cutoff 50CCA (no used)
                                   1100,              //badcell high voltage limit
                                    550,              //badcell low voltage limit
                                   1240,              //battery recharge voltage
                                   1140,              //battery ok to test voltage
                                   1270,              //battery full charge voltage
                                   1340,              //battery surface charge voltage (no used)
                                   90,                //conductance above recharge percent
                                   255,               //conductance below recharge percent
                                   118,               //temperature compensation percent (no used)
                                   100,               //CCA factor percent
                                   125,               //CA factor percent
                                   130,               //MCA factor percent
                                   100,               //JIS factor percent
                                   56,                //DIN factor percent
                                   100,               //SAE factor percent
                                   63,                //IEC factor percent
                                   92,                //EN factor percent
                                   60,                //SOC percent cutoff
                                   0,                 //SOC control 0
                                   0,                 //SOC control 1
                                   20,                //pass percent for 8.00volts
                                   20,                //pass percent for 8.05volts
                                   20,                //pass percent for 8.10volts
                                   20,                //pass percent for 8.15volts
                                   20,                //pass percent for 8.20volts
                                   20,                //pass percent for 8.25volts
                                   20,                //pass percent for 8.30volts
                                   20,                //pass percent for 8.35volts
                                   20,                //pass percent for 8.40volts
                                   20,                //pass percent for 8.45volts
                                   20,                //pass percent for 8.50volts
                                   20,                //pass percent for 8.55volts
                                   20,                //pass percent for 8.60volts
                                   20,                //pass percent for 8.65volts
                                   21,                //pass percent for 8.70volts
                                   21,                //pass percent for 8.75volts
                                   22,                //pass percent for 8.80volts
                                   22,                //pass percent for 8.85volts
                                   22,                //pass percent for 8.90volts
                                   23,                //pass percent for 8.95volts
                                   23,                //pass percent for 9.00volts
                                   24,                //pass percent for 9.05volts
                                   24,                //pass percent for 9.10volts
                                   24,                //pass percent for 9.15volts
                                   25,                //pass percent for 9.20volts
                                   25,                //pass percent for 9.25volts
                                   26,                //pass percent for 9.30volts
                                   26,                //pass percent for 9.35volts
                                   27,                //pass percent for 9.40volts
                                   27,                //pass percent for 9.45volts
                                   27,                //pass percent for 9.50volts
                                   28,                //pass percent for 9.55volts
                                   28,                //pass percent for 9.60volts
                                   29,                //pass percent for 9.65volts
                                   29,                //pass percent for 9.70volts
                                   29,                //pass percent for 9.75volts
                                   30,                //pass percent for 9.80volts
                                   30,                //pass percent for 9.85volts
                                   31,                //pass percent for 9.90volts
                                   31,                //pass percent for 9.95volts
                                   31,                //pass percent for 10.00volts
                                   32,                //pass percent for 10.05volts
                                   32,                //pass percent for 10.10volts
                                   33,                //pass percent for 10.15volts
                                   33,                //pass percent for 10.20volts
                                   33,                //pass percent for 10.25volts
                                   34,                //pass percent for 10.30volts
                                   34,                //pass percent for 10.35volts
                                   35,                //pass percent for 10.40volts
                                   35,                //pass percent for 10.45volts
                                   36,                //pass percent for 10.50volts
                                   36,                //pass percent for 10.55volts
                                   36,                //pass percent for 10.60volts
                                   37,                //pass percent for 10.65volts
                                   37,                //pass percent for 10.70volts
                                   38,                //pass percent for 10.75volts
                                   38,                //pass percent for 10.80volts
                                   38,                //pass percent for 10.85volts
                                   39,                //pass percent for 10.90volts
                                   39,                //pass percent for 10.95volts
                                   255,               //pass percent for 11.00volts
                                   255,               //pass percent for 11.05volts
                                   255,               //pass percent for 11.10volts
                                   255,               //pass percent for 11.15volts
                                   255,               //pass percent for 11.20volts
                                   255,               //pass percent for 11.25volts
                                   255,               //pass percent for 11.30volts
                                   255,               //pass percent for 11.35volts
                                   28,                //pass percent for 11.40volts
                                   29,                //pass percent for 11.45volts
                                   30,                //pass percent for 11.50volts
                                   32,                //pass percent for 11.55volts
                                   33,                //pass percent for 11.60volts
                                   35,                //pass percent for 11.65volts
                                   37,                //pass percent for 11.70volts
                                   39,                //pass percent for 11.75volts
                                   41,                //pass percent for 11.80volts
                                   43,                //pass percent for 11.85volts
                                   45,                //pass percent for 11.90volts
                                   47,                //pass percent for 11.95volts
                                   50,                //pass percent for 12.00volts
                                   52,                //pass percent for 12.05volts
                                   55,                //pass percent for 12.10volts
                                   57,                //pass percent for 12.15volts
                                   60,                //pass percent for 12.20volts
                                   63,                //pass percent for 12.25volts
                                   66,                //pass percent for 12.30volts
                                   69,                //pass percent for 12.35volts
                                   72,                //pass percent for 12.40volts
                                   75,                //pass percent for 12.45volts
                                   77,                //pass percent for 12.50volts
                                   80,                //pass percent for 12.55volts
                                   82,                //pass percent for 12.60volts
                                   84,                //pass percent for 12.65volts
                                   85,                //pass percent for 12.70volts
                                   85,                //pass percent for 12.75volts
                                    0,                //fail percent for 8.00volts
                                    0,                //fail percent for 8.05volts
                                    0,                //fail percent for 8.10volts
                                    0,                //fail percent for 8.15volts
                                    0,                //fail percent for 8.20volts
                                    0,                //fail percent for 8.25volts
                                    0,                //fail percent for 8.30volts
                                    0,                //fail percent for 8.35volts
                                    0,                //fail percent for 8.40volts
                                    0,                //fail percent for 8.45volts
                                    0,                //fail percent for 8.50volts
                                    0,                //fail percent for 8.55volts
                                    0,                //fail percent for 8.60volts
                                    0,                //fail percent for 8.65volts
                                    0,                //fail percent for 8.70volts
                                    0,                //fail percent for 8.75volts
                                    0,                //fail percent for 8.80volts
                                    0,                //fail percent for 8.85volts
                                    0,                //fail percent for 8.90volts
                                    0,                //fail percent for 8.95volts
                                    0,                //fail percent for 9.00volts
                                    0,                //fail percent for 9.05volts
                                    0,                //fail percent for 9.10volts
                                    0,                //fail percent for 9.15volts
                                    0,                //fail percent for 9.20volts
                                    0,                //fail percent for 9.25volts
                                    0,                //fail percent for 9.30volts
                                    0,                //fail percent for 9.35volts
                                    0,                //fail percent for 9.40volts
                                    0,                //fail percent for 9.45volts
                                    0,                //fail percent for 9.50volts
                                    0,                //fail percent for 9.55volts
                                    0,                //fail percent for 9.60volts
                                    0,                //fail percent for 9.65volts
                                    0,                //fail percent for 9.70volts
                                    0,                //fail percent for 9.75volts
                                    0,                //fail percent for 9.80volts
                                    0,                //fail percent for 9.85volts
                                    0,                //fail percent for 9.90volts
                                    0,                //fail percent for 9.95volts
                                    0,                //fail percent for 10.00volts
                                    0,                //fail percent for 10.05volts
                                    0,                //fail percent for 10.10volts
                                    0,                //fail percent for 10.15volts
                                    0,                //fail percent for 10.20volts
                                    0,                //fail percent for 10.25volts
                                    0,                //fail percent for 10.30volts
                                    0,                //fail percent for 10.35volts
                                    0,                //fail percent for 10.40volts
                                    0,                //fail percent for 10.45volts
                                    0,                //fail percent for 10.50volts
                                    0,                //fail percent for 10.55volts
                                    0,                //fail percent for 10.60volts
                                    0,                //fail percent for 10.65volts
                                    0,                //fail percent for 10.70volts
                                    0,                //fail percent for 10.75volts
                                    0,                //fail percent for 10.80volts
                                    0,                //fail percent for 10.85volts
                                    0,                //fail percent for 10.90volts
                                    0,                //fail percent for 10.95volts
                                    0,                //fail percent for 11.00volts
                                    0,                //fail percent for 11.05volts
                                    0,                //fail percent for 11.10volts
                                    0,                //fail percent for 11.15volts
                                    0,                //fail percent for 11.20volts
                                    0,                //fail percent for 11.25volts
                                    0,                //fail percent for 11.30volts
                                    0,                //fail percent for 11.35volts
                                    0,                //fail percent for 11.40volts
                                    0,                //fail percent for 11.45volts
                                    0,                //fail percent for 11.50volts
                                    0,                //fail percent for 11.55volts
                                    0,                //fail percent for 11.60volts
                                    0,                //fail percent for 11.65volts
                                    2,                //fail percent for 11.70volts
                                    5,                //fail percent for 11.75volts
                                    8,                //fail percent for 11.80volts
                                    11,               //fail percent for 11.85volts
                                    15,               //fail percent for 11.90volts
                                    19,               //fail percent for 11.95volts
                                    23,               //fail percent for 12.00volts
                                    28,               //fail percent for 12.05volts
                                    33,               //fail percent for 12.10volts
                                    38,               //fail percent for 12.15volts
                                    44,               //fail percent for 12.20volts
                                    50,               //fail percent for 12.25volts
                                    57,               //fail percent for 12.30volts
                                    64,               //fail percent for 12.35volts
                                    72,               //fail percent for 12.40volts
                                    75,               //fail percent for 12.45volts
                                    77,               //fail percent for 12.50volts
                                    80,               //fail percent for 12.55volts
                                    82,               //fail percent for 12.60volts
                                    84,               //fail percent for 12.65volts
                                    85,               //fail percent for 12.70volts
                                    85,               //fail percent for 12.75volts
                                   7686},
                                   {           //curve  AGM Algthrom----Algorithm_071_2TAA02_A
					  					             1,                  //curve number Algorithm_071_2TAA02_A 12V AGM
                                   20,                 //badcell cutoff 50CCA
                                   1100,              //badcell high voltage limit
                                   550,              //badcell low voltage limit
                                   1260,              //battery recharge voltage
                                   1140,              //battery ok to test voltage
                                   1260,              //battery full charge voltage
                                   1340,              //battery surface charge voltage
                                   85,                //conductance above recharge percent
                                   255,               //conductance below recharge percent
                                   118,               //temperature compensation percent
                                   83,               //CCA factor percent  83%
                                   125,               //CA factor percent
                                   130,               //MCA factor percent
                                   100,               //JIS factor percent
                                   56,                //DIN factor percent
                                   100,               //SAE factor percent
                                   63,                //IEC factor percent
                                   92,                //EN factor percent
                                   60,                //SOC percent cutoff
                                   0,                 //SOC control 0
                                   0,                 //SOC control 1
                                   20,                //pass percent for 8.00volts
                                   20,                //pass percent for 8.05volts
                                   20,                //pass percent for 8.10volts
                                   20,                //pass percent for 8.15volts
                                   20,                //pass percent for 8.20volts
                                   20,                //pass percent for 8.25volts
                                   20,                //pass percent for 8.30volts
                                   20,                //pass percent for 8.35volts
                                   20,                //pass percent for 8.40volts
                                   20,                //pass percent for 8.45volts
                                   20,                //pass percent for 8.50volts
                                   20,                //pass percent for 8.55volts
                                   20,                //pass percent for 8.60volts
                                   20,                //pass percent for 8.65volts
                                   21,                //pass percent for 8.70volts
                                   21,                //pass percent for 8.75volts
                                   22,                //pass percent for 8.80volts
                                   22,                //pass percent for 8.85volts
                                   22,                //pass percent for 8.90volts
                                   23,                //pass percent for 8.95volts
                                   23,                //pass percent for 9.00volts
                                   24,                //pass percent for 9.05volts
                                   24,                //pass percent for 9.10volts
                                   24,                //pass percent for 9.15volts
                                   25,                //pass percent for 9.20volts
                                   25,                //pass percent for 9.25volts
                                   26,                //pass percent for 9.30volts
                                   26,                //pass percent for 9.35volts
                                   27,                //pass percent for 9.40volts
                                   27,                //pass percent for 9.45volts
                                   27,                //pass percent for 9.50volts
                                   28,                //pass percent for 9.55volts
                                   28,                //pass percent for 9.60volts
                                   29,                //pass percent for 9.65volts
                                   29,                //pass percent for 9.70volts
                                   29,                //pass percent for 9.75volts
                                   30,                //pass percent for 9.80volts
                                   30,                //pass percent for 9.85volts
                                   31,                //pass percent for 9.90volts
                                   31,                //pass percent for 9.95volts
                                   31,                //pass percent for 10.00volts
                                   32,                //pass percent for 10.05volts
                                   32,                //pass percent for 10.10volts
                                   33,                //pass percent for 10.15volts
                                   33,                //pass percent for 10.20volts
                                   33,                //pass percent for 10.25volts
                                   34,                //pass percent for 10.30volts
                                   34,                //pass percent for 10.35volts
                                   35,                //pass percent for 10.40volts
                                   35,                //pass percent for 10.45volts
                                   36,                //pass percent for 10.50volts
                                   36,                //pass percent for 10.55volts
                                   36,                //pass percent for 10.60volts
                                   37,                //pass percent for 10.65volts
                                   37,                //pass percent for 10.70volts
                                   38,                //pass percent for 10.75volts
                                   38,                //pass percent for 10.80volts
                                   38,                //pass percent for 10.85volts
                                   39,                //pass percent for 10.90volts
                                   39,                //pass percent for 10.95volts
                                   255,               //pass percent for 11.00volts
                                   255,               //pass percent for 11.05volts
                                   255,               //pass percent for 11.10volts
                                   255,               //pass percent for 11.15volts
                                   255,               //pass percent for 11.20volts
                                   255,               //pass percent for 11.25volts
                                   255,               //pass percent for 11.30volts
                                   255,               //pass percent for 11.35volts
                                   28,                //pass percent for 11.40volts
                                   31,                //pass percent for 11.45volts
                                   34,                //pass percent for 11.50volts
                                   37,                //pass percent for 11.55volts
                                   39,                //pass percent for 11.60volts
                                   42,                //pass percent for 11.65volts
                                   46,                //pass percent for 11.70volts
                                   49,                //pass percent for 11.75volts
                                   51,                //pass percent for 11.80volts
                                   54,                //pass percent for 11.85volts
                                   58,                //pass percent for 11.90volts
                                   60,                //pass percent for 11.95volts
                                   63,                //pass percent for 12.00volts
                                   66,                //pass percent for 12.05volts
                                   69,                //pass percent for 12.10volts
                                   70,                //pass percent for 12.15volts
                                   72,                //pass percent for 12.20volts
                                   74,                //pass percent for 12.25volts
                                   76,                //pass percent for 12.30volts
                                   78,                //pass percent for 12.35volts
                                   80,                //pass percent for 12.40volts
                                   82,                //pass percent for 12.45volts
                                   83,                //pass percent for 12.50volts
                                   84,                //pass percent for 12.55volts
                                   85,                //pass percent for 12.60volts
                                   85,                //pass percent for 12.65volts
                                   85,                //pass percent for 12.70volts
                                   85,                //pass percent for 12.75volts
                                    0,                //fail percent for 8.00volts
                                    0,                //fail percent for 8.05volts
                                    0,                //fail percent for 8.10volts
                                    0,                //fail percent for 8.15volts
                                    0,                //fail percent for 8.20volts
                                    0,                //fail percent for 8.25volts
                                    0,                //fail percent for 8.30volts
                                    0,                //fail percent for 8.35volts
                                    0,                //fail percent for 8.40volts
                                    0,                //fail percent for 8.45volts
                                    0,                //fail percent for 8.50volts
                                    0,                //fail percent for 8.55volts
                                    0,                //fail percent for 8.60volts
                                    0,                //fail percent for 8.65volts
                                    0,                //fail percent for 8.70volts
                                    0,                //fail percent for 8.75volts
                                    0,                //fail percent for 8.80volts
                                    0,                //fail percent for 8.85volts
                                    0,                //fail percent for 8.90volts
                                    0,                //fail percent for 8.95volts
                                    0,                //fail percent for 9.00volts
                                    0,                //fail percent for 9.05volts
                                    0,                //fail percent for 9.10volts
                                    0,                //fail percent for 9.15volts
                                    0,                //fail percent for 9.20volts
                                    0,                //fail percent for 9.25volts
                                    0,                //fail percent for 9.30volts
                                    0,                //fail percent for 9.35volts
                                    0,                //fail percent for 9.40volts
                                    0,                //fail percent for 9.45volts
                                    0,                //fail percent for 9.50volts
                                    0,                //fail percent for 9.55volts
                                    0,                //fail percent for 9.60volts
                                    0,                //fail percent for 9.65volts
                                    0,                //fail percent for 9.70volts
                                    0,                //fail percent for 9.75volts
                                    0,                //fail percent for 9.80volts
                                    0,                //fail percent for 9.85volts
                                    0,                //fail percent for 9.90volts
                                    0,                //fail percent for 9.95volts
                                    0,                //fail percent for 10.00volts
                                    0,                //fail percent for 10.05volts
                                    0,                //fail percent for 10.10volts
                                    0,                //fail percent for 10.15volts
                                    0,                //fail percent for 10.20volts
                                    0,                //fail percent for 10.25volts
                                    0,                //fail percent for 10.30volts
                                    0,                //fail percent for 10.35volts
                                    0,                //fail percent for 10.40volts
                                    0,                //fail percent for 10.45volts
                                    0,                //fail percent for 10.50volts
                                    0,                //fail percent for 10.55volts
                                    0,                //fail percent for 10.60volts
                                    0,                //fail percent for 10.65volts
                                    0,                //fail percent for 10.70volts
                                    0,                //fail percent for 10.75volts
                                    0,                //fail percent for 10.80volts
                                    0,                //fail percent for 10.85volts
                                    0,                //fail percent for 10.90volts
                                    0,                //fail percent for 10.95volts
                                    0,                //fail percent for 11.00volts
                                    0,                //fail percent for 11.05volts
                                    0,                //fail percent for 11.10volts
                                    0,                //fail percent for 11.15volts
                                    0,                //fail percent for 11.20volts
                                    0,                //fail percent for 11.25volts
                                    0,                //fail percent for 11.30volts
                                    0,                //fail percent for 11.35volts
                                    0,                //fail percent for 11.40volts
                                    0,                //fail percent for 11.45volts
                                    0,                //fail percent for 11.50volts
                                    0,                //fail percent for 11.55volts
                                    0,                //fail percent for 11.60volts
                                    0,                //fail percent for 11.65volts
                                    1,                //fail percent for 11.70volts
                                    3,                //fail percent for 11.75volts
                                    5,                //fail percent for 11.80volts
                                    7,                //fail percent for 11.85volts
                                    10,               //fail percent for 11.90volts
                                    13,               //fail percent for 11.95volts
                                    15,               //fail percent for 12.00volts
                                    18,               //fail percent for 12.05volts
                                    23,               //fail percent for 12.10volts
                                    25,               //fail percent for 12.15volts
                                    30,               //fail percent for 12.20volts
                                    34,               //fail percent for 12.25volts
                                    37,               //fail percent for 12.30volts
                                    44,               //fail percent for 12.35volts
                                    47,               //fail percent for 12.40volts
                                    55,               //fail percent for 12.45volts
                                    63,               //fail percent for 12.50volts
                                    72,               //fail percent for 12.55volts
                                    85,               //fail percent for 12.60volts
                                    85,               //fail percent for 12.65volts
                                    85,               //fail percent for 12.70volts
                                    85,               //fail percent for 12.75volts
                                   7686},  //curve check sum
                               {2,                 //LESS than 100cca Curve
                                15,                //badcell cutoff 50CCA
                                1100,              //badcell high voltage limit
                                 800,              //badcell low voltage limit
                                1240,              //battery recharge voltage
                                1170,              //battery ok to test voltage
                                1275,              //battery full charge voltage
                                1340,              //battery surface charge voltage
                                75,                //conductance above recharge percent
                                255,               //conductance below recharge percent
                                118,               //temperature compensation percent
                                100,               //CCA factor percent
                                125,               //CA factor percent
                                130,               //MCA factor percent
                                100,               //JIS factor percent
                                56,                //DIN factor percent
                                100,               //SAE factor percent
                                63,                //IEC factor percent
                                92,                //EN factor percent
                                60,                //SOC percent cutoff
                                0,                 //SOC control 0
                                0,                 //SOC control 1
                                15,                //pass percent for 8.00volts
                                15,                //pass percent for 8.05volts
                                15,                //pass percent for 8.10volts
                                16,                //pass percent for 8.15volts
                                16,                //pass percent for 8.20volts
                                16,                //pass percent for 8.25volts
                                16,                //pass percent for 8.30volts
                                16,                //pass percent for 8.35volts
                                16,                //pass percent for 8.40volts
                                17,                //pass percent for 8.45volts
                                17,                //pass percent for 8.50volts
                                17,                //pass percent for 8.55volts
                                17,                //pass percent for 8.60volts
                                17,                //pass percent for 8.65volts
                                17,                //pass percent for 8.70volts
                                18,                //pass percent for 8.75volts
                                18,                //pass percent for 8.80volts
                                18,                //pass percent for 8.85volts
                                18,                //pass percent for 8.90volts
                                18,                //pass percent for 8.95volts
                                18,                //pass percent for 9.00volts
                                19,                //pass percent for 9.05volts
                                19,                //pass percent for 9.10volts
                                19,                //pass percent for 9.15volts
                                19,                //pass percent for 9.20volts
                                19,                //pass percent for 9.25volts
                                19,                //pass percent for 9.30volts
                                20,                //pass percent for 9.35volts
                                20,                //pass percent for 9.40volts
                                20,                //pass percent for 9.45volts
                                20,                //pass percent for 9.50volts
                                20,                //pass percent for 9.55volts
                                20,                //pass percent for 9.60volts
                                21,                //pass percent for 9.65volts
                                21,                //pass percent for 9.70volts
                                21,                //pass percent for 9.75volts
                                21,                //pass percent for 9.80volts
                                21,                //pass percent for 9.85volts
                                21,                //pass percent for 9.90volts
                                22,                //pass percent for 9.95volts
                                22,                //pass percent for 10.00volts
                                22,                //pass percent for 10.05volts
                                22,                //pass percent for 10.10volts
                                22,                //pass percent for 10.15volts
                                22,                //pass percent for 10.20volts
                                23,                //pass percent for 10.25volts
                                23,                //pass percent for 10.30volts
                                23,                //pass percent for 10.35volts
                                23,                //pass percent for 10.40volts
                                23,                //pass percent for 10.45volts
                                23,                //pass percent for 10.50volts
                                24,                //pass percent for 10.55volts
                                24,                //pass percent for 10.60volts
                                24,                //pass percent for 10.65volts
                                24,                //pass percent for 10.70volts
                                24,                //pass percent for 10.75volts
                                24,                //pass percent for 10.80volts
                                25,                //pass percent for 10.85volts
                                25,                //pass percent for 10.90volts
                                25,                //pass percent for 10.95volts
                                25,                //pass percent for 11.00volts
                                25,                //pass percent for 11.05volts
                                26,                //pass percent for 11.10volts
                                26,                //pass percent for 11.15volts
                                26,                //pass percent for 11.20volts
                                27,                //pass percent for 11.25volts
                                27,                //pass percent for 11.30volts
                                27,                //pass percent for 11.35volts
                                28,                //pass percent for 11.40volts
                                28,                //pass percent for 11.45volts
                                28,                //pass percent for 11.50volts
                                28,                //pass percent for 11.55volts
                                29,                //pass percent for 11.60volts
                                29,                //pass percent for 11.65volts
                                29,                //pass percent for 11.70volts
                                30,                //pass percent for 11.75volts
                                30,                //pass percent for 11.80volts
                                34,                //pass percent for 11.85volts
                                38,                //pass percent for 11.90volts
                                41,                //pass percent for 11.95volts
                                45,                //pass percent for 12.00volts
                                49,                //pass percent for 12.05volts
                                53,                //pass percent for 12.10volts
                                56,                //pass percent for 12.15volts
                                60,                //pass percent for 12.20volts
                                64,                //pass percent for 12.25volts
                                68,                //pass percent for 12.30volts
                                71,                //pass percent for 12.35volts
                                75,                //pass percent for 12.40volts
                                75,                //pass percent for 12.45volts
                                75,                //pass percent for 12.50volts
                                75,                //pass percent for 12.55volts
                                75,                //pass percent for 12.60volts
                                75,                //pass percent for 12.65volts
                                75,                //pass percent for 12.70volts
                                75,                //pass percent for 12.75volts
                                0,                 //fail percent for 8.00volts
                                0,                 //fail percent for 8.05volts
                                0,                 //fail percent for 8.10volts
                                0,                 //fail percent for 8.15volts
                                0,                 //fail percent for 8.20volts
                                0,                 //fail percent for 8.25volts
                                0,                 //fail percent for 8.30volts
                                0,                 //fail percent for 8.35volts
                                0,                 //fail percent for 8.40volts
                                0,                 //fail percent for 8.45volts
                                0,                 //fail percent for 8.50volts
                                0,                 //fail percent for 8.55volts
                                0,                 //fail percent for 8.60volts
                                0,                 //fail percent for 8.65volts
                                0,                 //fail percent for 8.70volts
                                0,                 //fail percent for 8.75volts
                                0,                 //fail percent for 8.80volts
                                0,                 //fail percent for 8.85volts
                                0,                 //fail percent for 8.90volts
                                0,                 //fail percent for 8.95volts
                                0,                 //fail percent for 9.00volts
                                0,                 //fail percent for 9.05volts
                                0,                 //fail percent for 9.10volts
                                0,                 //fail percent for 9.15volts
                                0,                 //fail percent for 9.20volts
                                0,                 //fail percent for 9.25volts
                                0,                 //fail percent for 9.30volts
                                0,                 //fail percent for 9.35volts
                                0,                 //fail percent for 9.40volts
                                0,                 //fail percent for 9.45volts
                                0,                 //fail percent for 9.50volts
                                0,                 //fail percent for 9.55volts
                                0,                 //fail percent for 9.60volts
                                0,                 //fail percent for 9.65volts
                                0,                 //fail percent for 9.70volts
                                0,                 //fail percent for 9.75volts
                                0,                 //fail percent for 9.80volts
                                0,                 //fail percent for 9.85volts
                                0,                 //fail percent for 9.90volts
                                0,                 //fail percent for 9.95volts
                                0,                 //fail percent for 10.00volts
                                0,                 //fail percent for 10.05volts
                                0,                 //fail percent for 10.10volts
                                0,                 //fail percent for 10.15volts
                                0,                 //fail percent for 10.20volts
                                0,                 //fail percent for 10.25volts
                                0,                 //fail percent for 10.30volts
                                0,                 //fail percent for 10.35volts
                                0,                 //fail percent for 10.40volts
                                0,                 //fail percent for 10.45volts
                                0,                 //fail percent for 10.50volts
                                0,                 //fail percent for 10.55volts
                                0,                 //fail percent for 10.60volts
                                0,                 //fail percent for 10.65volts
                                0,                 //fail percent for 10.70volts
                                0,                 //fail percent for 10.75volts
                                0,                 //fail percent for 10.80volts
                                0,                 //fail percent for 10.85volts
                                0,                 //fail percent for 10.90volts
                                0,                 //fail percent for 10.95volts
                                0,                 //fail percent for 11.00volts
                                0,                 //fail percent for 11.05volts
                                0,                 //fail percent for 11.10volts
                                0,                 //fail percent for 11.15volts
                                0,                 //fail percent for 11.20volts
                                0,                 //fail percent for 11.25volts
                                0,                 //fail percent for 11.30volts
                                0,                 //fail percent for 11.35volts
                                0,                 //fail percent for 11.40volts
                                0,                 //fail percent for 11.45volts
                                0,                 //fail percent for 11.50volts
                                0,                 //fail percent for 11.55volts
                                0,                 //fail percent for 11.60volts
                                0,                 //fail percent for 11.65volts
                                0,                 //fail percent for 11.70volts
                                4,                 //fail percent for 11.75volts
                                8,                 //fail percent for 11.80volts
                                13,                //fail percent for 11.85volts
                                17,                //fail percent for 11.90volts
                                21,                //fail percent for 11.95volts
                                25,                //fail percent for 12.00volts
                                29,                //fail percent for 12.05volts
                                33,                //fail percent for 12.10volts
                                38,                //fail percent for 12.15volts
                                42,                //fail percent for 12.20volts
                                46,                //fail percent for 12.25volts
                                50,                //fail percent for 12.30volts
                                54,                //fail percent for 12.35volts
                                58,                //fail percent for 12.40volts
                                63,                //fail percent for 12.45volts
                                67,                //fail percent for 12.50volts
                                71,                //fail percent for 12.55volts
                                75,                //fail percent for 12.60volts
                                75,                //fail percent for 12.65volts
                                75,                //fail percent for 12.70volts
                                75,                //fail percent for 12.75volts
                                5881},              //curve check sum
                               {3,                 //GREATER than 100cca Curve
                                15,                //badcell cutoff 50CCA
                                1100,              //badcell high voltage limit
                                 800,              //badcell low voltage limit
                                1240,              //battery recharge voltage
                                1170,              //battery ok to test voltage
                                1275,              //battery full charge voltage
                                1340,              //battery surface charge voltage
                                75,                //conductance above recharge percent
                                255,               //conductance below recharge percent
                                118,               //temperature compensation percent
                                100,               //CCA factor percent
                                125,               //CA factor percent
                                130,               //MCA factor percent
                                100,               //JIS factor percent
                                56,                //DIN factor percent
                                100,               //SAE factor percent
                                63,                //IEC factor percent
                                92,                //EN factor percent
                                60,                //SOC percent cutoff
                                0,                 //SOC control 0
                                0,                 //SOC control 1
                                7,                 //pass percent for 8.00volts
                                7,                 //pass percent for 8.05volts
                                7,                 //pass percent for 8.10volts
                                8,                 //pass percent for 8.15volts
                                8,                 //pass percent for 8.20volts
                                8,                 //pass percent for 8.25volts
                                8,                 //pass percent for 8.30volts
                                8,                 //pass percent for 8.35volts
                                8,                 //pass percent for 8.40volts
                                9,                 //pass percent for 8.45volts
                                9,                 //pass percent for 8.50volts
                                9,                 //pass percent for 8.55volts
                                9,                 //pass percent for 8.60volts
                                9,                 //pass percent for 8.65volts
                                9,                 //pass percent for 8.70volts
                                10,                //pass percent for 8.75volts
                                10,                //pass percent for 8.80volts
                                10,                //pass percent for 8.85volts
                                10,                //pass percent for 8.90volts
                                10,                //pass percent for 8.95volts
                                10,                //pass percent for 9.00volts
                                11,                //pass percent for 9.05volts
                                11,                //pass percent for 9.10volts
                                11,                //pass percent for 9.15volts
                                11,                //pass percent for 9.20volts
                                11,                //pass percent for 9.25volts
                                11,                //pass percent for 9.30volts
                                12,                //pass percent for 9.35volts
                                12,                //pass percent for 9.40volts
                                12,                //pass percent for 9.45volts
                                12,                //pass percent for 9.50volts
                                12,                //pass percent for 9.55volts
                                12,                //pass percent for 9.60volts
                                13,                //pass percent for 9.65volts
                                13,                //pass percent for 9.70volts
                                13,                //pass percent for 9.75volts
                                13,                //pass percent for 9.80volts
                                13,                //pass percent for 9.85volts
                                13,                //pass percent for 9.90volts
                                14,                //pass percent for 9.95volts
                                14,                //pass percent for 10.00volts
                                14,                //pass percent for 10.05volts
                                14,                //pass percent for 10.10volts
                                14,                //pass percent for 10.15volts
                                14,                //pass percent for 10.20volts
                                15,                //pass percent for 10.25volts
                                15,                //pass percent for 10.30volts
                                15,                //pass percent for 10.35volts
                                15,                //pass percent for 10.40volts
                                15,                //pass percent for 10.45volts
                                15,                //pass percent for 10.50volts
                                16,                //pass percent for 10.55volts
                                16,                //pass percent for 10.60volts
                                16,                //pass percent for 10.65volts
                                16,                //pass percent for 10.70volts
                                16,                //pass percent for 10.75volts
                                16,                //pass percent for 10.80volts
                                17,                //pass percent for 10.85volts
                                17,                //pass percent for 10.90volts
                                17,                //pass percent for 10.95volts
                                255,               //pass percent for 11.00volts
                                255,               //pass percent for 11.05volts
                                255,               //pass percent for 11.10volts
                                255,               //pass percent for 11.15volts
                                255,               //pass percent for 11.20volts
                                255,               //pass percent for 11.25volts
                                255,               //pass percent for 11.30volts
                                255,               //pass percent for 11.35volts
                                35,                //pass percent for 11.40volts
                                38,                //pass percent for 11.45volts
                                40,                //pass percent for 11.50volts
                                43,                //pass percent for 11.55volts
                                45,                //pass percent for 11.60volts
                                48,                //pass percent for 11.65volts
                                50,                //pass percent for 11.70volts
                                53,                //pass percent for 11.75volts
                                55,                //pass percent for 11.80volts
                                58,                //pass percent for 11.85volts
                                60,                //pass percent for 11.90volts
                                63,                //pass percent for 11.95volts
                                65,                //pass percent for 12.00volts
                                68,                //pass percent for 12.05volts
                                70,                //pass percent for 12.10volts
                                73,                //pass percent for 12.15volts
                                75,                //pass percent for 12.20volts
                                75,                //pass percent for 12.25volts
                                75,                //pass percent for 12.30volts
                                75,                //pass percent for 12.35volts
                                75,                //pass percent for 12.40volts
                                75,                //pass percent for 12.45volts
                                75,                //pass percent for 12.50volts
                                75,                //pass percent for 12.55volts
                                75,                //pass percent for 12.60volts
                                75,                //pass percent for 12.65volts
                                75,                //pass percent for 12.70volts
                                75,                //pass percent for 12.75volts
                                0,                 //fail percent for 8.00volts
                                0,                 //fail percent for 8.05volts
                                0,                 //fail percent for 8.10volts
                                0,                 //fail percent for 8.15volts
                                0,                 //fail percent for 8.20volts
                                0,                 //fail percent for 8.25volts
                                0,                 //fail percent for 8.30volts
                                0,                 //fail percent for 8.35volts
                                0,                 //fail percent for 8.40volts
                                0,                 //fail percent for 8.45volts
                                0,                 //fail percent for 8.50volts
                                0,                 //fail percent for 8.55volts
                                0,                 //fail percent for 8.60volts
                                0,                 //fail percent for 8.65volts
                                0,                 //fail percent for 8.70volts
                                0,                 //fail percent for 8.75volts
                                0,                 //fail percent for 8.80volts
                                0,                 //fail percent for 8.85volts
                                0,                 //fail percent for 8.90volts
                                0,                 //fail percent for 8.95volts
                                0,                 //fail percent for 9.00volts
                                0,                 //fail percent for 9.05volts
                                0,                 //fail percent for 9.10volts
                                0,                 //fail percent for 9.15volts
                                0,                 //fail percent for 9.20volts
                                0,                 //fail percent for 9.25volts
                                0,                 //fail percent for 9.30volts
                                0,                 //fail percent for 9.35volts
                                0,                 //fail percent for 9.40volts
                                0,                 //fail percent for 9.45volts
                                0,                 //fail percent for 9.50volts
                                0,                 //fail percent for 9.55volts
                                0,                 //fail percent for 9.60volts
                                0,                 //fail percent for 9.65volts
                                0,                 //fail percent for 9.70volts
                                0,                 //fail percent for 9.75volts
                                0,                 //fail percent for 9.80volts
                                0,                 //fail percent for 9.85volts
                                0,                 //fail percent for 9.90volts
                                0,                 //fail percent for 9.95volts
                                0,                 //fail percent for 10.00volts
                                0,                 //fail percent for 10.05volts
                                0,                 //fail percent for 10.10volts
                                0,                 //fail percent for 10.15volts
                                0,                 //fail percent for 10.20volts
                                0,                 //fail percent for 10.25volts
                                0,                 //fail percent for 10.30volts
                                0,                 //fail percent for 10.35volts
                                0,                 //fail percent for 10.40volts
                                0,                 //fail percent for 10.45volts
                                0,                 //fail percent for 10.50volts
                                0,                 //fail percent for 10.55volts
                                0,                 //fail percent for 10.60volts
                                0,                 //fail percent for 10.65volts
                                0,                 //fail percent for 10.70volts
                                0,                 //fail percent for 10.75volts
                                0,                 //fail percent for 10.80volts
                                0,                 //fail percent for 10.85volts
                                0,                 //fail percent for 10.90volts
                                0,                 //fail percent for 10.95volts
                                0,                 //fail percent for 11.00volts
                                0,                 //fail percent for 11.05volts
                                0,                 //fail percent for 11.10volts
                                0,                 //fail percent for 11.15volts
                                0,                 //fail percent for 11.20volts
                                0,                 //fail percent for 11.25volts
                                0,                 //fail percent for 11.30volts
                                0,                 //fail percent for 11.35volts
                                0,                 //fail percent for 11.40volts
                                0,                 //fail percent for 11.45volts
                                0,                 //fail percent for 11.50volts
                                0,                 //fail percent for 11.55volts
                                0,                 //fail percent for 11.60volts
                                0,                 //fail percent for 11.65volts
                                0,                 //fail percent for 11.70volts
                                4,                 //fail percent for 11.75volts
                                8,                 //fail percent for 11.80volts
                                13,                //fail percent for 11.85volts
                                17,                //fail percent for 11.90volts
                                21,                //fail percent for 11.95volts
                                25,                //fail percent for 12.00volts
                                29,                //fail percent for 12.05volts
                                33,                //fail percent for 12.10volts
                                38,                //fail percent for 12.15volts
                                42,                //fail percent for 12.20volts
                                46,                //fail percent for 12.25volts
                                50,                //fail percent for 12.30volts
                                54,                //fail percent for 12.35volts
                                58,                //fail percent for 12.40volts
                                63,                //fail percent for 12.45volts
                                67,                //fail percent for 12.50volts
                                71,                //fail percent for 12.55volts
                                75,                //fail percent for 12.60volts
                                75,                //fail percent for 12.65volts
                                75,                //fail percent for 12.70volts
                                75,                //fail percent for 12.75volts
                                7557}             //curve check sum

					  };    

const rom _PartNumberStruct JISNumbers[JIS_NUM_ARRAY_SIZE] = {
                                    {"            ",       //JIS number 0 text NOT USED
                                     0,                   //rating factor
                                     2,                   //rating
                                     0,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                 //OK to test voltage
                                     0x6E},               //check sum
                                    {"12M3L-A",       //JIS number 1 text
                                     94,                  //rating factor
                                     35,                 //rating
                                     2,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0x5D},               //check sum
                                    {"12M5S-3B",       //JIS number 2 text
                                     94,                  //rating factor
                                     80,                  //rating
                                     2,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0xD5},               //check sum
                                    {"12M7A-3A",       //JIS number 3 text
                                     94,                  //rating factor
                                     90,                  //rating
                                     2,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0xBB},               //check sum
                                    {"CB4L-B",       //JIS number 4 text
                                     94,                  //rating factor
                                     80,                 //rating
                                     2,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0x70},               //check sum
                                    {"MTX7L-BS",       //JIS number 5 text
                                     94,                  //rating factor
                                     80,                 //rating
                                     2,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0xD1},               //check sum
                                    {"YB5L-B",       //JIS number 6 text
                                     94,                  //rating factor
                                     100,                 //rating
                                     3,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0x90},               //check sum
                                    {"YTX4L-BS",       //JIS number 6 text
                                     94,                  //rating factor
                                     50,                 //rating
                                     2,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0x90},               //check sum
                                    {"YTX7A-BS",       //JIS number 6 text
                                     94,                  //rating factor
                                     105,                 //rating
                                     3,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0x90},               //check sum
                                     {"YTX7L-BS",       //JIS number 6 text
                                     94,                  //rating factor
                                     100,                 //rating
                                     3,                   //Curve number
                                     0,                   //battery units CCA
                                     0,                   //rated voltage
                                     14,                  //OK to test voltage
                                     0x90},               //check sum                                    
};


