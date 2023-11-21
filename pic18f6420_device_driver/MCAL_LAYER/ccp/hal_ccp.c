#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENBALE  == INTERRUPT_FEATURE_ENABLE
static void (*CCP1_InterruptHandler)(void) = NULL;
#endif

#if CCP2_INTERRUPT_FEATURE_ENBALE  == INTERRUPT_FEATURE_ENABLE
static void (*CCP2_InterruptHandler)(void) = NULL;
#endif

static void CCP_capture_mode_timer_select(const  ccp_t * ccp_obj);
static void ccp_interrupt_config(const  ccp_t * ccp_obj);
static void ccp_pwm_mode_config(const  ccp_t * ccp_obj);


std_ReturnType CCP_Init(const ccp_t * ccp_obj){
     std_ReturnType ret = E_OK;
    if (NULL == ccp_obj) 
    {
        ret = E_NOT_ok; 
    }
    else{
        if (ccp_obj->ccp_instance == ccp1_select)
        {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if (ccp_obj->ccp_instance == ccp2_select)
        {
             CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else {} ; 
        if  (CCP1_COMPARE_MODE_SELECT == ccp_obj->CCP_mode)
        {
           if  ((ccp_obj->ccp_sub_mode)  == CCP_COMPARE_MODE_TOGGLE_ON_MATCH ) 
           {
                    CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); 
           }
           else if ((ccp_obj->ccp_sub_mode)  == CCP_COMPARE_MODE_GEN_EVENT )
            {
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT); 
            }
           else if ((ccp_obj->ccp_sub_mode)  == CCP_COMPARE_MODE_SET_PIN_LOW )
                
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW ); 
                    
           else if ((ccp_obj->ccp_sub_mode)  == CCP_COMPARE_MODE_SET_PIN_HIGH )
           {
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
           }
           else if ((ccp_obj->ccp_sub_mode)  == CCP_COMPARE_MODE_GEN_SW_INTERRUPT )
           {
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
           } 
           else {
              ret = E_NOT_ok;
           }
           }
        
        if  (CCP_CAPTURE_MODE_SELECT == ccp_obj->CCP_mode)
        {
            
            if (ccp_obj->ccp_sub_mode == CCP_CAPTURE_MODE_1_RAISING_EDGE ) 
            { 
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RAISING_EDGE); 
            }        
            else if (ccp_obj->ccp_sub_mode == CCP_CAPTURE_MODE_1_FALLING_EDGE ) 
            {   
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); 
            }    
            else if (ccp_obj->ccp_sub_mode == CCP_CAPTURE_MODE_1_FALLING_EDGE )
            {
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RAISING_EDGE ); 
            }
            else if (ccp_obj->ccp_sub_mode == CCP_CAPTURE_MODE_4_RAISING_EDGE )
            {
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RAISING_EDGE);
            }           
            else {
                    ret = E_NOT_ok;
            } 
             CCP_capture_mode_timer_select(ccp_obj);
        }
        
#if ((CCP_CFG_PWM_MODE_SELECTED  == CCP2_CFG_SELECT_MODE_SELECTED ) || (CCP_CFG_PWM_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED ))
        else if (CCP_PWM_MODE_SELECT == ccp_obj->CCP1_mode)
        {
          ccp_pwm_mode_config(ccp_obj);
        }
#endif 
        ret = gpio_pin_initialize_pin(&(ccp_obj->pin));
        ccp_interrupt_config(ccp_obj);
            ret = E_NOT_ok;                    
    }
    return ret ; 
}


