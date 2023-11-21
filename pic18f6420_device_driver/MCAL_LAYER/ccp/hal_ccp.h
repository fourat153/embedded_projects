/* 
 * File:   hal_ccp.h
 * Author: mm77
 *
 * Created on August 3, 2023, 10:40 AM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/*includes*/
#include "hal_ccp_cfg.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_interrupt_internal.h"
#include "../timer3/hal_timer3.h"
/*macros*/
#define	HAL_CCP_CFG_H
#define CCP_MODULE_DISABLE                0x00 
#define CCP_CAPTURE_MODE_1_FALLING_EDGE   0x04 
#define CCP_CAPTURE_MODE_1_RAISING_EDGE   0x05 
#define CCP_CAPTURE_MODE_4_RAISING_EDGE   0x06 
#define CCP_CAPTURE_MODE_16_RAISING_EDGE  0x07 

#define CCP_COMPARE_MODE_SET_PIN_LOW      0x08 
#define CCP_COMPARE_MODE_SET_PIN_HIGH     0x09
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH  0x02 
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT 0x0A 
#define CCP_COMPARE_MODE_GEN_EVENT        0x0B 
#define CCP_PWM_MODE                      0x0C  

#define CCP_CAPTURE_READY                 0x01
#define CCP_CAPTURE_NOT_READY             0x00

#define CCP_COMPARE_READY                 0x01
#define CCP_COMPARE_NOT_READY             0x00

#define ccp_postscaler_div1      1
#define ccp_postscaler_div2      2
#define ccp_postscaler_div3      3
#define ccp_postscaler_div4      4
#define ccp_postscaler_div5      5
#define ccp_postscaler_div6      6
#define ccp_postscaler_div7      7
#define ccp_postscaler_div8      8
#define ccp_postscaler_div9      9
#define ccp_postscaler_div10     10
#define ccp_postscaler_div11     11
#define ccp_postscaler_div12     12
#define ccp_postscaler_div13     13
#define ccp_postscaler_div14     14
#define ccp_postscaler_div15     15
#define ccp_postscaler_div16     16

#define ccp_prescaler_div1      1
#define ccp_prescaler_div4      4
#define ccp_prescaler_div16     16


/*function like macros */
#define CCP1_SET_MODE(_CONFIG)       (CCP1CONbits.CCP1M == _CONFIG)
#define CCP2_SET_MODE(_CONFIG)       (CCP2CONbits.CCP2M == _CONFIG)

/*****************user define data types***********************************/
typedef enum 
{
  CCP_CAPTURE_MODE_SELECT =0,  
  CCP1_COMPARE_MODE_SELECT,
  CCP_PWM_MODE_SELECT
}ccp_mode_t;
typedef union 
{
    struct {
        uint8 ccpr_low ; 
        uint8 ccpr_high;
    };
    struct
    {
     uint16    ccpr_16 ;
    };
}CCP_PERIOD_REG_T ;

typedef enum 
{
    ccp1_select = 0 , 
    ccp2_select 
}ccp_instance;

typedef enum 
{
    ccp1_ccp2_timer3 = 0 , 
    ccp1_timer1_ccp2_timer3,
    ccp1_ccp2_time1
}ccp_capture_timer_t ;

typedef struct 
{  
   ccp_capture_timer_t capture_timer_sele; 
   uint8 ccp_sub_mode ; 
   ccp_mode_t CCP_mode ;
   pin_config_t pin ; 
   ccp_instance ccp_instance ; 
#if CCP1_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
    void ( * CCP1_InterruptHandler)(void);
    interrupt_priority_cfg ccp1_priority;
#endif 
    
#if CCP2_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
    void ( * CCP2_InterruptHandler)(void);
    interrupt_priority_cfg ccp2_priority;
#endif 
    
#if ((CCP_CFG_PWM_MODE_SELECTED  == CCP2_CFG_SELECT_MODE_SELECTED ) || (CCP_CFG_PWM_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED ))
    uint32 PWM_Frequency ;
    uint8 timer2_postscaler_value : 4 ; 
    uint8 timer2_prescaler_value : 2 ; 
#endif             
    
}ccp_t;



/*******************function prototypes****************************/
std_ReturnType CCP_Init(const ccp_t * ccp_obj);
std_ReturnType CCP_DeInit(const ccp_t * ccp_obj);
#if (CCP1_CFG_CAPTURE_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED)
std_ReturnType CCP1_IsCaptureIsReady(uint8  * capture_status);
std_ReturnType CCP1_Capture_Mode_Read_Value(uint8  * capture_value );
#endif 

#if (CCP1_CFG_COMPARE_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED)
std_ReturnType CCP1_IsCompareComplete(uint8  * compare_status);  
std_ReturnType CCP1_Compare_Mode_set_Value(uint16   compare_value );

        
#endif 
#if (CCP_CFG_PWM_MODE_SELECTED  == CCP1_CFG_SELECT_MODE_SELECTED)
 std_ReturnType CCP_PWM_Mode_Set_Duty(uint8  duty  , const ccp_t * ccp_obj );
 std_ReturnType CCP_PWM_Start(const  ccp_t * ccp_obj);
 std_ReturnType CCP_PWM_Stop(const  ccp_t * ccp_obj);

#endif 

#endif	/* HAL_CCP_H */

