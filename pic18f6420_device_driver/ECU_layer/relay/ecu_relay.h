/* 
 * File:   ecu_relay.h
 * Author: mm77
 *
 * Created on June 12, 2023, 2:35 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*section: includes*/
#include "ecu_relay_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" 
/*section : macros definition */
#define RELAY_ON_STATUS   0x01U 
#define RELAY_OFF_STATUS  0x00U 
/*section: macro functions definition */



/*section :user define data types*/
typedef struct {
    uint8 relay_port : 4 ;
    uint8 relay_pin : 3 ;
    uint8 relay_status : 1 ;
}relay_t;
/*section: function prototype*/
std_ReturnType relay_initialize(const relay_t * relay) ; 
std_ReturnType relay_turn_on (const relay_t * relay) ;
std_ReturnType relay_turn_off(const relay_t * relay) ; 



#endif	/* ECU_RELAY_H */

