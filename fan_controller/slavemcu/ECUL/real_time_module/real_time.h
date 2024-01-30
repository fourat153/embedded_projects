/* 
 * File:   real_timeclock.h
 * Author: ahmed
 *
 * Created on January 26, 2024, 1:08 PM
 */

#ifndef REAL_TIMECLOCK_H
#define	REAL_TIMECLOCK_H
#include "../../mcc_generated_files/mcc.h"
#include "../../mcc_generated_files/examples/i2c_master_example.h"
#include "../uart_logging/uart_logging.h"

typedef struct 
{
    uint8_t seconds ;
    uint8_t minutes ; 
    uint8_t  hours ; 
    
    uint8_t days ; 
    uint8_t months  ; 
    uint8_t years ; 
    
    
}real_time_clock_t;


real_time_clock_t get_Real_time_clock (void) ; 
void print_realtimeclock(void);
#endif	/* REAL_TIMECLOCK_H */



