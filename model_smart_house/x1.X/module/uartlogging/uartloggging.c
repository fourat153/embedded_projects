#include "uartlogging.h"

void uart_loggingDebugData(uint8_t * str , uint16_t str_length){
    for ( uint8_t i  = 0 ; i < str_length ; i++ )
    {
        EUSART_Write(*str++);
    }
}

