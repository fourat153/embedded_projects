#include "../real_time_module/real_time.h"
#include "real_time.h"
static real_time_clock_t real_time; 
real_time_clock_t get_Real_time_clock (void) 
{
    real_time.seconds = I2C_Read1ByteRegister( 0x68, 0x0);  // D0 == 11010000  last bit is for read or write  send 0xD0 / 2 ITS A BUG  
    return real_time ;
}
