/* 
 * File:   hal_timer2.h
 * Author: mm77
 *
 * Created on July 31, 2023, 8:00 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*section : includes */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_interrupt_internal.h"
#include "../GPIO/hal_gpio.h"
/*section : macros definition*/
#define timer2_postscaler_div1     0
#define timer2_postscaler_div2     1
#define timer2_postscaler_div3     2
#define timer2_postscaler_div4     3
#define timer2_postscaler_div5     4
#define timer2_postscaler_div6     5
#define timer2_postscaler_div7     6
#define timer2_postscaler_div8     7
#define timer2_postscaler_div9     8
#define timer2_postscaler_div10     9
#define timer2_postscaler_div11     10
#define timer2_postscaler_div12     11
#define timer2_postscaler_div13     12
#define timer2_postscaler_div14     13
#define timer2_postscaler_div15     14
#define timer2_postscaler_div16     15

#define timer2_prescaler_div1      0
#define timer2_pretscaler_div4     1
#define timer2_prescaler_div16     2


/*section : function macros*/
#define TIMER2_MODULE_ENABLE()           (T2CONbits.TMR2ON = 1) 
#define TIMER2_MODULE_DISABLE()          (T2CONbits.TMR2ON = 0) 

#define TIMER2_PRESCALER_SELECT(_PRESCALER_)        (T2CONbits.T2CKPS = _PRESCALER_)
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)        ( T2CONbits.TOUTPS= _POSTSCALER_)


/*section : user define data types */
typedef struct 
{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void ( * TIMER2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif 
    uint8 timer2_preloaded_value; 
    uint8 timer2_postscaler_value : 4 ;
    uint8 timer2_prescaler_value : 2 ;
    uint8 timer1_reserved : 2 ;
}timer2_t;

/*section : function prototypes */
std_ReturnType Timer2_init(const timer2_t *   timer) ; 
std_ReturnType Timer2_deinit(const timer2_t* timer) ; 
std_ReturnType Timer2_write_value(const  timer2_t * timer , uint16 value) ; 
std_ReturnType Timer2_read_value(const  timer2_t * timer , uint16 * value) ; 

#endif	/* HAL_TIMER2_H */

