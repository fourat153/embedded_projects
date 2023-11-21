/* 
 * File:   ecu_led.h
 * Author: mm77
 *
 * Created on June 1, 2023, 9:09 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*section : includes*/
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" 
#include "ecu_led_cfg.h"
/*section : macros declaration */


/*section : macros function definition */


/*section : user define data types*/
typedef enum
{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct  
{
   uint8  port_name  : 4 ;               // 4 the bit for future  upgrade 
   uint8  pin : 3 ; 
   uint8  led_status : 1 ;
}led_t;
/*section : function prototype */
std_ReturnType led_initialize( const led_t* led) ; 
std_ReturnType led_turn_on(const led_t  * led) ; 
std_ReturnType led_turn_off(const led_t * led);
std_ReturnType led_turn_toggle (const led_t * led ); 

#endif	/* ECU_LED_H */

