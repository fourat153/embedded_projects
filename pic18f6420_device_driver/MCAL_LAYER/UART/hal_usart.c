#include "hal_usart.h"
static void EUSAT_BaudeCalculation_Rate(const usart_t * usart);
static void UART_ASYNC_RX_Init(const usart_t * usart ) ;
static void UART_ASYNC_TX_Init(const usart_t * usart ) ;

#if USART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*USART_TxInterruptHandler)(void) = NULL;
#endif 
#if USART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*USART_RxInterruptHandler)(void) = NULL;
static void (*USART_FramingErrorInterruptHandler)(void) = NULL;
static void (*USART_OverrunErrorInterruptHandler)(void) = NULL;

#endif 



std_ReturnType usart_async_Init(const usart_t * usart){
     std_ReturnType ret = E_OK ; 
    if(usart  == NULL ) 
    { 
        ret = E_NOT_ok ;
    }
    else
    {
        
        RCSTAbits.SPEN  = USART_MODULE_DISABLE; 
        TRISCbits.RC7 = 1 ;
        TRISCbits.RC6 = 1 ;
        EUSAT_BaudeCalculation_Rate(usart);
        UART_ASYNC_RX_Init(usart);
        UART_ASYNC_TX_Init(usart); 
        RCSTAbits.SPEN  = USART_MODULE_ENABLE ; 
        ret= E_OK
    }
    return ret ;
} 
std_ReturnType usart_async_DeInit(const usart_t * usart ) {
     std_ReturnType ret = E_OK ; 
    if(usart  == NULL ) 
    { 
        
        ret = E_NOT_ok ;
    }
    else
    {
       
        ret= E_OK
    }
    return ret ;
} 
std_ReturnType usart_async_ReadByteBlocking( uint8  * data )
{
    
   std_ReturnType ret = E_OK ; 
   while(!PIR1bits.RCIF)
   {
       *data = RCREG;
   }
    return ret ;
} 
std_ReturnType usart_async_WriteByteBlocking( uint8 data ) 
   {
        std_ReturnType ret = E_OK ; 
        while(!TXSTAbits.TRMT) ; 
#if USART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        USART_TX_InterruptEnable() ; 
#endif
        TXREG = data ; 
        ret= E_OK
   }
    


static void EUSAT_BaudeCalculation_Rate(const usart_t * usart)
{
    float baud_rate_temp = 0 ; 
        switch (usart->baude_config ){
          case BAUDERATE_ASYN_8BIT_LOW_SPEED: 
              TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
              TXSTA1bits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
              BAUDCONbits.BRG16 = EUSART_08BIT_BAUDERATE_GEN ;
              baud_rate_temp = ((_XTAL_FREQ/ (float)usart->bauderate)/ 64) - 1; 
                         break ; 
          case BAUDERATE_ASYN_8BIT_HIGH_SPEED: 
              TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
              TXSTA1bits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
              BAUDCONbits.BRG16 = EUSART_08BIT_BAUDERATE_GEN ;
              baud_rate_temp = ((_XTAL_FREQ/ (float)usart->bauderate)/ 16) - 1; 

                         break ; 
          case    BAUDERATE_ASYN_16BIT_LOW_SPEED:
              TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
              TXSTA1bits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
              BAUDCONbits.BRG16 = EUSART_16BIT_BAUDERATE_GEN ;
              baud_rate_temp = ((_XTAL_FREQ/ (float)usart->bauderate)/ 16) - 1; 
              
                         break ; 
          case  BAUDERATE_ASYN_16BIT_HIGH_SPEED: 
              TXSTA1bits.SYNC = EUSART_ASYNCHRONOUS_MODE ;
              TXSTA1bits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
              BAUDCONbits.BRG16 = EUSART_16BIT_BAUDERATE_GEN ;
              baud_rate_temp = ((_XTAL_FREQ/ (float)usart->bauderate)/ 4) - 1; 
              
                         break ; 
            
          case  BAUDERATE_SYN_8BIT: 
              TXSTA1bits.SYNC = EUSART_SYNCHRONOUS_MODE ;
              BAUDCONbits.BRG16 = EUSART_08BIT_BAUDERATE_GEN ;
              baud_rate_temp = ((_XTAL_FREQ/ (float)usart->bauderate)/ 4) - 1; 
              
                        break ; 
                      
          case BAUDERATE_SYN_16BIT: 
              TXSTA1bits.SYNC = EUSART_SYNCHRONOUS_MODE ;  
              BAUDCONbits.BRG16 = EUSART_16BIT_BAUDERATE_GEN ;
              baud_rate_temp = ((_XTAL_FREQ/ (float)usart->bauderate)/ 4) - 1;
              
                      break ; 
            default : 
                break ;
       
    }
        SPBRG = (uint8)((uint32)baud_rate_temp);
        SPBRGH =(uint8)(((uint32)baud_rate_temp)>> 8 ) ; // mode 16 bit shift 8 bit high to read it 
} 

