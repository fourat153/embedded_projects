#include "../ECU_layer/led/ecu_led.h"
std_ReturnType led_initialize( const led_t* led) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == led) 
    { 
        ret = E_NOT_ok ;
    }
    else       
    {
         pin_config_t pin_obj = {.port = led->port_name , .pin = led->pin , .direction = OUTPUT_DIRECTION,
         .logic = led->led_status} ;       
        gpio_pin_intialize(&pin_obj); 
    }
    return ret ; 
}
std_ReturnType led_turn_on(const led_t  * led) 
{
    std_ReturnType ret = E_OK; 
    if (NULL == led) 
    {
        ret = E_NOT_ok;
    }
    else 
    {
       pin_config_t pin_obj = {.port = led->port_name , .pin = led->pin , .direction = OUTPUT_DIRECTION,
         .logic = led->led_status} ;  
        gpio_pin_wirte_logic(&pin_obj, HIGH); 
    }
    
    
    return ret; 
}
std_ReturnType led_turn_off(const led_t * led)
{
    std_ReturnType ret = E_OK;
    if (NULL == led) 
    {
        ret = E_NOT_ok;
    }
    else 
    {
    pin_config_t pin_obj = {.port = led->port_name , .pin = led->pin , .direction = OUTPUT_DIRECTION,
         .logic = led->led_status} ;  
        gpio_pin_wirte_logic(&pin_obj , LOW); 
    }
    
    return ret ; 
}
std_ReturnType led_turn_toggle (const led_t * led )
{
    std_ReturnType ret = E_OK ;
    if (NULL == led )
    {
        ret = E_NOT_ok; 
    }
    else 
    {
        pin_config_t pin_obj = {.port = led->port_name , .pin = led->pin , .direction = OUTPUT_DIRECTION,
         .logic = led->led_status} ;  
        gpio_pin_toggle_logic(&pin_obj); 
        
    }
    return ret ; 
}