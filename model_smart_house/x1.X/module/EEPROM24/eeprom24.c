#include"eeprom.h"


void eeprom_24_writebyte (i2c_address_t eeprom_add , i2c_address_t byte_address , uint8_t Data )
{
    // eeprom addres t5arja men data sheet using jummper tech 
    I2C_Write1ByteRegister(eeprom_add , byte_address , Data ); 
}
uint8_t  eeprom_24_readbyte (i2c_address_t eeprom_add , i2c_address_t byte_address  )
{
    uint8_t value = 0 ; 
    
    value = I2C_Read1ByteRegister(eeprom_add , byte_address);
    return value ; 
}
