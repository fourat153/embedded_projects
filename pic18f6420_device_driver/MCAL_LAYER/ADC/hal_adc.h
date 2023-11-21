/* 
 * File:   hal_adc.h
 * Author: mm77
 *
 * Created on July 24, 2023, 11:22 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/********* includes ************/
#include "hal_adc_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"
#include "../../MCAL_LAYER/mcal_std_types.h"
#include "pic18f4620.h"
#include "../Interrupt/mcal_interrupt_internal.h"



/********* macros ************/
#define ADC_AN0_ANALOGE_FUNCTIONALITY  0x0E // WHICHE PIN are configred analogue or dgital 
#define ADC_AN1_ANALOGE_FUNCTIONALITY  0x0D
#define ADC_AN2_ANALOGE_FUNCTIONALITY  0x0C
#define ADC_AN3_ANALOGE_FUNCTIONALITY  0x0B
#define ADC_AN4_ANALOGE_FUNCTIONALITY  0x0A
#define ADC_AN5_ANALOGE_FUNCTIONALITY  0x09
#define ADC_AN6_ANALOGE_FUNCTIONALITY  0x08
#define ADC_AN7_ANALOGE_FUNCTIONALITY  0x07
#define ADC_AN8_ANALOGE_FUNCTIONALITY  0x06
#define ADC_AN9_ANALOGE_FUNCTIONALITY  0x05
#define ADC_AN10_ANALOGE_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOGE_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOGE_FUNCTIONALITY 0x02
/*TWO BIT REPRESENTATION 0000 AND 0001 ARE ARLL ANLOGE*/
#define ADC_ALL_ANALOGE_FUNCTIONALITY  0x00
/*ONE BIT REPRESENTATION 0000 AND 1111 ARE ARLL DIGITAL*/
#define ADC_ALL_DIGITAL_FUNCTIONALITY  0x0F

#define ADC_RESULT_RIGHT 0X01U
#define ADC_RESULT_LEFT  0X00U

#define ADC_VOLTAGE_REFRANCE_ENABLE   0X01U
#define ADC_VOLTAGE_REFRANCE_DISABLE  0X00U

#define ADC_CONVERSION_COMPLETED 1 ; 
#define ADC_CONVERSION_IN_PROGRESS 0 ;



/********* function macros ************/
#define ADC_CONVERSION_STATUS()            (ADCON0bits.GO_nDONE )
#define ADC_START_CONVERSION()             (ADCON0bits.GODONE = 1)

#define ADC_CONVERTER_ENABLE()              (ADCON0bits.ADON = 1 ) 
#define ADC_CONVERTER_DISABLE()             (ADCON0bits.ADON = 0 ) 
// using external vref                                       
#define ADC_ENABLE_VOLTAGE_REFRANCE()    do{ADCON1bits.VCFG1 = 1 ;\
                                             ADCON1bits.VCFG0 = 1 ;\
                                            }while(0)  
// using default vref                                       
#define ADC_DISABLE_VOLTAGE_REFRANCE()    do{ADCON1bits.VCFG1  = 0 ;\
                                             ADCON1bits.VCFG0 = 0 ;\
                                            }while(0)  

#define ADC_ANALOGE_DIGITAL_PORT_CONFIG(_CONFIG)  (ADCON1bits.PCFG =_CONFIG)

#define ADC_RESULT_RIGHT_FORMAT()          (ADCON2bits.ADFM = 1 )
#define ADC_RESULT_LEFT_FORMAT()          (ADCON2bits.ADFM = 0 )

/********* user define data types ************/

typedef enum {
   ADC_CHANNEL_AN0 =  0, 
   ADC_CHANNEL_AN1,
   ADC_CHANNEL_AN2, 
   ADC_CHANNEL_AN3,
   ADC_CHANNEL_AN4,
   ADC_CHANNEL_AN5,
   ADC_CHANNEL_AN6,
   ADC_CHANNEL_AN7, 
   ADC_CHANNEL_AN8,
   ADC_CHANNEL_AN9,
   ADC_CHANNEL_AN10,
   ADC_CHANNEL_AN11,
   ADC_CHANNEL_AN12,    
}adc_channel_select_t;


typedef enum 
{
    ADC_0_TAD  =0 ,
    ADC_2_TAD  ,
    ADC_4_TAD  ,
    ADC_8_TAD  ,
    ADC_10_TAD  ,
    ADC_12_TAD  ,
    ADC_16_TAD  ,
    ADC_20_TAD  

}adc_time_aquisation_t;

typedef enum 
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0, 
    ADC_CONVERSION_CLOCK_FOSC_DIV_8 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16 , 
    ADC_CONVERSION_CLOCK_FOSC_DIV_64 ,
}adc_converison_clock_t;

typedef struct 
{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void ( * ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif 
    adc_time_aquisation_t aquisation_time; 
    adc_converison_clock_t conversion_clock;
    adc_channel_select_t  adc_channel ;
    uint8 voltage_reference : 1 ;
    uint8 result_format  : 1 ;
    uint8 adc_reserved : 6; 
    
}adc_config_t;

typedef uint16 adc_result_t;
/********* functions prototypes ************/
std_ReturnType ADC_Init(const adc_config_t * _adc ) ; 
std_ReturnType ADC_DeInit(const adc_config_t * _adc ) ; 
std_ReturnType ADC_select_channel (const adc_config_t * _adc , adc_channel_select_t channel ) ; 
std_ReturnType ADC_start_conversion(const adc_config_t * _adc );
std_ReturnType ADC_IsConversionDone (const adc_config_t * _adc , uint8 * conversion_status ) ; 
std_ReturnType ADC_GetConversionResult (const adc_config_t * _adc , adc_result_t * conversion_status ) ; 
std_ReturnType ADC_GetConversion_Blocking (const adc_config_t * _adc ,adc_channel_select_t channel , adc_result_t * conversion_status ) ; 
std_ReturnType ADC_GetConversion_interrupt(const adc_config_t * _adc ,adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

