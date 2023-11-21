
#include "hal_timer2.h"


#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER2_InterruptHandler)(void) = NULL;
#endif 
static uint16 timer2_preload_alaise = 0 ; 

std_ReturnType Timer2_init(const timer2_t *   timer) 
{
 std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TIMER2_MODULE_DISABLE();
        TIMER2_POSTSCALER_SELECT(timer->timer2_postscaler_value);
        TIMER2_PRESCALER_SELECT(timer->timer2_prescaler_value);
        TMR2 = timer->timer2_preloaded_value ; 
        timer2_preload_alaise = timer->timer2_preloaded_value ; 
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TIMER2_InterruptHandler = timer->TIMER2_InterruptHandler; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             TIMER2_HighPrioritySet();
          
        }
        else if (INTERRUPT_LOW_PRIORITY == timer->priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            TIMER2_LowPrioritySet() ;
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();     
#endif 
#endif
        TIMER2_MODULE_ENABLE();
       
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer2_deinit(const timer2_t* timer)
{
    std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
       TIMER2_InterruptDisable();
#endif 
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer2_write_value(const  timer2_t * timer ,uint16 value)
{
    std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TMR2 = value; 
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer2_read_value(const  timer2_t * timer , uint16 * value) 
{
    std_ReturnType ret = E_OK ; 
    if((timer == NULL) || (value == NULL)) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        *value = TMR2;   
        ret= E_OK
    }
    return ret ;
}

void TIMER2_ISR(void )
{
   
    TIMER2_InterruptFlagClear();
    TMR2= timer2_preload_alaise;
    if( TIMER2_InterruptHandler)
    {
         TIMER2_InterruptHandler();
    }
     
}