#include "../uart_logging/uart_logging.h"
#include "../../mcc_generated_files/eusart.h"

void uart_logging(uint8_t * string , int size )
{
    for (int i = 0 ; i < size ; i++)
    {
        EUSART_Write(*string++);
    }
}