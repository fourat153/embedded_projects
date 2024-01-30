#include "temp_sensor.h"

uint8_t Sensor_ReadTemp(i2c_address_t address_sensors )
{
    uint8_t data ; 
    data = I2C_Read1ByteRegister(address_sensors , 0x0);
    return data ; 
}
