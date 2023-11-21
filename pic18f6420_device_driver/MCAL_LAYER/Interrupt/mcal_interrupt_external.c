#include "mcal_interrupt_external.h"
static void ( * INT0_InterruptHandler)(void) = NULL; // take form the already intialized obj_intx the function and assign it here  
static void ( * INT1_InterruptHandler)(void) = NULL;
static void ( * INT2_InterruptHandler)(void) = NULL;

static void ( * RB4_InterruptHandler)(void) = NULL; // take form the already intialized obj_intx the function and assign it here  
static void ( * RB5_InterruptHandler)(void) = NULL;
static void ( * RB6_InterruptHandler)(void) = NULL;
static void ( * RB7_InterruptHandler)(void) = NULL; // take form the already intialized obj_intx the function and assign it here  


static std_ReturnType Interrupt_INTx_Enable(const Interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_Disable(const Interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_Priority_init(const Interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_Edge_Init(const Interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_PIN_Init(const Interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_clear_flag(const Interrupt_INTx_t * int_obj);

static std_ReturnType INT0_setinterrupthandler(void (* INTx_interrupt_handler)(void) );
static std_ReturnType INT1_setinterrupthandler(void ( * INTx_interrupt_handler)(void) );
static std_ReturnType INT2_setinterrupthandler(void ( * INTx_interrupt_handler)(void) );
static std_ReturnType interrupt_intx_setinterrupthandler(const Interrupt_INTx_t * int_obj );


static std_ReturnType Interrupt_RBx_Enable(const Interrupt_RBx_t * int_obj);
static std_ReturnType Interrupt_RBx_Disable(const Interrupt_RBx_t * int_obj);
static std_ReturnType Interrupt_RBx_Priority_init(const Interrupt_RBx_t * int_obj);
static std_ReturnType Interrupt_RBx_PIN_Init(const Interrupt_RBx_t * int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t * int_obj ){
    std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        /*disable interrupt */
        ret= Interrupt_INTx_Disable(int_obj);
        /*clear flag : external interrupt did not ocure */
        ret = Interrupt_INTx_clear_flag(int_obj);
        
        /*configure external interrupt edge */
        ret = Interrupt_INTx_Edge_Init(int_obj);
        /*configure external priority */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        ret = Interrupt_INTx_Priority_init(int_obj);
        #endif
        /*configure external I/O*/
        ret =Interrupt_INTx_PIN_Init(int_obj);
        /*configure default callback*/
        ret  = interrupt_intx_setinterrupthandler(int_obj);
        /*enable interrupt*/
        ret= Interrupt_INTx_Enable(int_obj);
        
    }
    
    
    return ret ; 
}
void INT0_ISR(void) 
{
    EXT_INT0_InterruptFlagClear();
    if (INT0_InterruptHandler) // if not null excuter it 
    {
        INT0_InterruptHandler();
     
    }
}

void INT1_ISR(void) 
{
    EXT_INT1_InterruptFlagClear();
    if (INT1_InterruptHandler) // if not null excuter it 
    {
        INT1_InterruptHandler();
     
    }
}


void INT2_ISR(void) 
{
    EXT_INT2_InterruptFlagClear();
    if (INT2_InterruptHandler) // if not null excuter it 
    {
        INT2_InterruptHandler();
     
    }
}
void RB4_ISR(void) 
{
    EXT_RBx_InterruptFlagClear();
    if (RB4_InterruptHandler) // if not null excuter it 
    {
       RB4_InterruptHandler();
     
    }
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t * int_obj ){
     std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        ret = Interrupt_INTx_Disable(int_obj);  
    }
    
    
    return ret ; 
    
} 

/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBTx_Init(const Interrupt_RBx_t * int_obj ){
     std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        EXT_RBx_InterruptDisable(); 
        EXT_RBx_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            EX_RBx_LowPriorityset() ;
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority)
        {
            INTERRUPT_GlobalInterrupthighEnable();
            EX_RBx_HighPriorityset() ;
        }
        else 
        {
            
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable(); 
#endif 
        ret = gpio_pin_initialize_pin(&(int_obj->mcu_pin));
        switch(int_obj->mcu_pin.pin)
        {
            case PIN4 :
                RB4_InterruptHandler  = int_obj->EXTERNAL_INTRRUPT_HANDLER;
                break;
            case PIN5 :
                RB5_InterruptHandler  = int_obj->EXTERNAL_INTRRUPT_HANDLER;
                break;
            case PIN6 :
                RB6_InterruptHandler  = int_obj->EXTERNAL_INTRRUPT_HANDLER;
                break;
            case PIN7 :
                RB7_InterruptHandler  = int_obj->EXTERNAL_INTRRUPT_HANDLER;
                break;
            default :
                ret = E_NOT_ok;
        }
        
        EXT_RBx_InterruptEnable() ;
    }
     
    return ret ; 
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_t * int_obj )
{
     std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
    }
    
    
    return ret ; 
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_Enable(const Interrupt_INTx_t * int_obj)
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        switch(int_obj->source) 
        {
            case  INERRUPT_EXTARNAL_INT0 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
           
                 INTERRUPT_GlobalInterrupthighEnable() ; // INT0 is HIHGH ¨PER default cant be low p
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();            
#endif
                EXT_INT0_InterruptEnable();
                    break ;
            case  INERRUPT_EXTARNAL_INT1: 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnables();
            if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                    {
                     INTERRUPT_GlobalInterruptlowEnable()   ;
                    }
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                    {
                       INTERRUPT_GlobalInterrupthighEnable() ;
                    }
                    else
                    {
                        /*nothing*/
                    }
                
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();            
#endif
                EXT_INT1_InterruptEnable() ;  
                break ;
            case  INERRUPT_EXTARNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnables();
if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                    {
                     INTERRUPT_GlobalInterruptlowEnable()     ;
                    }
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                    {
                        INTERRUPT_GlobalInterrupthighEnable() ;
                    }
                    else
                    {
                        /*nothing*/
                    }
                
                
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();            
#endif
                EXT_INT2_InterruptEnable() ;
                
                break ;
            default : ret =E_NOT_ok;
        }   
    }
    
    return ret ; 
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_Disable(const Interrupt_INTx_t * int_obj)
{
   std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        switch(int_obj->source) 
        {
            case  INERRUPT_EXTARNAL_INT0 : EXT_INT0_InterruptDisable() ;break ;
            case  INERRUPT_EXTARNAL_INT1: EXT_INT1_InterruptDisable() ;break ;
            case  INERRUPT_EXTARNAL_INT2: EXT_INT2_InterruptDisable() ;break ;
            default : ret =E_NOT_ok;
        }   
           
        
    }
    return ret ; 
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE 
static std_ReturnType Interrupt_INTx_Priority_init(const Interrupt_INTx_t * int_obj)
{
     std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
           switch(int_obj->source) 
        {
            case  INERRUPT_EXTARNAL_INT0:
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                {
                    EX_INT1_lowPriorityset();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                     EX_INT1_lowPriorityset();
                }
                else
                {
                    /*nothing*/
                }
                break;
            case  INERRUPT_EXTARNAL_INT2:
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority )
                {
                     EX_INT2_lowPriorityset();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                     EX_INT2_lowPriorityset();
                }
                else
                {
                    /*nothing*/
                }
                break;
            
            default : ret =E_NOT_ok;
        }   
           
    }
    
    
    return ret ; 
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_Edge_Init(const Interrupt_INTx_t * int_obj)
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
           switch(int_obj->source) 
        {
            case  INERRUPT_EXTARNAL_INT0 :
                if(INERRUPT_FALLING_EDGE == int_obj->edge )
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else if (INERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT0_RisingEdgeSet();
                }
                else
                {
                    /*nothing*/
                }
                break;
                
            case  INERRUPT_EXTARNAL_INT1:
                if(INERRUPT_FALLING_EDGE == int_obj->edge )
                {
                    EXT_INT1_FallingEdgeSet();
                }
                else if (INERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT1_RisingEdgeSet();
                }
                else
                {
                    /*nothing*/
                }
                break;
                
            case  INERRUPT_EXTARNAL_INT2:
                if(INERRUPT_FALLING_EDGE == int_obj->edge )
                {
                    EXT_INT2_FallingEdgeSet();
                }
                else if (INERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT2_RisingEdgeSet();
                }
                else
                {
                    /*nothing*/
                }
                break;
            
            
            default : ret =E_NOT_ok;
        }   
           
    }
    
    
    return ret ; 
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_ReturnType Interrupt_INTx_PIN_Init(const Interrupt_INTx_t * int_obj)
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        ret= gpio_pin_initialize_pin(&(int_obj->mcu_pin));
    }
    
    
    return ret ; 
}
static std_ReturnType Interrupt_INTx_clear_flag(const Interrupt_INTx_t * int_obj)
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        switch(int_obj->source)
        {
            case INERRUPT_EXTARNAL_INT0  :
                ret = EXT_INT0_InterruptFlagClear();
                break ; 
            case INERRUPT_EXTARNAL_INT1 :
                ret = EXT_INT1_InterruptFlagClear();
                break ;   
            case INERRUPT_EXTARNAL_INT2 :
                ret = EXT_INT2_InterruptFlagClear();
                break ;  
            default : ret = E_NOT_ok; 
                   
        }
    }
    
      return ret ;
    
}
static std_ReturnType INT0_setinterrupthandler(void  ( * INTx_interrupt_handler)(void) )
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == INTx_interrupt_handler )
    { 
        ret = E_NOT_ok;
    }
    else 
    {
        INT0_InterruptHandler = INTx_interrupt_handler;
        ret = E_OK;
    }
    
      return ret ;
    
}
static std_ReturnType INT1_setinterrupthandler(void (* INTx_interrupt_handler)(void) )
{
      std_ReturnType ret= E_OK ; 
    if ( NULL == INTx_interrupt_handler )
    { 
        ret = E_NOT_ok;
    }
    else 
    {
        INT1_InterruptHandler = INTx_interrupt_handler;
        ret = E_OK;
    }
    
      return ret ;
}
static std_ReturnType INT2_setinterrupthandler(void ( *INTx_interrupt_handler)(void) )
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == INTx_interrupt_handler )
    { 
        ret = E_NOT_ok;
    }
    else 
    {
        INT2_InterruptHandler = INTx_interrupt_handler;
        ret = E_OK;
    }
    
      return ret ;
}
static std_ReturnType interrupt_intx_setinterrupthandler(const Interrupt_INTx_t * int_obj )
{
    std_ReturnType ret= E_OK ; 
    if ( NULL == int_obj )
    {
        ret = E_NOT_ok;
    }
    else 
    {
        switch(int_obj->source)
        {
            case INERRUPT_EXTARNAL_INT0  :
                ret = INT0_setinterrupthandler(int_obj->EXTERNAL_INTRRUPT_HANDLER);
                break ; 
            case INERRUPT_EXTARNAL_INT1 :
                ret = INT1_setinterrupthandler(int_obj->EXTERNAL_INTRRUPT_HANDLER);
                break ;   
            case INERRUPT_EXTARNAL_INT2 :
                ret = INT2_setinterrupthandler(int_obj->EXTERNAL_INTRRUPT_HANDLER);
                break ;  
            default : ret = E_NOT_ok; 
                   
        }
    }
    
      return ret ; 
}