static void UART_ASYNC_TX_Init(const usart_t * usart ) 
{
    if (EUSART_ASYNCHRONOUS_TX_ENABLE == usart->usart_tx_config.usart_tx_enable)
    {
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        USART_TxInterruptHandler = usart->EUSART_TX_INTERRUPT_HANDLER;
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == usart->usart_tx_config.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE ;
#if USART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
            USART_TX_InterruptEnable();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
         INTERRUPT_PriorityLevelsEnables();
         if(INTERRUPT_HIGH_PRIORITY == usart->usart_tx_config.priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             USART_TX_HighPrioritySet();  
         }
        else if (INTERRUPT_LOW_PRIORITY == usart->usart_tx_config.priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            USART_TX_LowPrioritySet()  ;
        }    
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();    
#endif 
#endif 
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == usart->usart_tx_config.usart_tx_interrupt_enable)
        {
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE ;
        }
        else 
        {}
        if (EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == usart->usart_tx_config.usart_tx_9bit_enable )
        {
            TXSTA1bits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE; 
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == usart->usart_tx_config.usart_tx_9bit_enable )
        {
            TXSTA1bits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE; 
        }
        else 
        {}
    }
}
static void UART_ASYNC_RX_Init(const usart_t * usart ) 
{
    if (EUSART_ASYNCHRONOUS_RX_ENABLE == usart->usart_rx_config.usart_rx_enable)
    {
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        USART_RxInterruptHandler = usart->EUSART_RX_INTERRUPT_HANDLER;
        USART_OverrunErrorInterruptHandler = usart->EUSART_OVERRUN_INTERRUPT_HANDLER;
        USART_FramingErrorInterruptHandler = usart->EUSART_FRAMERROR_INTERRUPT_HANDLER;

        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == usart->usart_rx_config.usart_rx_interrupt_enable)
        {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE ;
#if USART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
            USART_RX_InterruptEnable();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnables();
         if(INTERRUPT_HIGH_PRIORITY == usart->usart_rx_config.priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             USART_RX_HighPrioritySet()   ;
         }
        else if (INTERRUPT_LOW_PRIORITY == usart->usart_rx_config.priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            USART_RX_LowPrioritySet()  ;
        }    
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();    
#endif 
#endif 
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == usart->usart_rx_config.usart_rx_interrupt_enable)
        {
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE ;
        }
        else 
        {}
        if (EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == usart->usart_rx_config.usart_rx_9bit_enable )
        {
            RCSTA1bits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE; 
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == usart->usart_rx_config.usart_rx_9bit_enable )
        {
             RCSTA1bits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE; 
        }
        else 
        {}
    }
}
std_ReturnType usart_async_WriteStringByteBlocking( uint8 *data , uint8 str_len ) 
{
    std_ReturnType ret = E_OK ; 
    if(data == NULL ) 
    {  
        ret = E_NOT_ok ;
    }
    else
    {
      for (int i = 0 ; i < str_len ; i++) 
      {
         ret=usart_async_WriteByteBlocking( data[i]); 
      }
        ret= E_OK
    }
    return ret ;
}
void USART_TX_ISR()
{
    USART_TX_InterruptDisable();
    if(USART_TxInterruptHandler)
    {
        USART_TxInterruptHandler(); 
    }
    else 
    {
        /*nothing*/
    }
}
void USART_RX_ISR()
{
    if(USART_RxInterruptHandler)
    {
        USART_RxInterruptHandler();
    }
    else{}
    if(USART_OverrunErrorInterruptHandler)
    {
        USART_OverrunErrorInterruptHandler();
    }
    else
    {
        
    }
    if(USART_FramingErrorInterruptHandler)
    {
        USART_FramingErrorInterruptHandler(); 
    }
    else{}
}

