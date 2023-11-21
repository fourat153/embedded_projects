/* 
 * File:   HAL_EEPROM.h
 * Author: mm77
 *
 * Created on July 23, 2023, 6:24 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/******* ****includes********/

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_LAYER/Interrupt/mcal_interrupt_internal.h"


/*************macros************/




/*************function macros******/
#define ACCESS_FLASH_PROGRAM_MEMORY  1 ; 
#define ACCESS_EEPROM_PROGRAM_MEMORY 0 ;

#define ACCESS_CONFIG_REGISTERS  1 ; 
#define ACCESS_FLASH_EEPROM_MEMORY 0 ;

#define ALLOW_WRITE_CYCLES_FLASH_EEPROM  1 ; 
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM  0 ;

#define INITIATE_DATA_EEPROM_WRITE_ERASE 1 ;
#define DATA_EEPORM_WRITE_ERASE_COMPLETED 0;

#define INTI_DATA_EEPORM_READ 0;
/*************user define data types*******/



/*************function prototypes******/
std_ReturnType Data_eeprom_write_byte(uint16 address_target , uint8 data ) ; 
std_ReturnType Data_eeprom_read_byte(uint16 address_target , uint8 * saved_location);


#endif	/* HAL_EEPROM_H */

