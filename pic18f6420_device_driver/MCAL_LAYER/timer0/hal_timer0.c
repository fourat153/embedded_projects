#include "hal_timer0.h"
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_InterruptHandler)(void) = NULL;
#endif 
static inline void Timer0_Prescaler_config(const timer0_t * timer);
static inline void Timer0_mode_select(const timer0_t * timer);
static inline void Timer0_regiseter_size(const timer0_t * timer);

static uint16 preload_alaise = 0 ; 

std_ReturnType Timer0_init(const timer0_t *   timer)
{
    std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TIMER0_MODULE_DISABLE(); 
        Timer0_mode_select(timer);
        Timer0_Prescaler_config(timer);
        Timer0_regiseter_size(timer);
        TMR0H  = (timer->timer0_preload_value)>> 8 ;
        TMR0L  = (uint8) (timer->timer0_preload_value);
        preload_alaise = timer->timer0_preload_value ; 
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TIMER0_InterruptHandler = timer->TIMER0_InterruptHandler; 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             TIMER0_HighPrioritySet();
          
        }
        else if (INTERRUPT_LOW_PRIORITY == timer->priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            TIMER0_LowPrioritySet() ;
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();     
#endif 
#endif 
        TIMER0_MODULE_ENABLE();
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer0_deinit(const timer0_t * timer)
{
     std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
       TIMER0_MODULE_DISABLE(); 
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
       TIMER0_InterruptDisable();
#endif 
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer0_write_value(const timer0_t * timer , uint16 value)
{
     std_ReturnType ret = E_OK ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        TMR0H  = (timer->timer0_preload_value)>> 8 ;
        TMR0L  = (uint8) (timer->timer0_preload_value);
        ret= E_OK
    }
    return ret ;
}
std_ReturnType Timer0_read_value(const timer0_t * timer , uint16 * value){
     std_ReturnType ret = E_OK ; 
     uint8 l_tmr0l = 0 , l_tmr0h = 0 ; 
    if(timer == NULL ) 
    {
        ret = E_NOT_ok ;
    }
    else
    {
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0L;
        * value = (uint16)((l_tmr0h << 8 ) + l_tmr0l);
        
        ret= E_OK
    }
    return ret ;
 
}

void TIMER0_ISR(void )
{
    TMR0H  = (preload_alaise)>> 8 ;
    TMR0L  = (uint8) (preload_alaise);
    TIMER0_InterruptFlagClear();
    if( TIMER0_InterruptHandler)
    {
         TIMER0_InterruptHandler();
    }
     
}
static inline void Timer0_Prescaler_config(const timer0_t * timer)
{
    if(TIMER0_PRESCALER_ENABLE_CFG == timer->prescaler_enable)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG   == timer->prescaler_enable)
        {
            TIMER0_PRESCALER_DISABLE();
        }
  
}

static inline void Timer0_mode_select(const timer0_t * timer)
{
    if(TIMER0_TIMER_MODE == timer->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
       
    }
    else
    {
        if(TIMER0_TIMER_MODE   == timer->timer0_mode)
        {
             TIMER0_COUNTER_MODE_ENABLE();
             if(TIMER0_RISING_EDGE_CFG == timer->timer0_counter_edge)
             {
                 TIMER0_RISING_EDEGE_ENABLE() ;
             }
             else if(TIMER0_FALLING_EDGE_CFG == timer->timer0_counter_edge) 
             {
                 TIMER0_FALLING_EDEGE_ENABLE();
             }
                   
        }
    }
}
static inline void Timer0_regiseter_size(const timer0_t * timer)
{
    if( TIMER0_8BIT_REGISTER_MODE  == timer->timer0_register_size)
    {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if (TIMER0_16BIT_REGISTER_MODE == timer->timer0_register_size)
    {
        TIMER0_16BIT_REGISTER_MODE_ENABLE(); 
    }
    else
    {}
}
