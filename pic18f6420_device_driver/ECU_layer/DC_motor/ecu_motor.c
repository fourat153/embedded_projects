#include"ecu_motor.h"
static pin_config_t pin_obj1 ; 
static pin_config_t pin_obj2 ; 
std_ReturnType dc_motor_intialize(const dc_motor_t * motor)
{
    std_ReturnType ret = E_OK; 
    if (NULL == motor) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
   
    
    gpio_pin_intialize(&(motor->dc_motor[0]));
    gpio_pin_intialize(&(motor->dc_motor[1]));
    }
   return ret ;      
}
   
     
    
std_ReturnType dc_motor_move_right (const dc_motor_t *motor) 
{

   std_ReturnType ret = E_OK; 
    if (NULL == motor) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        gpio_pin_wirte_logic(&(motor->dc_motor[0]) , HIGH);
        gpio_pin_wirte_logic(&(motor->dc_motor[1]), LOW) ;
    }
   return ret ;   

}; 
std_ReturnType dc_motor_move_left (const dc_motor_t * motor)
{
    
    std_ReturnType ret = E_OK; 
    if (NULL == motor) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        gpio_pin_wirte_logic(&(motor->dc_motor[0]), LOW);
        gpio_pin_wirte_logic(&(motor->dc_motor[1]) , HIGH) ;
    }
   return ret ;   
    
    
};
std_ReturnType dc_motor_stop  (const dc_motor_t * motor )
{

   std_ReturnType ret = E_OK; 
    if (NULL == motor) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        gpio_pin_wirte_logic(&(motor->dc_motor[0]) , LOW);
        gpio_pin_wirte_logic(&(motor->dc_motor[1]), LOW) ;
    }
   return ret ;   


};
