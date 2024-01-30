#include "../real_time_module/real_time.h"

static real_time_clock_t real_time; 
static uint8_t pack_real_time[17] ; 
real_time_clock_t get_Real_time_clock (void) 
{
    real_time.seconds = I2C_Read1ByteRegister( 0xD0, 0x0);  // D0 == 11010000  last bit is for read or write  send 0xD0 / 2 ITS A BUG  or INSTEAD  delete the shift to the left << 1 ib i2c api
    real_time.minutes = I2C_Read1ByteRegister(0xD0 , 0x1) ;
    real_time.hours = I2C_Read1ByteRegister(0xD0 , 0x2) ;
    
    real_time.days = I2C_Read1ByteRegister(0xD0 , 0x4) ;
    real_time.months  = I2C_Read1ByteRegister(0xD0 , 0x5) ;
     real_time.years  = I2C_Read1ByteRegister(0xD0 , 0x6) ;


    return real_time ;
}

void print_realtimeclock(void) 
{
    pack_real_time[0] =  (real_time.years >> 4 ) + '0';
    pack_real_time[1] =  (real_time.years & 0x0F) + '0';
     pack_real_time[2] =  '-';
    pack_real_time[3] =  (real_time.months >> 4 ) + '0';
    pack_real_time[4] =  (real_time.months& 0x0F) + '0';
     pack_real_time[5] =  '-';
    pack_real_time[6] =  (real_time.days >> 4 ) + '0';
     pack_real_time[7] =  (real_time.days & 0x0F) + '0';
     pack_real_time[8] =  ':';
    pack_real_time[9] =  (real_time.hours >> 4 ) + '0';
    pack_real_time[10] = (real_time.hours & 0x0F) + '0';
     pack_real_time[11] =  '-';
    pack_real_time[12] = ( real_time.minutes >> 4 ) + '0';
     pack_real_time[13] =  (real_time.minutes & 0x0F) + '0';
     pack_real_time[14] =  '-';
    pack_real_time[15] = (real_time.seconds >> 4 ) + '0';
    pack_real_time[16] =  (real_time.seconds & 0x0F) + '0';
    uart_logging(pack_real_time , 17) ; 
}