@REM  CBT-300 Build.bat - A Batch script that will build the CBT-350
@REM  08-31-2015    KC    Developed
@REM  01-30-2018    CH    Modify, support Bootloader downloading and update
@REM

color 1F

@ECHO OFF
SET COMP="C:\MCC18\bin\mcc18.exe"
SET LINKR="C:\MCC18\bin\mplink.exe"
SET LIBR="C:\MCC18\lib"
SET HFILES="C:\MCC18\h"
SET MP2HEX="C:\MCC18\bin\mp2hex.exe"

SET str=%echo %%~dp0%
SET PROJECT_DIR=%str:~0,-1%
SET LNKFILE="%PROJECT_DIR%\Applications\Standard\18f67j10i_e_hex.lkr"
SET HEXMATE="%PROJECT_DIR%\hexmate.exe"
SET OBJCOPY="%PROJECT_DIR%\objcopy.exe"
SET OUTPUT_DIR="%PROJECT_DIR%\Output_files"

SET PROCESSOR=-p=18F67J10
SET COMP_ARG_OPT=--extended -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa- -nw=2060
SET DEFINES=-DUSE_BOOT_LOADER


SET APP_SRC_DIR="%PROJECT_DIR%\Applications\Standard"
SET DATA_SRC_DIR="%PROJECT_DIR%\Data\Standard"
SET DRV_SRC_DIR="%PROJECT_DIR%\Drivers\Standard"
SET SYS_SRC_DIR="%PROJECT_DIR%\System\Standard"

SET APP_OBJ_DIR="%PROJECT_DIR%\Applications\Standard\object_files"
SET DATA_OBJ_DIR="%PROJECT_DIR%\Data\Standard\object_files"
SET DRV_OBJ_DIR="%PROJECT_DIR%\Drivers\Standard\object_files"
SET SYS_OBJ_DIR="%PROJECT_DIR%\System\Standard\object_files"


SET APP_SECRECT_DIR="%PROJECT_DIR%\Applications\Standard\secret_object_files"
SET DATA_SECRECT_DIR="%PROJECT_DIR%\Data\Standard\secret_object_files"
SET DRV_SECRECT_DIR="%PROJECT_DIR%\Drivers\Standard\secret_object_files"
SET SYS_SECRECT_DIR="%PROJECT_DIR%\System\Standard\secret_object_files"

SET MAPFILE= "CBT300TesterAppHex.map"
SET COFFILE= "CBT300TesterAppHex.cof"
SET S19FILE= "CBT300TesterAppHex.s19"
SET HEXFILE= "CBT300TesterAppHex.hex"
SET FIRMWARE="192-129999A Firmware"
SET EEPROM=  "192-139999A EEProm"
SET FIRMWARE_UPDATE=FIRM999A
SET EEPROM_UPDATE=EEPM999A

SET APPFILES=c018_e AppMain SelfTest AppCurvePN AppUtility AppStates AppData AppError AppCalibrat AppStartUp
SET APPFILES=%APPFILES% AppBluetooth AppBattest AppBatQuest AppEEData 

SET DRVFILES=DrvMdxP600 DrvLoad DrvConfigBoard DrvAdc_18F67J10 DrvKey DrvInt_18F67J10
SET DRVFILES=%DRVFILES% DrvTimer_18F67J10 DrvUsart_18F67J10 DrvLCD_OPTO1140GG DrvCca
SET DRVFILES=%DRVFILES% DrvPan1026  DrvSsp_18F67J10 DrvEeprom_25AA320

SET SYSFILES=SysFont6x8 SysDisplay  SysVoltage SysGraphic SysBluetooth SysCalibrate

SET DATAFILES=DatDictAsian DatDictStandard DatFont12x16 DatFont6x16 

:compile

CD %OUTPUT_DIR%
@ECHO Delete the hex output file
del *.hex

@ECHO Delete the s19 output file
del *.s19

@ECHO Delete the cof output file
del *.cof

@ECHO Delete the map output file
del *.map

@ECHO Delete the error files
cd %APP_SRC_DIR%
del *.err
cd %DRV_SRC_DIR%
del *.err
CD %SYS_SRC_DIR%
del *.err
CD %DAT_SRC_DIR%
del *.err

IF "%1"=="link" goto Link 

@ECHO Delete the application object file
CD %APP_OBJ_DIR%
FOR %%x in (%APPFILES%) DO del %%x.o

@ECHO Delete the driver object file
CD %DRV_OBJ_DIR%
FOR %%x in (%DRVFILES%) DO del %%x.o

@ECHO Delete the driver object file
CD %SYS_OBJ_DIR%
FOR %%x in (%SYSFILES%) DO del %%x.o

@ECHO Delete the Data object file
CD %DATA_OBJ_DIR%
FOR %%x in (%DATAFILES%) DO del %%x.o

IF "%1"=="clean" goto EXIT 

