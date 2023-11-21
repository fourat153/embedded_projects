#include "timer1.h"

static inline void Timer1_mode_select(const timer1_t * timer);

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER1_InterruptHandler)(void) = NULL;
#endif 
static uint16 preload_alaise = 0 ; 
std_ReturnType Timer1_init(const timer1_t *   timer) 
{
    std_ReturnType ret = E_OK ;
    if( NULL == timer )
    {
        ret = E_NOT_ok; 
    }
    else 
    {
        TIMER1_MODULE_DISABLE(); 
        TIMER1_PRESCALER_SELECT(timer->timer1_prescaler_value);
        Timer1_mode_select(timer);
        TMR1H  = (timer->timer1_preload_value)>> 8 ;
        TMR1L  = (uint8) (timer->timer1_preload_value);
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        TIMER1_InterruptHandler = timer->TIMER1_InterruptHandler; 
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
        
        TIMER1_MODULE_ENABLE(); 
        
    }
    return ret ; 
}
std_ReturnType Timer1_deinit(const timer1_t* timer) 
{
    std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
       TIMER1_MODULE_DISABLE(); 
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
       TIMER1_InterruptDisable();
#endif 
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer1_write_value(const  timer1_t * timer , uint16 value) {
    std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TMR1H  = (timer->timer1_preload_value)>> 8 ;
        TMR1L  = (uint8) (timer->timer1_preload_value);
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer1_read_value(const  timer1_t * timer , uint16 * value){
     std_ReturnType ret = E_OK ;
       uint8 l_tmr1l = 0 , l_tmr1h = 0 ; 
    if((NULL == timer) || (NULL == value))
    {
        ret = E_NOT_ok; 
    }
    else 
    {
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1L;
        * value = (uint16)((l_tmr1h << 8 ) + l_tmr1l);
        ret= E_OK
    }
    return ret ; 
}
static inline void Timer1_mode_select(const timer1_t * timer)
{
    if(TIMER1_TIMER_MODE == timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
       
    }
    else if(TIMER1_COUNTER_MODE  == timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE == timer->timer1_counter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == timer->timer1_counter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
         }
    }
        
}
void TIMER1_ISR(void )
{
    TMR1H  = (preload_alaise)>> 8 ;
    TMR1L  = (uint8) (preload_alaise);
    TIMER1_InterruptFlagClear();
    if( TIMER1_InterruptHandler)
    {
         TIMER1_InterruptHandler();
    }
     
}