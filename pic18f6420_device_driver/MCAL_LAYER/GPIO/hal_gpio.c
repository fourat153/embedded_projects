
/* 
 * File:   application.c
 * Author: ahmed_chammam
 *
 * Created on May 31, 2023, 1:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "hal_gpio.h"
volatile uint8 *TRIS_register[] = {&TRISA , &TRISB ,&TRISC, &TRISD ,&TRISE }; 
volatile uint8 *LAT_register[] = {&LATA , &LATB ,&LATC, &LATD ,&LATE }; 
volatile uint8 *PORT_register[] = {&PORTA , &PORTB ,&PORTC, &PORTD ,&PORTE };

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_initialize_pin(const pin_config_t * _pin_config )
{
    std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER -1 ) 
    {
        ret = E_NOT_ok; 
    }
    else{
    switch (_pin_config->direction )
    {
            case OUTPUT_DIRECTION : 
                CLEAR_BIT(*TRIS_register[_pin_config->port],_pin_config->pin) ;                 
                    break ;
            case INPUT_DIRECTION:
                SET_BIT(*TRIS_register[_pin_config->port] , _pin_config->pin) ;                    
                break; 
        default :
            ret = E_NOT_ok;                    
    }
    }
    return ret ; 
};
#endif
/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_get_direction_status (const pin_config_t * _pin_config , direction_t * direction_status)
{
    std_ReturnType ret = E_OK;
    if (( NULL == _pin_config) ||    (NULL==direction_status) || (_pin_config->pin > PORT_PIN_MAX_NUMBER -1) )
    {
        ret = E_NOT_ok;
    }
    else 
     {
        *direction_status = READ_BIT( *TRIS_register[_pin_config->port] ,  _pin_config->pin );  
     }
    return ret ;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE 
std_ReturnType gpio_pin_wirte_logic(const pin_config_t * _pin_config , logic_t  logic )
{
    std_ReturnType ret = E_OK ;
    if (( NULL ==_pin_config) ||(_pin_config->pin >PORT_PIN_MAX_NUMBER - 1))
    {
        ret = E_NOT_ok ;
    }
    else 
    {
        switch(logic){
            case LOW : 
                CLEAR_BIT(*LAT_register[_pin_config->port],_pin_config->pin);
                break;
            case HIGH :
                SET_BIT(*LAT_register[_pin_config->port],_pin_config->pin );
                break ;
            default  : 
            ret = E_NOT_ok;
        }
    }   
    return ret ;
}
#endif
/**
 * 
 * @param pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE 
std_ReturnType gpio_pin_read_logic (const pin_config_t * pin_config , logic_t * logic)
{
    std_ReturnType ret = E_OK ;
    if ((NULL == pin_config ) || (NULL == logic) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1))
    {
        ret = E_NOT_ok ;
    }
    else 
    {
        *logic = READ_BIT(*PORT_register[pin_config->port] , pin_config->pin);
      
    }
    return ret; 
}
#endif
std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config )
{
    std_ReturnType ret = E_OK;
    if((NULL == _pin_config)||(_pin_config->pin > PORT_PIN_MAX_NUMBER- 1))
    {
        ret = E_NOT_ok ; 
    }
    else
    {
        TOGGLE_BIT(*LAT_register[_pin_config->port], _pin_config->pin);
     
    }
    return ret ; 
}
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config) 
{
    std_ReturnType ret = E_OK;
    if ((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1 ))
    {
        ret = E_NOT_ok; 
    }
    else 
    {
        ret = gpio_pin_initialize_pin(_pin_config);
        ret = gpio_pin_wirte_logic(_pin_config, _pin_config->logic);
       
    }
    
    return ret; 
}
#endif

std_ReturnType gpio_port_initialize(port_index_t port , uint8  direction)
{
    std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1 ) 
    {
        ret = E_NOT_ok;
    }
    else 
    {
          *TRIS_register[port] = direction; 
    }
    return ret ;
}
std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 * direction ) 
{
    std_ReturnType ret = E_OK;
    if ((port > PORT_MAX_NUMBER - 1 ) || (NULL == direction))
    {
        ret = E_NOT_ok ; 
    }
    else 
    {
        *direction = *TRIS_register[port] ;
    }
    return ret ;
}
std_ReturnType gpio_port_wirte_logic(port_index_t port , logic_t  logic )
{
    std_ReturnType ret  = E_OK ;
    if ((port > PORT_MAX_NUMBER - 1 ))
    {
        ret = E_NOT_ok;
    }
    else 
    {
        *LAT_register[port] = logic ; 
    }
    
    return ret ; 
    
}
std_ReturnType gpio_port_read_logic(port_index_t port , logic_t * logic)
{
    std_ReturnType  ret = E_OK  ;
    if ((port > PORT_MAX_NUMBER - 1 ) || (NULL == logic )) 
    {
        ret = E_NOT_ok;
              
    }
    else 
    {
        *logic = *LAT_register[port];
    }
    return ret; 
}
std_ReturnType gpio_port_toggle_logic (port_index_t port )
{
    
     std_ReturnType  ret = E_OK  ;
      if (port > PORT_MAX_NUMBER - 1 ) 
    {
        ret = E_NOT_ok;
              
    }
    else 
    {
         *LAT_register[port] ^= PORTC_MASK;
    }
    return ret; 
}