@echo Compiling System Files ...
@ECHO ON
CD %SYS_SRC_DIR%
FOR %%x in (%SYSFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_SRC_DIR% -I%DATA_SRC_DIR% -I%DRV_SRC_DIR% -I%SYS_SRC_DIR% %%x.c -fo=%SYS_OBJ_DIR%\%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS

@echo Compiling Driver Files ...
@ECHO ON
CD %DRV_SRC_DIR%
FOR %%x in (%DRVFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_SRC_DIR% -I%DATA_SRC_DIR% -I%DRV_SRC_DIR% -I%SYS_SRC_DIR% %%x.c -fo=%DRV_OBJ_DIR%\%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS

@echo Compiling Data Files ...
@ECHO ON
CD %DATA_SRC_DIR%
FOR %%x in (%DATAFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_SRC_DIR% -I%DATA_SRC_DIR% -I%DRV_SRC_DIR% -I%SYS_SRC_DIR% %%x.c -fo=%DATA_OBJ_DIR%\%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS

@echo Compiling Application Files ...
@ECHO ON
CD %APP_SRC_DIR%
FOR %%x in (%APPFILES%) DO %COMP% %PROCESSOR% -I%HFILES% -I%APP_SRC_DIR% -I%DATA_SRC_DIR% -I%DRV_SRC_DIR% -I%SYS_SRC_DIR% %%x.c -fo=%APP_OBJ_DIR%\%%x.o %DEFINES% %COMP_ARG_OPT%
@ECHO OFF
if exist *.err goto COMP_ERRS


CD %OUTPUT_DIR%
@ECHO Link Order
@REM Link Order
SET LINKFILES=c018_e.o AppMain.o SelfTest.o AppCurvePN.o AppUtility.o AppStates.o AppData.o AppError.o
SET LINKFILES=%LINKFILES% AppCalibrat.o AppStartUp.o AppBluetooth.o AppBattest.o AppBatQuest.o AppEEData.o
SET LINKFILES=%LINKFILES% DrvCca.o DrvMdxP600.o DrvLoad.o DrvConfigBoard.o DrvAdc_18F67J10.o DrvKey.o 
SET LINKFILES=%LINKFILES% DrvTimer_18F67J10.o DrvUsart_18F67J10.o DrvLCD_OPTO1140GG.o DrvSsp_18F67J10.o 
SET LINKFILES=%LINKFILES% DrvEeprom_25AA320.o DrvPan1026.o DrvInt_18F67J10.o
SET LINKFILES=%LINKFILES% SysBluetooth.o SysVoltage.o SysGraphic.o SysFont6x8.o SysDisplay.o SysCalibrate.o
SET LINKFILES=%LINKFILES% DatDictAsian.o DatDictStandard.o DatFont12x16.o DatFont6x16.o


cd %OUTPUT_DIR%
@echo -------------------- Creating the Firmware--------------------
@ECHO Linking the files...
@ECHO
%LINKR% %LNKFILE% %LINKFILES% /l%APP_SECRECT_DIR% /l%DRV_SECRECT_DIR% /l%SYS_SECRECT_DIR% /l%DATA_SECRECT_DIR% /l%APP_OBJ_DIR% /l%DRV_OBJ_DIR% /l%SYS_OBJ_DIR% /l%DATA_OBJ_DIR% /l%LIBR% /m%MAPFILE% /o%COFFILE%  /w /d /x
@ECHO OFF

if NOT EXIST %COFFILE% goto LINK_ERR

@ECHO Create coff files
copy %COFFILE% %FIRMWARE%.COF

@ECHO Create hex files for uP Flash
%MP2HEX% /a INHX32 /r 0x008000-0x01FBFF /q %FIRMWARE%.COF

@ECHO Add checksum to uP Flash
%HEXMATE% %FIRMWARE%.HEX -CK=0x8000-0x1FBFD@0x1FBFEw2 -FILL=FF@0x8000-0x1FBFD -O%FIRMWARE%.HEX

@ECHO Create S19 Mapple files for uP Flash
%OBJCOPY% -O srec %FIRMWARE%.HEX %FIRMWARE%.s19

:://////////////////////////////////////////////////////////////////////////////
@ECHO -------------------- Creating the CBT300 EEPROM ----------------------
@ECHO Linking the files...
@ECHO OFF
%LINKR% %LNKFILE% %LINKFILES% /l%APP_SECRECT_DIR% /l%DRV_SECRECT_DIR% /l%SYS_SECRECT_DIR% /l%DATA_SECRECT_DIR% /l%APP_OBJ_DIR% /l%DRV_OBJ_DIR% /l%SYS_OBJ_DIR% /l%DATA_OBJ_DIR% /l%LIBR% /m%MAPFILE% /o%EEPROM%.COF /w /d /x
@ECHO OFF

if NOT EXIST %EEPROM%.COF goto LINK_ERR

@ECHO Create coff files
copy %EEPROM%.COF %EEPROM_UPDATE%.COF

@ECHO Create hex files for CBT300 EEProm
%MP2HEX% /a INHX32 /r 0x600010-0x600FFF /q %EEPROM%.COF

@ECHO Create S19 Mapple files for CBT300 EEProm
%OBJCOPY% -O srec %EEPROM%.HEX %EEPROM%.s19

@ECHO Create eeprom update files
@REM For update file all EE memory except Cal factors
%MP2HEX% /a INHX32 /r 0x600060-0x600FFF /q %EEPROM_UPDATE%.COF

@ECHO Create Update File for CBT300 EEProm
%OBJCOPY% -O srec %EEPROM_UPDATE%.HEX %EEPROM_UPDATE%.dx6

@ECHO --------------- Creating Firmware Files ----------------
@ECHO Create DX6 Update files for uP Flash
%OBJCOPY% -O srec %FIRMWARE%.HEX %FIRMWARE_UPDATE%.dx6

goto EXIT

:COMP_ERRS
@ECHO There are Compile errors
color 4F
FOR %%x in (*.err) DO ECHO %%x

goto EXIT

:LINK_ERR
color 4F
echo Link Failed
goto EXIT

:EXIT
cd %PROJECT_DIR%
echo.
pause

