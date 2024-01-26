/* 
 * File:   real_timeclock.h
 * Author: ahmed
 *
 * Created on January 26, 2024, 1:08 PM
 */

#ifndef REAL_TIMECLOCK_H
#define	REAL_TIMECLOCK_H
#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/i2c_master.h"
#include "../mcc_generated_files/examples/i2c_master_example.h"

typedef struct 
{
    uint16_t seconds ;
    uint16_t minutes ; 
    uint16_t  hours ; 
    
    uint16_t days ; 
    uint16_t months  ; 
    uint16_t years ; 
    
    
}real_time_clock_t;


real_time_clock_t get_Real_time_clock (void) ; 
#endif	/* REAL_TIMECLOCK_H */



