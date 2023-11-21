/* 
 * File:   mcal_interrupt_external.h
 * Author: mm77
 *
 * Created on July 18, 2023, 2:37 PM
 */

#ifndef MCAL_INTERRUPT_EXTERNAL_H
#define	MCAL_INTERRUPT_EXTERNAL_H
/*************includes***************/
#include "mcal_interrupt_cfg.h"
/*****macros***************/
//intx === extarnal interrupts
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define EXT_INT0_InterruptDisable()          (INTCONbits.INT0IE = 0 )
#define EXT_INT0_InterruptEnable()           (INTCONbits.INT0IE = 1 )
#define EXT_INT0_InterruptFlagClear()        (INTCONbits.INT0IF = 0 )
#define EXT_INT0_RisingEdgeSet()             (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdgeSet()            (INTCON2bits.INTEDG0 = 0)

#define EXT_INT1_InterruptDisable()          (INTCON3bits.INT1IE = 0 ) 
#define EXT_INT1_InterruptEnable()           (INTCON3bits.INT1IE = 1 )
#define EXT_INT1_InterruptFlagClear()        (INTCON3bits.INT1IF = 0 )
#define EXT_INT1_RisingEdgeSet()             (INTCON2bits.INTEDG1 = 1 )
#define EXT_INT1_FallingEdgeSet()            (INTCON2bits.INTEDG1 = 0 )

#define EXT_INT2_InterruptDisable()          (INTCON3bits.INT2IE = 0 )
#define EXT_INT2_InterruptEnable()           (INTCON3bits.INT2IE = 1 )
#define EXT_INT2_InterruptFlagClear()        (INTCON3bits.INT2IF = 0)
#define EXT_INT2_RisingEdgeSet()             (INTCON2bits.INTEDG2 = 1 )
#define EXT_INT2_FallingEdgeSet()            (INTCON2bits.INTEDG2 = 0 )
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 

#define EX_INT1_HighPriorityset()                (INTCON3bits.INT1IP =  1)
#define EX_INT1_lowPriorityset()                 (INTCON3bits.INT1IP =  0)

#define EX_INT2_HighPriorityset()                (INTCON3bits.INT2IP =  1)
#define EX_INT2_lowPriorityset()                (INTCON3bits.INT2IP =  0)
#endif
#endif
#if EXTERNAL_INTERRUPT_onchange_FEATURE_ENABLE  == INTERRUPT_FEATURE_ENABLE

#define EXT_RBx_InterruptDisable()             (INTCONbits.RBIE = 0 )
#define EXT_RBx_InterruptEnable()              (INTCONbits.RBIE = 1 )
#define EXT_RBx_InterruptFlagClear()           (INTCONbits.RBIF = 0 )

#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 

#define EX_RBx_HighPriorityset()                (INTCON2bits.RBIP =  1)
#define EX_RBx_LowPriorityset()                (INTCON2bits.RBIP =  0)

#endif
/*function macros*/ 
/*user define data types */
typedef enum {
    INERRUPT_FALLING_EDGE = 0, 
    INERRUPT_RISING_EDGE   
}interrupt_INTx_edge;

typedef enum {
    INERRUPT_EXTARNAL_INT0 = 0, 
    INERRUPT_EXTARNAL_INT1,
    INERRUPT_EXTARNAL_INT2
}interrupt_INTx_src;



typedef struct 
{
    void (* EXTERNAL_INTRRUPT_HANDLER)(void);  // callback to informe the a event happen 
    pin_config_t mcu_pin ; 
    interrupt_INTx_edge edge; 
    interrupt_INTx_src source; 
    interrupt_priority_cfg priority;
}Interrupt_INTx_t;


typedef struct 
{
    void (* EXTERNAL_INTRRUPT_HANDLER)(void);  // callback to informe the a event happen 
    pin_config_t mcu_pin ;  
    interrupt_priority_cfg priority;
}Interrupt_RBx_t;







/*function prototypes*/
std_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t * int_obj );
std_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t * int_obj );  // two types of int interrup and change on interrupt 

std_ReturnType Interrupt_RBTx_Init(const Interrupt_RBx_t * int_obj );
std_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_t * int_obj );



#endif	/* MCAL_INTERRUPT_EXTERNAL_H */

