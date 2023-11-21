/* 
 * File:   ecu_motor.h
 * Author: mm77
 *
 * Created on June 13, 2023, 10:49 AM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H
/*section : includes */
#include "ecu_motor_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
/*section : macros */
#define DC_MOTOR_STATUS_ON 0x01U 
#define DC_MOTOR_STATUS_OFF 0x00U
/*section : function macros */



/*section : user define data type*/


typedef struct{
    pin_config_t dc_motor[2] ; 
}dc_motor_t;


/*section : function prototype */
std_ReturnType dc_motor_intialize(const dc_motor_t * motor); 
std_ReturnType dc_motor_move_right (const dc_motor_t *motor) ; 
std_ReturnType dc_motor_move_left (const dc_motor_t * motor);
std_ReturnType dc_motor_stop  (const dc_motor_t * motor ) ;


#endif	/* ECU_MOTOR_H */

