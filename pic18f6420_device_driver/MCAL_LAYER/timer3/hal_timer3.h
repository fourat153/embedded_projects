/* 
 * File:   hal_timer3.h
 * Author: mm77
 *
 * Created on July 31, 2023, 8:07 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*section : includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_internal.h"
#include "../GPIO/hal_gpio.h"
/*section : macros definition*/
#define TIMER3_TIMER_MODE            0
#define TIMER3_COUNTER_MODE          1
#define TIMER3_ASYNC_COUNTER_MODE    1
#define TIMER3_SYNC_COUNTER_MODE     0

#define timer3_prescaler_div1    0
#define timer3_prescaler_div2    1
#define timer3_prescaler_div4    2
#define timer3_prescaler_div8    3

#define TIMER3_8BIT_REGISTER_MODE            0
#define TIMER3_16BIT_REGISTER_MODE           1


/*section : function macros*/

#define TIMER3_MODULE_ENABLE()                       (T3CONbits.TMR3ON= 1)
#define TIMER3_MODULE_DISABLE()                      ( T3CONbits.TMR3ON= 0)

#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS=1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()        ( T3CONbits.T3SYNC= 0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_)        (T3CONbits.T3CKPS = _PRESCALER_)

#define TIMER3_RW_REG_8BIT_MODE_ENABLE()        (T3CONbits.RD16  = 0 )
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()        (T3CONbits.RD16  = 1)

/*section : user define data types */
typedef struct 
{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void ( * TIMER3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif 
    uint16 timer3_preload_value ; 
    uint8 timer3_mode : 1 ;
    uint8 timer3_counter_mode : 1 ; 
    uint8 timer3_prescaler_value : 2 ;
    uint8 timer3_reg_wr_mode : 1;
    uint8 timer3_reserved : 3;
    
}timer3_t;
/*section : function prototypes */
std_ReturnType Timer3_init(const timer3_t *   timer) ; 
std_ReturnType Timer3_deinit(const timer3_t* timer) ; 
std_ReturnType Timer3_write_value(const  timer3_t * timer , uint16 value) ; 
std_ReturnType Timer3_read_value(const  timer3_t * timer , uint16 * value) ; 

#endif	/* HAL_TIMER3_H */

