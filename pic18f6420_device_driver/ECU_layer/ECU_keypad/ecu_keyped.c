#include"ecu_keybad.h"
uint8 btn_values [ECU_KEYPAD_ROW][ECU_KEYPAD_COLUMNS] =
{
    {'7', '8' , '9' , '/'},
    {'4' , '5' , '6' ,'*'},
    {'1' , '2' , '3' ,'-'},
    {'#' , '0' , '=' ,'+' }
};
std_ReturnType keypad_initialize(const keypad_t * keypad_obj)   
{
    
    uint8 ROW_COUNTER = 0 ;
    uint8 COLUMN_COUNTER= 0 ;
    std_ReturnType ret = E_OK ; 
    if (NULL== keypad_obj) 
    {
        ret = E_NOT_ok; 
        
    }
    else 
    {
        for(ROW_COUNTER = 0  ; ROW_COUNTER <ECU_KEYPAD_ROW ; ROW_COUNTER++ )
        {
           ret =  gpio_pin_intialize(&(keypad_obj->keypad_row_pin[ROW_COUNTER]));
        }
         for(COLUMN_COUNTER = 0  ; COLUMN_COUNTER <ECU_KEYPAD_COLUMNS ; COLUMN_COUNTER++ )
        {
           ret =  gpio_pin_initialize_pin(&(keypad_obj->keypad_col_pin[COLUMN_COUNTER]));
        }
        
    }
    return ret ; 
}

std_ReturnType keypad_get_value (const  keypad_t * keypad_obj , uint8 * value) 
{
    uint8 ROW_COUNTER = 0 ;
    uint8 COLUMN_COUNTER= 0 ;
    uint8 counter = 0 ;
    uint8 logic = 0 ;
    std_ReturnType ret = E_OK ;
    if (NULL== keypad_obj  || NULL == value)  
    {
        ret = E_NOT_ok; 
        
    }
    else 
    {
        for (ROW_COUNTER = 0 ; ROW_COUNTER < ECU_KEYPAD_ROW ; ROW_COUNTER++)
        {
            for(counter = 0 ; counter < ECU_KEYPAD_ROW ; counter++) 
            {
                ret = gpio_pin_wirte_logic(&(keypad_obj->keypad_row_pin[counter]) , LOW);
            }
            gpio_pin_wirte_logic(&(keypad_obj->keypad_row_pin[ROW_COUNTER]) , HIGH) ;
            for (COLUMN_COUNTER = 0  ; COLUMN_COUNTER < ECU_KEYPAD_COLUMNS ; COLUMN_COUNTER++) 
            {
                ret = gpio_pin_read_logic(&(keypad_obj->keypad_col_pin[COLUMN_COUNTER]) , &logic) ;
                if (logic == HIGH) 
                {
                    *value = btn_values[ROW_COUNTER][COLUMN_COUNTER] ;
                }
            }
                
        }
        
         
         
         
    }
    
    return ret; 
}
