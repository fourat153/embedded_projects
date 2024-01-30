/* 
 * File:   eeprom.h
 * Author: ahmed
 *
 * Created on January 28, 2024, 9:59 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H
#include "../../mini_project smart home .X/mcc_generated_files/mcc.h"
#include "../../mini_project smart home .X/mcc_generated_files/examples/i2c_master_example.h"
void Eeprom_write_byte(i2c_address_t eeprom_adress , i2c_address_t address , uint8_t data) ; 
uint8_t Eeprom_read_byte (i2c_address_t eeprom_adress , i2c_address_t address); 

#endif	/* EEPROM_H */

