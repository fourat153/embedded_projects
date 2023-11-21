/* 
 * File:   timer1.h
 * Author: mm77
 *
 * Created on July 30, 2023, 10:17 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

/*section : includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_internal.h"
#include "../GPIO/hal_gpio.h"
/*section : macros definition*/
#define TIMER1_TIMER_MODE            0
#define TIMER1_COUNTER_MODE          1
#define TIMER1_ASYNC_COUNTER_MODE    1
#define TIMER1_SYNC_COUNTER_MODE     0
#define TIMER1_OSC_ENABLE            1
#define TIMER1_OSC_DISABEL           0
#define timer1_prescaler_div1     0
#define timer1_prescaler_div2    1
#define timer1_prescaler_div4    2
#define timer1_prescaler_div8    3
#define TIMER1_8BIT_REGISTER_MODE            0
#define TIMER1_16BIT_REGISTER_MODE           1
/*section : function macros*/
#define TIMER1_MODULE_ENABLE()                       (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                      (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()        (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_HW_ENABLE()         (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()        (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)        (T1CONbits.T1CKPS = _PRESCALER_)
/*source clocks timer1 osc mech internal and primary osc */
#define TIMER1_SYSTM_CLK_STATUS()        (T1CONbits.T1RUN = 1)

#define TIMER1_RW_REG_8BIT_MODE_ENABLE()        (T1CONbits.RD16  = 0 )
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()        (T1CONbits.RD16  = 1)


/*section : user define data types */
typedef struct 
{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void ( * TIMER1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif 
    uint16 timer1_preload_value ; 
    uint8 timer1_mode : 1 ;
    uint8 timer1_counter_mode : 1 ; 
    uint8 timer1_osc_cfg : 1 ;
    uint8 timer1_prescaler_value : 2 ;
    uint8 timer1_reg_wr_mode : 1;
    uint8 timer1_reserved : 2 ;
    
}timer1_t;

/*section : function prototypes */
std_ReturnType Timer1_init(const timer1_t *   timer) ; 
std_ReturnType Timer1_deinit(const timer1_t* timer) ; 
std_ReturnType Timer1_write_value(const  timer1_t * timer , uint16 value) ; 
std_ReturnType Timer1_read_value(const  timer1_t * timer , uint16 * value) ; 
#endif	/* TIMER1_H */

