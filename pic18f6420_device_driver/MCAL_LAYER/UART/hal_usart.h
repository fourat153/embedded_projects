/* 
 * File:   hal_usart.h
 * Author: mm77
 *
 * Created on August 10, 2023, 1:42 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H


/********* includes ************/


#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
#include "../../MCAL_LAYER/mcal_std_types.h"
#include "pic18f4620.h"
#include "../Interrupt/mcal_interrupt_internal.h"
#include "../application.h"

/********* macros ************/
#define USART_MODULE_ENABLE 1 
#define USART_MODULE_DISABLE 0 

#define EUSART_ASYNCHRONOUS_MODE   0 
#define EUSART_SYNCHRONOUS_MODE   1
#define EUSART_ASYNCHRONOUS_HIGH_SPEED 1 
#define EUSART_ASYNCHRONOUS_LOW_SPEED  0 

#define EUSART_16BIT_BAUDERATE_GEN      1 
#define EUSART_08BIT_BAUDERATE_GEN      0

#define EUSART_ASYNCHRONOUS_TX_ENABLE    1 
#define EUSART_ASYNCHRONOUS_TX_DISABLE   0 

#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE    1 
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE   0 

#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE    1 
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE   0 

#define EUSART_ASYNCHRONOUS_RX_ENABLE    1 
#define EUSART_ASYNCHRONOUS_RX_DISABLE   0 

#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE    1 
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE   0 

#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE    1 
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE   0 

#define EUSART_OVERARUN_ERROR_DETECTED        1 
#define EUSART_OVERARUN_ERROR_CLEARD          0 

#define EUSART_FARMMING_ERROR_DETECTED        1 
#define EUSART_FARMMING_ERROR_CLEARD          0 
/********* function macros ************/
  



/********* user define data types ************/
typedef enum {
    BAUDERATE_ASYN_8BIT_LOW_SPEED,
    BAUDERATE_ASYN_8BIT_HIGH_SPEED,
    BAUDERATE_ASYN_16BIT_LOW_SPEED,
    BAUDERATE_ASYN_16BIT_HIGH_SPEED,
    BAUDERATE_SYN_8BIT, 
    BAUDERATE_SYN_16BIT,
}bauderate_gen_t;

typedef struct {
    uint8 usart_tx_enable : 1 ; 
    uint8 usart_tx_interrupt_enable : 1 ; 
    uint8 usart_tx_9bit_enable : 1 ;
    uint8 usart_tx_reserved : 5 ; 
    interrupt_priority_cfg priority;
}usart_tx_cfg_t;

typedef struct {
    uint8 usart_rx_enable : 1 ; 
    uint8 usart_rx_interrupt_enable : 1 ; 
    uint8 usart_rx_9bit_enable : 1 ;
    uint8 usart_rx_reserved : 5 ; 
    interrupt_priority_cfg priority;
}usart_rx_cfg_t;

typedef union 
{
    struct {
        uint8 usart_frame_error : 1; 
        uint8 usart_overrun_error   : 1;
        uint8 usart_reserved : 6 ; 
    };
    uint8 usart_status ;
}usart_error_status_t ;
typedef struct 
{
    uint32 bauderate ; 
    bauderate_gen_t baude_config ; 
    usart_rx_cfg_t usart_rx_config ; 
    usart_tx_cfg_t usart_tx_config ; 
    usart_error_status_t error_status;
    void (*EUSART_RX_INTERRUPT_HANDLER)(void) ; 
    void (*EUSART_TX_INTERRUPT_HANDLER)(void) ; 
    void (*EUSART_FRAMERROR_INTERRUPT_HANDLER)(void) ; 
    void (*EUSART_OVERRUN_INTERRUPT_HANDLER)(void) ; 
    
}usart_t;

/********* functions pIrototypes ************/
std_ReturnType usart_async_Init(const usart_t * usart); 
std_ReturnType usart_async_DeInit(const usart_t * usart ) ; 
std_ReturnType usart_async_ReadByteBlocking( uint8  * data ) ;
std_ReturnType usart_async_WriteByteBlocking( uint8 data ) ; 
std_ReturnType usart_async_WriteStringByteBlocking( uint8 *data , uint8 str_len ) ; 

#endif	/* HAL_USART_H */

