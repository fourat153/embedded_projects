#include "../RealTimeClock/RealTimeClock.h"
RealaTimeClockDSI_t realtimeclock_obj ;
static  uint8_t RealaTimeClockDSI_pack[12];
RealaTimeClockDSI_t realtimeclockDSI(void) 
{
    realtimeclock_obj.seconds = I2C_Read1ByteRegister( 0xD0 , 0x00);
    realtimeclock_obj.minute = I2C_Read1ByteRegister( 0xD0 , 0x01);
    realtimeclock_obj.days = I2C_Read1ByteRegister( 0xD0 , 0x02);
    realtimeclock_obj.days = I2C_Read1ByteRegister( 0xD0 , 0x04);
    realtimeclock_obj.months = I2C_Read1ByteRegister( 0xD0 , 0x5);
    realtimeclock_obj.years= I2C_Read1ByteRegister( 0xD0 , 0x06);
    
    return realtimeclock_obj;
}
void print_realtimeclock(void)
{
    RealaTimeClockDSI_pack[0] = ((realtimeclock_obj.days >> 4 )  + 0x30 ) ; //turn it to char
    RealaTimeClockDSI_pack[1] = ((realtimeclock_obj.days & 0x0F ) + 0x30 );
    RealaTimeClockDSI_pack[2] = ':' ; 
    RealaTimeClockDSI_pack[3] = ((realtimeclock_obj.months >> 4 )  + 0x30 ) ; //turn it to char
    RealaTimeClockDSI_pack[4] = ((realtimeclock_obj.months& 0x0F ) + 0x30 );
    RealaTimeClockDSI_pack[5] =  ':'; 
    RealaTimeClockDSI_pack[6] = ((realtimeclock_obj.years >> 4 )  + 0x30 ) ; //turn it to char
    RealaTimeClockDSI_pack[7] = ((realtimeclock_obj.years & 0x0F ) + 0x30 );
    RealaTimeClockDSI_pack[8] = '\r';

    uart_loggingDebugData(RealaTimeClockDSI_pack , 9 );
    uart_loggingDebugData("Data : ", 7 );
                     
}