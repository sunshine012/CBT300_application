/* $Id: c018i_e.c,v 1.5 2004/10/15 22:35:00 GrosbaJ Exp $ */
//#include "BIOSBSP.h"
/* Copyright (c)1999 Microchip Technology */
#include "DrvMDXP600.h"
/* MPLAB-C18 startup code, including initialized data */

/* external reference to the user's main routine */
extern void main (void);
extern unsigned char AppMain (unsigned char Data);
/* prototype for the startup function */
void _entry (void);
void _startup (void);
/* prototype for the initialized data setup */
void _do_cinit (void);

extern volatile near unsigned long short TBLPTR;
extern near unsigned FSR0;
#define RND 6

#ifdef USE_BOOT_LOADER
// The _entry code will (unfortunately) put a return right where these loader values
// need to be.  The only way around it is to hard-code a goto at address 0x4000
// that will go to the _startup routine.
#pragma romdata _loader_vals=APP_START_ADDRESS
//rom unsigned int _goto   = 0xEF15;	// We want to jump to 0x802A, 802A / 2 = 0x4015
rom unsigned int _goto   = (0xEF00 | ((APP_START_ADDRESS / 2) & 0x00FF));	// We want to jump to 0x802A, 802A / 2 = 0x4015
//rom unsigned int __strup = 0xF040;	// Low byte jump is after EF, high byte after F0.
rom unsigned int __strup = (0xF000 | ((APP_START_ADDRESS / 2) >> 8));	// Low byte jump is after EF, high byte after F0.
rom unsigned int Loader1 = 0x017E;	// 
rom unsigned int Loader2 = 0xA987;

#pragma romdata _code_ver=APP_CODE_VERSION
//#pragma romdata _code_ver=0x8010
rom unsigned int code_ver = 0;
rom unsigned int code_mon = 1;
rom unsigned int code_yr  = 7;
#pragma romdata

#else

#pragma code _entry_scn=0x0

void _entry (void)
{
_asm goto _startup _endasm
}
#endif

#ifdef USE_BOOT_LOADER
#pragma code _startup_scn=APP_START_SCN
#else
#pragma code _startup_scn=0x2A
#endif
void
_startup (void)
{
#ifndef USE_BOOT_LOADER
  _asm
    // Initialize the stack pointer
    lfsr 1, _stack
    lfsr 2, _stack

    clrf TBLPTRU, 0 // 1st silicon doesn't do this on POR

    _endasm 
#endif
    _do_cinit ();

loop:

  // Call the user's main routine
  _asm goto AppMain _endasm
  //main1(0x55);

  goto loop;
}                               /* end _startup() */

/* MPLAB-C18 initialized data memory support */
/* The linker will populate the _cinit table */
extern far rom struct
{
  unsigned short num_init;
  struct _init_entry
  {
    unsigned long from;
    unsigned long to;
    unsigned long size;
  }
  entries[];
}
_cinit;

#pragma code _cinit_scn
void
_do_cinit (void)
{
  /* we'll make the assumption in the following code that these statics
   * will be allocated into the same bank.
   */
  static short long prom;
  static unsigned short curr_byte;
  static unsigned short curr_entry;
  static short long data_ptr;

  // Initialized data...
  TBLPTR = (short long)&_cinit;
  _asm
    movlb data_ptr
    tblrdpostinc
    movf TABLAT, 0, 0
    movwf curr_entry, 1
    tblrdpostinc
    movf TABLAT, 0, 0
    movwf curr_entry+1, 1
  _endasm
    //while (curr_entry)
    //{
    test:
    _asm
     bnz 3
    tstfsz curr_entry, 1
    bra 1
    _endasm
    goto done;
      /* Count down so we only have to look up the data in _cinit
       * once.
       *
       * At this point we know that TBLPTR points to the top of the current
       * entry in _cinit, so we can just start reading the from, to, and
       * size values.
       */
      _asm
	/* read the source address */
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf prom, 1
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf prom+1, 1
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf prom+2, 1
	/* skip a byte since it's stored as a 32bit int */
	tblrdpostinc
	/* read the destination address directly into FSR0 */
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf FSR0L, 0
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf FSR0H, 0
	/* skip two bytes since it's stored as a 32bit int */
	tblrdpostinc
	tblrdpostinc
	/* read the destination address directly into FSR0 */
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf curr_byte, 1
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf curr_byte+1, 1
	/* skip two bytes since it's stored as a 32bit int */
	tblrdpostinc
	tblrdpostinc
      _endasm  
      //prom = data_ptr->from;
      //FSR0 = data_ptr->to;
      //curr_byte = (unsigned short) data_ptr->size;
      /* the table pointer now points to the next entry. Save it
       * off since we'll be using the table pointer to do the copying
       * for the entry.
       */
      data_ptr = TBLPTR;
      
      /* now assign the source address to the table pointer */
      TBLPTR = prom;

      /* do the copy loop */
      _asm
        // determine if we have any more bytes to copy
	movlb curr_byte
	movf curr_byte, 1, 1
copy_loop:
	bnz 2 // copy_one_byte
	movf curr_byte + 1, 1, 1
	bz 7 // done_copying

copy_one_byte:
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf POSTINC0, 0

	// decrement byte counter
	decf curr_byte, 1, 1
	bc -8 // copy_loop
        decf curr_byte + 1, 1, 1
	bra -7 // copy_one_byte

done_copying:

      _endasm
      /* restore the table pointer for the next entry */
      TBLPTR = data_ptr;
      /* next entry... */
      curr_entry--;
      goto test;
done:
;
}

