#include "eeprom.h"

void Eeprom_write_byte(i2c_address_t eeprom_adress , i2c_address_t address , uint8_t data) 
{
    I2C_Write1ByteRegister(eeprom_adress , address , data );
}
uint8_t Eeprom_read_byte (i2c_address_t eeprom_adress , i2c_address_t address) // we need to add a delay between write operation  
{
    uint8_t data  = 0 ;
    data = I2C_Read1ByteRegister(eeprom_adress , address) ; 
    return  data  ;
}
