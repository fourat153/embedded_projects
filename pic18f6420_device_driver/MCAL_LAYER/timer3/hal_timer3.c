#include "hal_timer3.h"
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_InterruptHandler)(void) = NULL;
#endif
static inline void Timer3_mode_select(const timer3_t * timer);
 
static uint16 timer3_preload_alaise = 0 ; 

std_ReturnType Timer3_init(const timer3_t *   timer){
    std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        
        TIMER3_MODULE_DISABLE(); 
        TIMER3_PRESCALER_SELECT(timer->timer3_prescaler_value);
        Timer3_mode_select(timer);
        TMR1H  = (timer->timer3_preload_value)>> 8 ;
        TMR1L  = (uint8) (timer->timer3_preload_value);
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TIMER3_InterruptHandler = timer->TIMER3_InterruptHandler; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             TIMER1_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == timer->priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            TIMER1_LowPrioritySet() ;
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();     
#endif 
#endif
        
        TIMER3_MODULE_ENABLE(); 
        ret= E_OK
    }
    return ret ;
    
}
std_ReturnType Timer3_deinit(const timer3_t* timer){
     std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TIMER3_MODULE_DISABLE(); 
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
       TIMER3_InterruptDisable();
#endif 
        ret= E_OK
    
    }
    return ret ;
} 
std_ReturnType Timer3_write_value(const  timer3_t * timer , uint16 value){
     std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    { 
        
        ret = E_NOT_ok ;
    }
    else
    {
        TMR3H  = (value)>> 8 ;
        TMR3L  = (uint8)(value);
        ret= E_OK
    }
    return ret ;
} 
std_ReturnType Timer3_read_value(const  timer3_t * timer , uint16 * value){
      std_ReturnType ret = E_OK ;
       uint8 l_tmr3l = 0 , l_tmr3h = 0 ; 
    if((NULL == timer) || (NULL == value))
    {
        ret = E_NOT_ok; 
    }
    else 
    {
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        * value = (uint16)((l_tmr3h << 8 ) + l_tmr3l);
        ret= E_OK
    }
    return ret ; 
 }
void TIMER3_ISR(void )
{
    TMR1H  = (timer3_preload_alaise)>> 8 ;
    TMR1L  = (uint8) (timer3_preload_alaise);
    TIMER1_InterruptFlagClear();
    if( TIMER3_InterruptHandler)
    {
         TIMER3_InterruptHandler();
    }
     
}

static inline void Timer3_mode_select(const timer3_t * timer)
{
    if(TIMER3_TIMER_MODE == timer->timer3_mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
       
    }
    else if(TIMER3_COUNTER_MODE  == timer->timer3_mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE == timer->timer3_counter_mode)
        {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == timer->timer3_counter_mode)
        {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
         }
    }
        
}