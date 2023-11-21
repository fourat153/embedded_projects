/* 
 * File:   application.h
 * Author: mm77
 *
 * Created on June 1, 2023, 9:23 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "../ECU_layer/ecu_init_layer.h"
#include "../MCAL_LAYER/Interrupt/mcal_interrupt_external.h"
#include "ADC/hal_adc.h"
#include "timer0/hal_timer0.h"
#include "timer1/timer1.h"
#include "timer2/hal_timer2.h"
#include "ccp/hal_ccp.h"
#include "UART/hal_usart.h"
#include "i2c/i2c.h"
void application_intialize(void);
#define _XTAL_FREQ 8000000UL // ocilitor
extern keypad_t key_pad_obj;
extern lcd_8bits_t lcd2 ; 
extern lcd_4bits_t lcd1 ;
#endif	/* APPLICATION_H */

