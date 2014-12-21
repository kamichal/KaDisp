/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  I2C header file
 *
 */

#ifndef I2C_
#define I2C_

#include "usbstk5515.h"

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16 USBSTK5515_I2C_init ( );
Int16 USBSTK5515_I2C_close( );
Int16 USBSTK5515_I2C_read( Uint16 i2c_addr, Uint8* data, Uint16 len );
Int16 USBSTK5515_I2C_write( Uint16 i2c_addr, Uint8* data, Uint16 len );

#endif
