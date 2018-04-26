/******************************************************************************
 *
 * Platform:      184-000385
 * Module:        Drivers
 * File:             SysDisplay.c
 *
 * Designed by:   King Chen
 *
 *
 * Description:
 *
 * 
 * References:
 *
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvPic18f67J10.h"
#include <stdio.h>
#include <string.h>
#include "DrvMdxP600.h"
#include "SysDisplay.h"
#include "DrvLCD_OPTO1140GG.h"
#include "SysFont6x8.h"
#include "AppData.h"
#include "DatDictStandard.h"
#include "DatFont12x16.h"
#include "DatFont6x16.h"
#include "DatDictAsian.h"
//#include "SysFont.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////

const rom CHAR UP_ARROW_8X8[8]={0x7C,0xDE,0xCE,0xC6,0xC6,0xCE,0xDE,0x7C}; //  up
const rom CHAR DOWN_ARROW_8X8[8]={0x7C,0xF6,0xE6,0xC6,0xC6,0xE6,0xF6,0x7C};  //  down
const rom CHAR ENTER_ARROW_8X8[8]={0x7C,0xDE,0x8E,0xDE,0xDE,0xC2,0xFE,0x7C};  //  enter

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Gobal functions.
//
////////////////////////////////////////////////////////////////////////////////

//
// Function:    
// 
// Parameters:  
// Return Value:
// 
// Description:
//  
// Revision History:
// Date        Initials    Reason
// ========    ========    ======
// 09/02/15    KC         Developed
//

void SysClear_Line(unsigned char Line)
{
	unsigned char SpaceBufer[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  	unsigned char i;
  	unsigned char Col=0;
	Line = (Line<<1)+1;
	for(i=0; i<20; i++)
	{
		Display_Graphic_6X16(Line,Col,SpaceBufer, DISPLAY_N);// BLANK  a line
		Col = Col +6;
	}
}
void SysClear_Line_S(unsigned char Line)
{
	unsigned char SpaceBufer[6]={0x00,0x00,0x00,0x00,0x00,0x00};
  	unsigned char i;
  	unsigned char Col=0;
	Line = Line+2;
	for(i=0; i<20; i++)
	{
		Display_Graphic_6X8(Line,Col, SpaceBufer, DISPLAY_N);// BLANK  a line
		Col = Col +6;
	}
}
    
void SysDisplayString_W(unsigned int DICTOffs, unsigned char Row, unsigned char byFlag)
{

    UINT8 byLen;
    UINT8 byLineLen;
    UINT8 i;
    UINT8 byLineCount;
    UINT8 byLineStart;
    UINT16 TempOffs;
    UINT16 TempDictSCOffs;
    UINT8   TempDictUS;	
    UINT8   TempFont[24];
    UINT16  Temp;
	
    SysClear_Line(Row);
    Row = (Row<<1) +1;
    byLen = 0;
    byLineCount = 0;
    byLineStart =0;
	
     if(AppData.LanguageId == LANGUANGE_CHINESE)
     {	
     		memcpypgm2ram(&TempDictSCOffs,(const rom char *)((DATA_PTR)&DictSCOffsets[DICTOffs]),2);
    		TempOffs = TempDictSCOffs/2;
    		while(1)
    		{	
			memcpypgm2ram(&TempDictSCOffs,(const rom char *)((DATA_PTR)&DictAsianStrings[TempOffs+byLen]),sizeof(WCHAR));
    			if(TempDictSCOffs ==0)
    				break;					
	 		if(TempDictSCOffs < 128)
	 			byLineCount = byLineCount+6;
	 		else
				byLineCount = byLineCount+12;
	 		byLen = byLen+1;
		       CLRWDT();
    		}
     	}
       else if(AppData.LanguageId == LANGUANGE_ENGLISH)
       {
     		memcpypgm2ram(&TempDictSCOffs,(const rom char*)&DictUsOffsets[DICTOffs],2);
    		TempOffs = TempDictSCOffs;             
    		while(1)
    		{
			memcpypgm2ram(&TempDictUS,(const rom char*)&DictStandardStrings[TempOffs+byLen],1);
    			if(TempDictUS ==0)
    				break;	
	 		byLineCount = byLineCount+6;
	 		byLen = byLen+1;
			 CLRWDT();
    		}			  
       }
	if(DISPLAY_C & byFlag)
		byLineStart =(120-byLineCount)/2;  // Cent    
	else if(DISPLAY_R & byFlag)
		byLineStart =120-byLineCount;  // Right
	else if(DISPLAY_L & byFlag)		
    		byLineStart = 0;
	
	byLen = 0;
     	if(AppData.LanguageId == LANGUANGE_CHINESE)
     	{
         while(1)
    	  {
    	  	
    	  	memcpypgm2ram(&TempDictSCOffs,(const rom char *)((DATA_PTR)&DictAsianStrings[TempOffs+byLen]),sizeof(WCHAR));
    		if(TempDictSCOffs ==0)
    			break;
		else if(TempDictSCOffs>127)
    		{	
    			TempDictSCOffs -=128;
    			memcpypgm2ram(TempFont,(const rom char *)((DATA_PTR)&Font12x16[TempDictSCOffs]),24);
			Display_Graphic_12X16(Row,byLineStart,TempFont);
			byLineStart = byLineStart+12;	
    		}
		else if(TempDictSCOffs<127)
		{
			TempDictSCOffs -= FONT6X16_CHAR_OFFSET;
			memcpypgm2ram(TempFont,(const rom char *)&Font6x16[TempDictSCOffs],12);
			Display_Graphic_6X16(Row,byLineStart,TempFont, DISPLAY_N);
			byLineStart = byLineStart+6;	
		}
			 	
		byLen = byLen+1;
	 	 CLRWDT();
    	   }	
	}
	else if(AppData.LanguageId == LANGUANGE_ENGLISH)
	{
         while(1)//(0 !=DictStandardStrings[TempOffs+byLen])
    	  {
    	  	memcpypgm2ram((void *)&TempDictUS,(const rom char *)&DictStandardStrings[TempOffs+byLen],1);
		if(TempDictUS ==0)
    			break;	
		else if(TempDictUS > (FONT6X16_CHAR_OFFSET-1))
		{	
			TempDictUS -=FONT6X16_CHAR_OFFSET;
			memcpypgm2ram((void *)TempFont,(const rom char *)&Font6x16[TempDictUS],12);
			Display_Graphic_6X16(Row,byLineStart,TempFont, DISPLAY_N);
			byLineStart = byLineStart+6;
		}
			 	
		byLen = byLen+1;
	 	CLRWDT();
    	   }

	}
}

void SysDisplayString(unsigned char *string, unsigned char row, unsigned char Mask)
{
  unsigned char ByLen;
  unsigned char ByColCount;
  unsigned char i;
  unsigned char Temp;
  unsigned char TempFontBuffer[ 12 ];

	ByLen = strlen((char *)string);
	if(0 == ByLen)
		return ;
	
	ByColCount = 0;

	row = (row<<1)+1;
	if(DISPLAY_C&Mask)
		ByColCount =(120-ByLen*6)>>1;  // Centre  
	else if(DISPLAY_R&Mask)
    		ByColCount =120-ByLen*6;       // Right
	else if(DISPLAY_N&Mask)
    		ByColCount =0;                 // Left
    		
	for(i=0; i<ByLen; i++)
	{
		Temp = string[i]-FONT6X16_CHAR_OFFSET;
		memcpypgm2ram((void *)TempFontBuffer,(const rom char *)&Font6x16[Temp],12);
		Display_Graphic_6X16(row,ByColCount,TempFontBuffer, Mask);		
		ByColCount = ByColCount+6;
	}
}

void DisplayString_S(const unsigned char *string, unsigned char row, unsigned char Mask)
{
  unsigned char ByLen;
  unsigned char ByColCount;
  unsigned char i;
  unsigned char Temp;
  unsigned char Buffer[ 8 ];

	//ByLen = strlen((char *)string);
	ByLen = 0;
	i = 0;
	while(string[i] != '\0')
	{
		ByLen++;
		i++;
	}
	
	ByColCount = 0;
	if(!ByLen)
	     return ;	
	//row = (row<<1)+1;
	row = row +2;
	if(DISPLAY_C&Mask)
		ByColCount =(120-ByLen*6)>>1;  // Centre  
	else if(DISPLAY_R&Mask)
		ByColCount =120-ByLen*6;          // Right
	else if(DISPLAY_N&Mask)
		ByColCount =0;                           // Normal	
	for(i=0; i<ByLen; i++)
	{
		Temp = string[i]-dFont6x8_CharacterOffset;
		memcpypgm2ram( Buffer, Font6x8[ Temp ], 6 );
		Buffer[ 6 ] = 0;
		Display_Graphic_6X8(row, ByColCount, Buffer, Mask);
		ByColCount = ByColCount+6;
	}
}



void AppControlStatus(unsigned char Mask)
{
	unsigned char TemperBufer[8];
  	if(CTRL_NONE == Mask)
  	{	
  		memset(TemperBufer,0X00,sizeof(TemperBufer));
        	Display_Graphic_8X8(4, LCD_SCREEN_WIDTH - 8, TemperBufer);
        	Display_Graphic_8X8(5, LCD_SCREEN_WIDTH - 8, TemperBufer);
        	Display_Graphic_8X8(6, LCD_SCREEN_WIDTH - 8, TemperBufer);
        	return;
	}
	// UP Menu
	if(CTRL_UP & Mask)
	{
		memcpypgm2ram( TemperBufer, UP_ARROW_8X8, 8 );
	}
	else
	{
		memset(TemperBufer,0X00,sizeof(TemperBufer));
	}
	Display_Graphic_8X8(4, LCD_SCREEN_WIDTH - 8, TemperBufer);
	// DOWN Menu
	if(CTRL_DOWN & Mask)
	{
		memcpypgm2ram( TemperBufer, DOWN_ARROW_8X8, 8 );
	}
	else
	{
		memset(TemperBufer,0X00,sizeof(TemperBufer));
	}
	Display_Graphic_8X8(5, LCD_SCREEN_WIDTH - 8, TemperBufer);
	// ENTER Menu
	if(CTRL_ENTER & Mask)
	{
		memcpypgm2ram( TemperBufer, ENTER_ARROW_8X8, 8 );
	}
	else
	{
		memset(TemperBufer,0X00,sizeof(TemperBufer));
	}	
	Display_Graphic_8X8(6, LCD_SCREEN_WIDTH - 8, TemperBufer);
}

void SysDisplayLogo128X8(UINT8 row,const UINT8 * DataBuffer)
{
		UINT8 j;
		XLCD_Address(row,0);
		for(j=128; j>0; j--)
		{
            		XLCD_Data(*DataBuffer);
            		DataBuffer++;
			CLRWDT();		
		}

}