std_ReturnType CCP_DeInit(const ccp_t * ccp_obj)
{
     std_ReturnType ret = E_OK ; 
    if(ccp_obj == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        if (ccp_obj->ccp_instance == ccp1_select)
        {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
       CCP1_InterruptDisable(); 
#endif 
        }
        else if (ccp_obj->ccp_instance == ccp2_select)
        {
             CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
       CCP2_InterruptDisable();
#endif 
        }
        else {} ; 
        ret= E_OK
    }
    return ret ;
}
#if (CCP1_CFG_CAPTURE_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED)
std_ReturnType CCP1_IsCaptureIsReady(uint8  * capture_status)
{
    std_ReturnType ret = E_OK;
    if (NULL == capture_status) 
    {
        if (CCP_CAPTURE_READY == PIR1bits.CCP1IF)
        {
            *capture_status = CCP_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else
        {
           *capture_status = CCP_CAPTURE_NOT_READY;
        }
        ret = E_NOT_ok; 
    }
    else{
            ret = E_NOT_ok;                    
    }
    
    return ret ; 
}
std_ReturnType CCP1_Capture_Mode_Read_Value(uint8  * capture_value ){
         std_ReturnType ret = E_OK;
         CCP_PERIOD_REG_T capture_temp_value = { .ccpr_high= 0 , .ccpr_high =0  } ;  
    if (NULL == capture_value) 
    {
        ret = E_NOT_ok; 
    }
    else{
        capture_temp_value.ccpr_low = CCPR1L;
        capture_temp_value.ccpr_high = CCPR1H;
        *capture_value = capture_temp_value.ccpr_16 ; 
        ret = E_NOT_ok;                    
    }
    
    return ret ; 
}
#endif 

#if (CCP1_CFG_COMPARE_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED)
std_ReturnType CCP1_IsCompareComplete(uint8  * compare_status)
{
         std_ReturnType ret = E_OK;
    if (NULL == compare_status) 
    {
         if (CCP1_COMPARE_READY == PIR1bits.CCP1IF)
        {
            *compare_status = CCP1_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else
        {
           *compare_status = CCP1_COMPARE_NOT_READY;
        }
        ret = E_NOT_ok; 
    }
    else{
 
        
        
        
        
            ret = E_NOT_ok;                    
    }
    
    return ret ; 
}
std_ReturnType CCP1_Compare_Mode_set_Value(uint16  compare_value )
{
    std_ReturnType ret = E_NOT_ok;
    CCP1_PERIOD_REG_T capture_temp_value = { .ccpr1_high= 0 , .ccpr1_high =0  } ;  
    capture_temp_value.ccpr_16 = compare_value; 
    CCPR1H =  capture_temp_value.ccpr1_high ;  
    CCPR1L =  capture_temp_value.ccpr1_low ;  
    ret = E_OK;   

    return ret ; 
}
        
#endif 
#if (CCP_CFG_PWM_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED)
  std_ReturnType CCP_PWM_Mode_Set_Duty(uint8  duty  , const ccp_t * ccp_obj )
  {
      std_ReturnType ret = E_OK; 
      if (NULL== ccp_obj)
      {
          ret = E_NOT_ok; 
      }
      else
      {
     uint16 l_duty_temp = 0 ; 
     l_duty_temp = (uint16)(4* (PR2+1 ) * (duty /100.0));
     if (ccp1_select == ccp_obj->ccp_instance)
     {
     CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
     CCPR1L = (uint8)(l_duty_temp >> 2 );
     }
     else if (ccp2_select == ccp_obj->ccp_instance)
     {
     CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
     CCPR2L = (uint8)(l_duty_temp >> 2 );  
     }
     else {}
     ret = E_OK;
     }
     return ret; 
  }

 std_ReturnType CCP_PWM_Start(const  ccp_t * ccp_obj)
 {
     std_ReturnType ret = E_OK;
     if (ccp_obj == NULL)
     {
         ret = E_NOT_ok; 
     }
     else 
     {
         if(ccp_obj->ccp_instance == ccp1_select)
         {
             CCP1CONbits.CCP1M = CCP_PWM_MODE ;
         }
         else if (ccp_obj->ccp_instance == ccp2_select)
         {
              CCP2CONbits.CCP2M = CCP_PWM_MODE ;
         }   
     }
    return ret ;
 }
 std_ReturnType CCP_PWM_Stop(const  ccp_t * ccp_obj)
 {  
     std_ReturnType ret = E_OK;
     if (ccp_obj == NULL)
     {
         ret = E_NOT_ok; 
     }
     else 
     {
         if(ccp_obj->ccp_instance == ccp1_select)
         {
             CCP1CONbits.CCP1M = CCP_MODULE_DISABLE ;
         }
         else if (ccp_obj->ccp_instance == ccp2_select)
         {
              CCP2CONbits.CCP2M = CCP_MODULE_DISABLE ;
         }   
     }
    return ret ;
 }

#endif 

void CCP1_ISR(void )
{
    CCP1_InterruptFlagClear();
    if(  CCP1_InterruptHandler)
    {
          CCP1_InterruptHandler();
    }
     
}

void CCP2_ISR(void )
{
    CCP2_InterruptFlagClear();
    if(  CCP2_InterruptHandler)
    {
          CCP2_InterruptHandler();
    }
     
}
static void CCP_capture_mode_timer_select(const  ccp_t * ccp_obj)
{
    if(ccp_obj->capture_timer_sele == ccp1_ccp2_timer3)
    {
        T3CONbits.T3CCP1 = 0 ; 
        T3CONbits.T3CCP2 = 1 ; 

        
    }
    else if (ccp_obj->capture_timer_sele ==ccp1_timer1_ccp2_timer3)
    {
        T3CONbits.T3CCP1 = 1 ; 
        T3CONbits.T3CCP2 = 0 ; 
    }
    else if (ccp_obj->capture_timer_sele ==ccp1_ccp2_time1)
    {
          T3CONbits.T3CCP1 = 0 ; 
        T3CONbits.T3CCP2 =   0 ; 
    }
    else
    {}
}
static void ccp_interrupt_config(const  ccp_t * ccp_obj)
{
#if CCP1_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE
       CCP1_InterruptEnable();
       CCP1_InterruptFlagClear();
       CCP1_InterruptHandler = ccp_obj->CCP2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_HIGH_PRIORITY == ccp_obj->ccp1_priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             CCP1_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == ccp_obj->ccp1_priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            CCP1_LowPrioritySet() ;
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();     
#endif 
#endif
#if CCP2_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE
       CCP2_InterruptEnable();
       CCP2_InterruptFlagClear();
       CCP2_InterruptHandler = ccp_obj->CCP2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_HIGH_PRIORITY == ccp_obj->ccp2_priority)
        {
            INTERRUPT_GlobalInterrupthighEnable();
            CCP2_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == ccp_obj->ccp2_priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            CCP2_LowPrioritySet() ;
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();     
#endif 
#endif  
       
}
#if ((CCP_CFG_PWM_MODE_SELECTED  == CCP2_CFG_SELECT_MODE_SELECTED ) || (CCP_CFG_PWM_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED ))

static void ccp_pwm_mode_config(const  ccp_t * ccp_obj)
{
      if(ccp1_select == ccp_obj->ccp_instance){
                if (CCP_PWM_MODE == ccp_obj->ccp1_sub_mode){
                    CCP1_SET_MODE(CCP_PWM_MODE );
            }
                else{};
            }
            else if(ccp2_select == ccp_obj->ccp_instance){
                if (CCP_PWM_MODE == ccp_obj->ccp1_sub_mode){
                    CCP2_SET_MODE(CCP_PWM_MODE );
            }
                else{};
            }
            PR2 = (uint8)((4000000UL/((ccp_obj->PWM_Frequency *4.0 * ccp_obj->timer2_postscaler_value * ccp_obj->timer2_prescaler_value))-1));
              
       
            /*nothing */
}
#endif