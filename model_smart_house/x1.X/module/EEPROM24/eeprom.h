/* 
 * File:   eeprom.h
 * Author: mm77
 *
 * Created on September 5, 2023, 6:14 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H
#include "../../mcc_generated_files/examples/i2c_master_example.h"
void eeprom_24_writebyte (i2c_address_t eeprom_add , i2c_address_t byte_address , uint8_t Data );
uint8_t  eeprom_24_readbyte (i2c_address_t eeprom_add , i2c_address_t byte_address  );

#endif	/* EEPROM_H */

 