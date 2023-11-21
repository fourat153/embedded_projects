/* 
 * File:   mcal_interrupt_manger.h
 * Author: mm77
 *
 * Created on July 18, 2023, 2:44 PM
 */

#ifndef MCAL_INTERRUPT_MANGER_H
#define	MCAL_INTERRUPT_MANGER_H

/*************includes***************/
#include "mcal_interrupt_cfg.h"
/*****macros***************/
/*function macros*/ 
/*user define data types */
/*function prototypes*/
void INT0_ISR(void) ;
void INT1_ISR(void) ;
void INT2_ISR(void) ;
void RB4_ISR(void) ;
void RB5_ISR(void) ;
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void  CCP2_ISR(void);
void  CCP1_ISR(void);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
void MSSP_I2C_ISR(void);
void  MSSP_I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANGER_H */

