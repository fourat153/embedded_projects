#include "ecu_button.h"

std_ReturnType initialize_button (const button_t * button)
{
    std_ReturnType ret = E_OK;
    if (NULL == button )
    {
        ret = E_NOT_ok;
    }
    else
    {
        ret = gpio_pin_initialize_pin(&button->button_pin);
    }
    return ret ; 
}


std_ReturnType read_button_status ( const  button_t * button , button_stats_t *button_status )
{
    std_ReturnType ret = E_OK; 
    logic_t btn_logic_status = LOW ;
    if ((NULL == button) || (NULL == button_status))
    {
        ret = E_NOT_ok; 
    }
    else 
    {
     gpio_pin_read_logic(&(button->button_pin) , & btn_logic_status);
    {
        if (BUTTON_ACTIVE_HIGH == button->button_connection)
    {
            if(btn_logic_status ==  HIGH)
            {
            
                *button_status = BUTTON_PRESSED;
            
            }
            else
            {
                *button_status = BUTTON_RELEASED;
            
            }
    }
            else if (BUTTON_ACTIVE_LOW == button->button_connection)
    {
            if(btn_logic_status ==  HIGH)
            {
            
                *button_status = BUTTON_RELEASED;
                
            
            }
            else
            {
                *button_status = BUTTON_PRESSED;
            }  
           
    }
            else {}
               
    }
     ret = E_OK;
    }
    return ret ; 
}