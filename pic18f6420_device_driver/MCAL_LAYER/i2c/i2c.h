/* 
 * File:   i2c.h
 * Author: mm77
 *
 * Created on September 2, 2023, 11:09 AM
 */

#ifndef I2C_H
#define	I2C_H
/*section : includes */
#include "pic18f4620.h"
#include "../../MCAL_LAYER/mcal_std_types.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
#include "../../MCAL_LAYER/Interrupt/mcal_interrupt_internal.h"
#include "../application.h"
/*section: macros definition */
#define I2C_SLEW_RATE_DISABLE 1
#define I2C_SLEW_RATE_ENABLE 0

#define I2C_SMBus_ENABLE   1 
#define I2C_SMBus_DISABLE  0 

#define I2C_LAST_BYTE_DATA 1 
#define I2C_LAST_BYTE_ADDRESS 0

#define STOP_BIT_DETECTED 1 
#define STOP_BIT_NOT_DETECTED 0

#define START_BIT_DETECTED 1 
#define START_BIT_NOT_DETECTED 0

#define  MSSP_I2C_MASTER_MODE 1 
#define  MSSP_I2C_SLAVE_MODE 0


#define I2C_SLAVE_MODE_7BITS_ADDRESS 0X06U
#define I2C_SLAVE_MODE_10BITS_ADDRESS 0X07U
#define I2C_SLAVE_MODE_7BITS_ADDRESS_SS_INTERRUPT_ENABLE 0X0EU
#define I2C_SLAVE_MODE_10BITS_ADDRESS_SS_INTERRUPT_ENABLE 0X0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK                     0X08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED               0X0BU 

#define I2C_GENERAL_CALL_ENABLE  1
#define I2C_GENERAL_CALL_DISABLE 0 

#define I2C_MASTER_RECEIVE_ENABLE 1
#define I2C_MASTER_RECEIVE_DISABLE 0

#define I2C_ACK_RECIVED_FROM_SLAVE 0 
#define I2C_ACK_NOT_RECIVED_FROM_SLAVE 1

#define I2C_MASTER_SEND_ACK 0 
#define I2C_MASTER_SEND_NOT_ACK 1

/*section: macros function declaration*/
#define I2C_SLEW_RATE_DISALE_CFG() (SSPSTATbits.SMP = 1 ) 
#define I2C_SLEW_RATE_ENABLE_CFG() (SSPSTATbits.SMP = 0 ) 

#define I2C_SMBus_DISABLE_CFG() (SSPSTATbits.CKE = 0 ) 
#define I2C_SMBus_ENABLE_CFG() (SSPSTATbits.CKE = 1 ) 

#define I2C_GENERAL_CALL_DISABLE_CFG() (SSPCON2bits.GCEN = 0 ) 
#define I2C_GENERAL_CALL_ENABLE_CFG() (SSPCON2bits.GCEN = 1 )

#define I2C_MASTER_RECEIVE_DISALE_CFG() (SSPCON2bits.RCEN = 0 ) 
#define I2C_MASTER_RECEIVE_ENABLE_CFG() (SSPCON2bits.RCEN = 1 )

#define MSSP_MODULE_ENABLE() (SSPCON1bits.SSPEN = 1 ) 
#define MSSP_MODULE_DISABLE() (SSPCON1bits.SSPEN = 0 ) 

#define I2C_CLOCK_STRETCH_ENABLE() (SSPCON1bits.CKP = 0) 
#define I2C_CLOCK_STRETCH_DISABLE() (SSPCON1bits.CKP = 1) 



/*section: user define data types */
typedef struct 
{
    uint8 i2c_mode_cfg ; 
    uint8 i2c_mode : 1 ;
    uint8 i2c_salave_address ; 
    uint8 i2c_slew_rate : 1 ; 
    uint8 i2c_SMBus_control : 1 ; 
    uint8 i2c_general_call : 1 ; 
    uint8 i2c_master_rec_mode : 1 ; 
    uint8 i2c_reserved : 3 ; 
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_cfg mssp_i2c_priority; 
    interrupt_priority_cfg mssp_i2c_bc_priority;
    
#endif 
}i2c_configs_t;
typedef struct 
{
    uint8 i2c_clock ; 
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
    void(*i2c_report_write_collision)(void); 
    void(*i2c_defaultinterrupthandler)(void); 
    void(*i2c_report_receive_overflow)(void); 
#endif 
    
    
    i2c_configs_t i2c_config ; 
}mssp_i2c_t;
/*section: function prototype*/
std_ReturnType mssp_i2c_init(const mssp_i2c_t * i2c_obj) ; 
std_ReturnType mssp_i2c_dinit (const mssp_i2c_t * i2c_obj) ; 
std_ReturnType mssp_i2c_master_send_start(const mssp_i2c_t * i2c_obj); 
std_ReturnType mssp_i2c_master_send_stop(const mssp_i2c_t * i2c_obj); 
std_ReturnType mssp_i2c_master_send_repeated_start(const mssp_i2c_t * i2c_obj); 
std_ReturnType mssp_i2c_master_write_blocking_data(const mssp_i2c_t * i2c_obj , uint8 data , uint8 * ack  );
std_ReturnType mssp_i2c_write_not_blocking_data(const mssp_i2c_t * i2c_obj , uint8 data ); 

std_ReturnType mssp_i2c_read_blocking_data(const mssp_i2c_t * i2c_obj , uint8 ack  , uint8 * data ); 

#endif	/* I2C_H */

