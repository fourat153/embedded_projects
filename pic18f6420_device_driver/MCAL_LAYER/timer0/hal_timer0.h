/* 
 * File:   hal_timer0.h
 * Author: mm77
 *
 * Created on July 29, 2023, 8:18 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*section : includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_internal.h"
#include "../GPIO/hal_gpio.h"
/*section : macros definition*/
#define TIMER0_PRESCALER_ENABLE_CFG            1
#define TIMER0_PRESCALER_DISABLE_CFG           0
#define TIMER0_RISING_EDGE_CFG            1
#define TIMER0_FALLING_EDGE_CFG           0
#define TIMER0_TIMER_MODE            1
#define TIMER0_COUNTER_MODE          0
#define TIMER0_8BIT_REGISTER_MODE            1
#define TIMER0_16BIT_REGISTER_MODE           0
/*section : functions macros definitions */
#define TIMER0_RISING_EDEGE_ENABLE()            (T0CONbits.T0PS1 = 0) 
#define TIMER0_FALLING_EDEGE_ENABLE()           (T0CONbits.T0PS1 = 1) 


#define TIMER0_PRESCALER_ENABLE()        (T0CONbits.PSA = 1)
#define TIMER0_PRESCALER_DISABLE()       (T0CONbits.PSA = 0)

#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()           (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()          (T0CONbits.T08BIT = 0)

#define TIMER0_MODULE_ENABLE()                       (T0CONbits.TMR0ON  = 1)
#define TIMER0_MODULE_DISABLE()                      (T0CONbits.TMR0ON  = 0)

/*section : user define data type */
typedef enum {
    timer0_prescaler_div2 = 0,
    timer0_prescaler_div4,
    timer0_prescaler_div8,
    timer0_prescaler_div16, 
    timer0_prescaler_div32,
    timer0_prescaler_div64, 
    timer0_prescaler_div128,
    timer0_prescaler_div256 
}Timer0_Prescaler_select_t;
typedef struct 
{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void ( * TIMER0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif 
    Timer0_Prescaler_select_t prescaler_value ;
    uint8 prescaler_enable : 1 ;
    uint16 timer0_preload_value ; 
    uint8 timer0_counter_edge : 1 ; 
    uint8 timer0_mode        : 1 ; 
    uint8 timer0_register_size : 1 ;
    uint8 timer0_reserved : 4 ;
}timer0_t;
/*section : function prototype*/
std_ReturnType Timer0_init(const timer0_t *   timer) ; 
std_ReturnType Timer0_deinit(const timer0_t * timer) ; 
std_ReturnType Timer0_write_value(const timer0_t * timer , uint16 value) ; 
std_ReturnType Timer0_read_value(const timer0_t * timer , uint16 * value) ; 
#endif	/* HAL_TIMER0_H */

