#include "temp.h" 
uint8_t TempSensorRead(i2c_address_t TC_addr)
{
    uint8_t TC74_temp = 0 ; 
    TC74_temp = I2C_Read1ByteRegister(TC_addr , 0x00);
    return TC74_temp;
}
