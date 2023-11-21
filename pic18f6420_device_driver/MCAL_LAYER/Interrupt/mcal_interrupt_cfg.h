/* 
 * File:   mcal_interrupt_cfg.h
 * Author: mm77
 *
 * Created on July 18, 2023, 2:44 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/*************includes***************/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_config_gen.h" // generate the behaviour of the interrupt priority on/off
#include "../GPIO/hal_gpio.h"
/*****macros***************/
#define INTERRUPT_ENABEL 1 
#define INTERRUPT_DESAIBLE 0 
#define INTERRUPT_OCCUR  1 
#define INTERRUPT_NOT_OCCUR 0 
#define INTERRUPT_PRIORITY_ENABLE 1 
#define INTERRUPT_PRIORITY_DESAIBLE 0 
/*function macros*/ 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_PriorityLevelsEnables() (RCONbits.IPEN = 1 )
#define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0 )

#define INTERRUPT_GlobalInterrupthighEnable() (INTCONbits.GIEH = 1 )
#define INTERRUPT_GlobalInterrupthighDisable() (INTCONbits.GIEH = 0 )

#define INTERRUPT_GlobalInterruptlowEnable() (INTCONbits.GIEL = 1 )
#define INTERRUPT_GlobalInterruptlowDisable() (INTCONbits.GIEL = 0 )
#else
// no interrupt priority
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1 )
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0 )
 
#define INTERRUPT_PeripheralsInterruptEnable() (INTCONbits.PEIE = 1 )
#define INTERRUPT_PeripheralsInterruptDisable() (INTCONbits.PEIE = 0 )
#endif

/*user define data types */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0 ,  
    INTERRUPT_HIGH_PRIORITY 
}interrupt_priority_cfg;


/*function prototypes*/

#endif	/* MCAL_INTERRUPT_CFG_H */

