/********************************************************************************

Header file for the USI TWI Slave driver.

Created by Donald R. Blake
donblake at worldnet.att.net

Adjusted to read/write mode my Moritz Strübe <morty@gmx.net>

---------------------------------------------------------------------------------

Created from Atmel source files for Application Note AVR312: Using the USI Module
as an I2C slave.

This program is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

---------------------------------------------------------------------------------

Change Activity:

    Date       Description
   ------      -------------
  15 Mar 2007  Created.

********************************************************************************/



#ifndef _USI_TWI_SLAVE_H_
#define _USI_TWI_SLAVE_H_

#include <stdint.h>

#define USI_ADDRESS 24


/********************************************************************************

                                    includes

********************************************************************************/

#include <stdbool.h>


/********************************************************************************

                                   prototypes

********************************************************************************/

void    usiTwiSlaveInit( void );
void    usiTwiSlaveCB( uint8_t (*cbRecieve) (uint8_t len), uint8_t(*cbTransmit) (void));
bool    usiTwiDataInReceiveBuffer( void );

/********************************************************************************

                           driver buffer definitions

********************************************************************************/


#define TWI_RX_BUFFER_SIZE  ( 1 )


#define TWI_TX_BUFFER_SIZE ( 16 )


extern uint8_t usiTwiRxBuf[TWI_RX_BUFFER_SIZE];

extern uint8_t usiTwiTxBuf[TWI_TX_BUFFER_SIZE];


#endif  // ifndef _USI_TWI_SLAVE_H_
