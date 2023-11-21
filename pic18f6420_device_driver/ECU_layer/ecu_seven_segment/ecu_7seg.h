/* 
 * File:   ecu_7seg.h
 * Author: mm77
 *
 * Created on June 16, 2023, 8:23 AM
 */

#ifndef ECU_7SEG_H
#define	ECU_7SEG_H

#include "../ecu_seven_segment/ecu_7seg_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
/*section : macros*/
#define SEGMENT_PIN0 0 
#define SEGMENT_PIN1 1 
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3 

/*section : function macros */
typedef enum 
{
    SEGMENT_COMMON_CATHODE,
    SEGMENT_COMMON_ANAODE                     
}segment_t; 

/*section : data type*/
typedef struct 
{
   pin_config_t segment_pins[4];
   segment_t segment_type ;
}segemnt_type_t ;

/*section : function prototype */ 
std_ReturnType seven_segment_initialize(const  segemnt_type_t * seg); 
std_ReturnType seven_segment_write_number(const segemnt_type_t *seg , uint8 number );
#endif	/* ECU_7SEG_H */

