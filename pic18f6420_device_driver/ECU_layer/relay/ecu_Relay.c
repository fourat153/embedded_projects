#include "ecu_relay.h"
std_ReturnType relay_initialize(const relay_t * relay) 
{
    std_ReturnType ret = E_OK ;
    if (NULL == relay)
    {
        ret = E_NOT_ok; 
    }
    else
    {
        pin_config_t  pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .logic = relay->relay_status
        , .direction = OUTPUT_DIRECTION };
        gpio_pin_intialize(&pin_obj);
    }
    return ret ;
};

std_ReturnType relay_turn_on (const relay_t * relay)
{

 std_ReturnType ret = E_OK ;
    if (NULL == relay)
    {
        ret = E_NOT_ok; 
    }
    else
    {
        pin_config_t  pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .logic = relay->relay_status
        , .direction = OUTPUT_DIRECTION };
        gpio_pin_wirte_logic(&pin_obj,HIGH);
    }
    return ret ;
};
std_ReturnType relay_turn_off(const relay_t * relay) 

{
    std_ReturnType ret = E_OK ;
   if (NULL == relay)
    {
        ret = E_NOT_ok; 
    }
    else
    {
        pin_config_t  pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .logic = relay->relay_status
        , .direction = OUTPUT_DIRECTION };
        gpio_pin_wirte_logic(&pin_obj,LOW);
    }
    return ret ;

}; 