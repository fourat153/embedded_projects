#include "HAL_EEPROM.h"

std_ReturnType Data_eeprom_write_byte(uint16 address_target , uint8 data ) 
{
    std_ReturnType ret= E_OK
   /* Read the Interrupt Status "Enabled or Disabled" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (uint8)((address_target >> 8) & 0x03);
    EEADR = (uint8)(address_target & 0xFF);
    /* Update the Data Register */
    EEDATA = data;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupts "General Interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = DATA_EEPORM_WRITE_ERASE_COMPLETED;
    /* Wait for write to complete */
    while(EECON1bits.WR); // HARDWAR SET TO 0 
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

std_ReturnType Data_eeprom_read_byte(uint16 address_target , uint8 * saved_location)
{
    std_ReturnType ret = E_OK ;
    if (NULL == saved_location )
    {
        ret = E_NOT_ok ; 
    }
    else 
    {
     EEADRH = (uint8 )((address_target >> 8) & 0x03  );
     EEADR  = (uint8) (address_target & 0xFF );
     EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY ;
     EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY ;
     EECON1bits.RD  = INTI_DATA_EEPORM_READ;
     NOP(); // preferd fi high freq no operation 
     NOP(); // preferd fi high freq no operation
     *saved_location =  EEDATA;
        ret = E_OK; 
    }
    return ret ; 
}

