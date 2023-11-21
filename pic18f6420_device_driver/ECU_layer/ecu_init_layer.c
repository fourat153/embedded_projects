#include "ecu_init_layer.h"

keypad_t key_pad_obj = {
  .keypad_row_pin[0].direction = OUTPUT_DIRECTION  ,
  .keypad_row_pin[0].logic = LOW,
  .keypad_row_pin[0].port = PORTC_INDEX,
  .keypad_row_pin[0].pin = PIN0 , 
  
  .keypad_row_pin[1].direction = OUTPUT_DIRECTION  ,
  .keypad_row_pin[1].logic = LOW,
  .keypad_row_pin[1].port = PORTC_INDEX,
  .keypad_row_pin[1].pin = PIN1 , 
  
  .keypad_row_pin[2].direction = OUTPUT_DIRECTION  ,
  .keypad_row_pin[2].logic = LOW,
  .keypad_row_pin[2].port = PORTC_INDEX,
  .keypad_row_pin[2].pin = PIN2 , 
  
  .keypad_row_pin[3].direction = OUTPUT_DIRECTION  ,
  .keypad_row_pin[3].logic = LOW,
  .keypad_row_pin[3].port = PORTC_INDEX,
  .keypad_row_pin[3].pin = PIN3 , 
    
   
  .keypad_col_pin[0].direction = INPUT_DIRECTION  ,
  .keypad_col_pin[0].logic = LOW,
  .keypad_col_pin[0].port = PORTC_INDEX,
  .keypad_col_pin[0].pin = PIN4 , 
  
  .keypad_col_pin[1].direction = INPUT_DIRECTION  ,
  .keypad_col_pin[1].logic = LOW,
  .keypad_col_pin[1].port = PORTC_INDEX,
  .keypad_col_pin[1].pin = PIN5 , 
  
  .keypad_col_pin[2].direction = INPUT_DIRECTION ,
  .keypad_col_pin[2].logic = LOW,
  .keypad_col_pin[2].port = PORTC_INDEX,
  .keypad_col_pin[2].pin = PIN6 , 
  
  .keypad_col_pin[3].direction = INPUT_DIRECTION  ,
  .keypad_col_pin[3].logic = LOW,
  .keypad_col_pin[3].port = PORTC_INDEX,
  .keypad_col_pin[3].pin = PIN7 , 
    
};
void ecu_layer_intialize(void)
{
    std_ReturnType ret = E_NOT_ok;
    ret =  keypad_initialize(&key_pad_obj);
};