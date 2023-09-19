/* 
 * File:   RealTimeClock.h
 * Author: mm77
 *
 * Created on September 4, 2023, 4:52 PM
 */

#ifndef REALTIMECLOCK_H
#define	REALTIMECLOCK_H
#include "../../mcc_generated_files/mcc.h"
#include "../../mcc_generated_files/examples/i2c_master_example.h"
#include "../../module/uartlogging/uartlogging.h"


typedef struct 
{
    uint8_t seconds ;
    uint8_t minute ; 
    uint8_t hours ;
    uint8_t days ; 
    uint8_t months; 
    uint8_t years ;
}RealaTimeClockDSI_t;
RealaTimeClockDSI_t realtimeclockDSI(void);

void print_realtimeclock(void);





#endif	/* REALTIMECLOCK_H */

