#include "ecu_7seg.h"
std_ReturnType seven_segment_initialize(const  segemnt_type_t * seg) 
{
    std_ReturnType ret = E_OK ; 
    if (NULL == seg )
    {
        ret = E_NOT_ok; 
    }
    else
    {
        ret = gpio_pin_intialize(&(seg->segment_pins[0]));
        ret = gpio_pin_intialize(&(seg->segment_pins[1]));
        ret = gpio_pin_intialize(&(seg->segment_pins[2]));
        ret = gpio_pin_intialize(&(seg->segment_pins[3]));
        ret = E_OK;
    }
    
    return ret ; 
}


std_ReturnType seven_segment_write_number(const segemnt_type_t *seg , uint8 number )
{
     std_ReturnType ret = E_OK ; 
    if ((NULL == seg) || (number > 9)  )
    {
        
        ret = E_NOT_ok; 
    }
    else
    {   
        ret = gpio_pin_wirte_logic(&(seg->segment_pins[0]) , number & 0x01);
        ret = gpio_pin_wirte_logic(&(seg->segment_pins[1]) , (number >> 1) & 0x01);
        ret = gpio_pin_wirte_logic(&(seg->segment_pins[2]) , (number >> 2) & 0x01);
        ret = gpio_pin_wirte_logic(&(seg->segment_pins[3]) , (number >> 3) & 0x01);
        
    } 
    
    return ret ; 
}