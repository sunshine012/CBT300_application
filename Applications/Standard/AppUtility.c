/****************************************************************************
;
;  Copyright (c) Midtronics 2015
;
;     This module defines utility routines
;
****************************************************************************/
#include <stdlib.h>
#include "AppUtility.h"
#include "AppData.h"
#include "AppEEData.h"
#include "DrvEeprom_25AA320.h"

/****************************************************************************

   This function verifies the cal factors.

   Parameters Passed:   none
   Parameters Returned: 0 checksum valid, -1 checksum invalid

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   10-10-15    KC          Developed

****************************************************************************/
UINT8 VerifyCalFactors (void)
{
   UINT8 ii;
   UINT8 sum = 0;

   DrvEepromRead((UINT16)&EECalFactor, (UINT8 *)&CalFactor, sizeof(_CalFactorStruct));
   for(ii = 0; ii < sizeof(CalFactor)-1; ii++)
   {                                   
      sum += *((UINT8*)&CalFactor + ii);
   }

   if(sum != *((UINT8*)&CalFactor + ii))    
      return -1;                       //return -1 if invalid
   else
      return 0;
}

UINT8 CalFactorsCheckSum (void)
{
  	UINT8 ii;
   	UINT8 sum = 0;
    	for(ii = 0; ii < sizeof(CalFactor)-1; ii++)
   	{                                   
      		sum += *((UINT8*)&CalFactor + ii);   
   	}
   	return(sum);
}
/****************************************************************************

   Routine converts a long to a string.  The number to be
   converted and a pointer to the string must be passed.  The string must
   be large enough to hold the converted number plus the null character.
   The converted number is placed in the passed string.
   These 2 routines convert to base 10 or base 16.

   Parameters Passed:   long number to convert, pointer to string
   Parameters Returned: None

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   06-16-05    RJ          Developed

****************************************************************************/
CHAR* itoabase(UINT16 number, CHAR *string, UINT8 JustifySize, UINT8 Base)
{
   UINT16  ii;
   CHAR    *q;
   CHAR*   TempPTR = string;

   q = string + 6;

   *q = '\0';                          //be sure to terminate the string with
   do{
                                       //a NULL character
      ii = (number % Base) + '0';
      if(ii > '9')
         ii += ('A' - '0' - 10);
      *--q = ii;
   }while(number /= Base);

   for( ; (*string++ = *q++); )        //move the string to the left,
      ;                                //including the NULL character

   if(JustifySize)
      RightJustify(TempPTR, JustifySize);
   return TempPTR;
}

/****************************************************************************

   This routine converts a passed number into an ascii decimal string for display.

   Ex.
         Number passed 1207 with 2 decimal places

            Divide.quot = 1207 / 100 ---> 12
            Divide.rem  = 1207 % 100 ---> 07

         String built "12.07"

   Parameters Passed:   Value to convert, number of decimal places and pointer
                        to buffer for string storage
   Parameters Returned: None

   Notes:

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   06-16-00    RJ          Developed
   11-14-01    CS          Modified to add a "V" to the end of the string

****************************************************************************/
CHAR* FormatVoltage(UINT16 Value, CHAR* string)
{
   CHAR*    TempPTR;
   UINT16   Number;

   TempPTR = string;
   if(Value != 0)
   {
      Number = Value / 100;              //calculate the quotient
      itoabase(Number, string, 0, 10); //add whole number to left of decimal point
      while(*string != '\0')
         string++;                             //locate the NULL character
      *string++ =  '.';
      Number = Value % 100;            //calculate the remainder
      if(Number < 10)
         *string++ = '0';                   //add padding zero
      itoabase(Number, string, 0, 10); //add fractional number to right of decimal
      while(*string != '\0')
         string++;                     //locate the NULL character
   }
   else
   {
      *string++ = '-';                 //show --.--V for 0 volts
      *string++ = '-';
      *string++ = '.';
      *string++ = '-';
      *string++ = '-';
   }

/* 
   if(Status.Bit.ShowMP == FALSE)
      string--;
*/
   
//#ifndef MAX_PRECISION_OUTPUT
//   string--;                           //Backup one character, thus reducing precision
//#endif
                                       //from xx.01V to xx.1V
   *string++ =  'V';                   //add a "V"
   *string =  '\0';                    //add the NULL

   RightJustify(TempPTR, 6);
   return(TempPTR);
}

/****************************************************************************

   Routine right justifies the passed string in the number of bytes passed
   in "size".

   Ex.
      string "25" and size = 4

      returned string "  25" where two padding spaces were added so string is
      now 4 characters long.

      Warning: passed string must be large enough to hold the padded string
               or there is a possiblity of corrupting data

   Parameters Passed:   pointer to string and size of area
   Parameters Returned: None

   Revision History:
   Date        Initials    Reason
   ========    ========    ======
   06-16-00    RJ          Developed

****************************************************************************/
void RightJustify(CHAR* string, UINT8 size)
{
   CHAR* pEnd;
   INT8  ii = 0;

   pEnd = string + size;
   while(*(string + ii) != '\0')
      ii++;
   while(ii >= 0)
   {
      *pEnd-- = *(string + ii);        //shift string to right
      ii--;
   }
   while(pEnd >= string)
      *pEnd-- = ' ';                   //add padding spaces
}


