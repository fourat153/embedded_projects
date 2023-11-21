/* 
 * File:   ecu_keybad.h
 * Author: mm77
 *
 * Created on June 26, 2023, 3:26 PM
 */

#ifndef ECU_KEYBAD_H
#define	ECU_KEYBAD_H
/*include section: */
#include"ecu_keypad_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
/*macro declarations */
#define ECU_KEYPAD_ROW 4 
#define ECU_KEYPAD_COLUMNS 4 
/*function macros*/ 



/*user define data type*/ 
typedef struct 
{
    pin_config_t keypad_row_pin[ECU_KEYPAD_ROW];
    pin_config_t keypad_col_pin[ECU_KEYPAD_COLUMNS];
}keypad_t;

/*function prototype*/
std_ReturnType keypad_initialize(const keypad_t * keypad_obj) ;  
std_ReturnType keypad_get_value (const  keypad_t * keypad_obj , uint8 * value) ;



#endif	/* ECU_KEYBAD_H */

