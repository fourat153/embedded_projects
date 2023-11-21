/* 
 * File:   mcal_interrupt_config_gen.h
 * Author: mm77
 *
 * Created on July 18, 2023, 4:09 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_GEN_H
#define	MCAL_INTERRUPT_CONFIG_GEN_H
/*************includes***************/
#define INTERRUPT_FEATURE_ENABLE                                       1U
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE                             INTERRUPT_FEATURE_ENABLE 
#define EXTERNAL_INTERRUPT_onchange_FEATURE_ENABLE                     INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE                         INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                                   INTERRUPT_FEATURE_ENABLE 
#define TIMER0_INTERRUPT_FEATURE_ENABLE                                INTERRUPT_FEATURE_ENABLE 
#define TIMER1_INTERRUPT_FEATURE_ENABLE                                INTERRUPT_FEATURE_ENABLE 
#define TIMER2_INTERRUPT_FEATURE_ENABLE                                INTERRUPT_FEATURE_ENABLE 
#define TIMER3_INTERRUPT_FEATURE_ENABLE                                INTERRUPT_FEATURE_ENABLE 
#define USART_TX_INTERRUPT_FEATURE_ENABLE                                INTERRUPT_FEATURE_ENABLE 
#define USART_RX_INTERRUPT_FEATURE_ENABLE                                INTERRUPT_FEATURE_ENABLE 
#define CCP1_INTERRUPT_FEATURE_ENBALE                                    INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENBALE                                    INTERRUPT_FEATURE_ENABLE
#define MSSP_I2C_INTERRUPT_FEATURE_ENBALE                                    INTERRUPT_FEATURE_ENABLE

/*****macros***************/


/*user define data types */
/*function prototypes*/


#endif	/* MCAL_INTERRUPT_CONFIG_GEN_H */

