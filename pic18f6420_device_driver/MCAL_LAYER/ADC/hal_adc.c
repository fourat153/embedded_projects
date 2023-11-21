#include "hal_adc.h"
static inline void adc_input_channel_port_config(adc_channel_select_t channel);
static inline void select_result_format(const adc_config_t  * _adc);
static inline void configure_voltage_ref (const adc_config_t  * _adc);

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif 
/**
 * 
 * @param _adc
 * @return 
 */
std_ReturnType ADC_Init(const adc_config_t * _adc ) 
{
    std_ReturnType ret = E_OK; 
    if (NULL == _adc) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        /*disable ADC*/ 
        ADC_CONVERTER_DISABLE();
        /*aquisation time */
        ADCON2bits.ACQT = _adc->aquisation_time;
        /*configure the conversion clock*/
        ADCON2bits.ADCS = _adc->conversion_clock ; 
        /*select channel to read from */
        ADCON0bits.CHS = _adc->adc_channel ;  
        adc_input_channel_port_config(_adc->adc_channel);
        /*interrupt config*/ 
        /*same in all modules */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY  == _adc->priority)
        {   
            ADC_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY  == _adc->priority)
        {
            ADC_LowPrioritySet();
        }
        else{}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralsInterruptEnable();
#endif
        ADC_InterruptHandler= _adc->ADC_InterruptHandler;
#endif 
        /*format right or left */
        select_result_format(_adc);
        /*voltage ref */
        configure_voltage_ref(_adc);
        /*enable adc*/
        
        ADC_CONVERTER_ENABLE();

   
    
   
    }
   return ret ;      
}
std_ReturnType ADC_DeInit(const adc_config_t * _adc ) 
{
    std_ReturnType ret = E_OK; 
    if (NULL == _adc) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        /*adc disable*/
         ADC_CONVERTER_DISABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
         ADC_InterruptDisable() ;
#endif 
    
   
    }
   return ret ;      
}
/*change channel any time  first channel is default channel ba3ed nbadlou*/
std_ReturnType ADC_select_channel (const adc_config_t * _adc , adc_channel_select_t channel ) 
{
   std_ReturnType ret = E_OK; 
    if (NULL == _adc) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        ADCON0bits.CHS  = channel; 
        adc_input_channel_port_config(channel);
        ret = E_OK;
    }
   return ret ;     
}
std_ReturnType   ADC_start_conversion(const adc_config_t * _adc )
{
    std_ReturnType ret = E_OK; 
    if (NULL == _adc) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
     ADC_START_CONVERSION();
     ret = E_OK;
    }
   return ret ;      
}
std_ReturnType ADC_IsConversionDone (const adc_config_t * _adc , uint8 * conversion_status )
{
    std_ReturnType ret = E_OK; 
    if ((NULL == _adc) || (NULL == conversion_status)) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
     *conversion_status  = (uint8)(!(ADCON0bits.GO_nDONE)); // si 1 raj3li 0 mzelt t5dem else 0 raj3li 1 true is done 
     ret = E_OK;
    }
   return ret ;      
}
std_ReturnType ADC_GetConversionResult (const adc_config_t * _adc , adc_result_t * conversion_status ) 
{
    std_ReturnType ret = E_OK; 
    if (NULL == _adc) 
        {
            ret = E_NOT_ok; 
        }
    else 
    {
      if (ADC_RESULT_RIGHT == _adc->result_format)
    {
        *conversion_status = (adc_result_t) ((ADRESH<<8) + ADRESL);
    }
    else if (ADC_RESULT_LEFT  == _adc->result_format)
    {
      *conversion_status = (adc_result_t) (((ADRESH<<8) + ADRESL)>> 6 );
    }
     ret = E_OK;
    }
   return ret ;      
}
std_ReturnType ADC_GetConversion_Blocking (const adc_config_t * _adc ,adc_channel_select_t channel , adc_result_t * conversion_result ) 
{
    std_ReturnType ret = E_OK;  
    if ((NULL == _adc)||(NULL == conversion_result))  
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        ret = ADC_select_channel(_adc,channel);
        ret = ADC_start_conversion(_adc);
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc,conversion_result);
        
    }
   return ret ;      
}

std_ReturnType ADC_GetConversion_interrupt(const adc_config_t * _adc ,adc_channel_select_t channel) 
{
    std_ReturnType ret = E_OK;  
    if (NULL == _adc)  
        {
            ret = E_NOT_ok; 
        }
    else 
    {
        ret = ADC_select_channel(_adc,channel);
        ret = ADC_start_conversion(_adc);
        
    }
   return ret ;      
}

static inline void adc_input_channel_port_config(adc_channel_select_t channel)
{
    /*setting the configuration of the bit */
    switch(channel)
    {
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA  , _TRISA_RA0_POSN); break ;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA  , _TRISA_RA1_POSN); break ;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA  , _TRISA_RA2_POSN); break ;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA  , _TRISA_RA3_POSN); break ;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA  , _TRISA_RA5_POSN); break ;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE  , _TRISE_RE0_POSN); break ;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE  , _TRISE_RE1_POSN); break ;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE  , _TRISE_RE2_POSN); break ;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB  , _TRISB_RB2_POSN); break ;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB  , _TRISB_RB3_POSN); break ;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB  , _TRISB_RB1_POSN); break ;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB  , _TRISB_RB4_POSN); break ;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB  , _TRISB_RB0_POSN); break ;

    }
}
static inline void select_result_format(const adc_config_t  * _adc)
{
    if (ADC_RESULT_RIGHT == _adc->result_format)
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if (ADC_RESULT_LEFT  == _adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_ref (const adc_config_t  * _adc)
{
    if (ADC_VOLTAGE_REFRANCE_ENABLE == _adc->voltage_reference)
    {
        ADC_ENABLE_VOLTAGE_REFRANCE();
    }
    else if (ADC_VOLTAGE_REFRANCE_DISABLE  == _adc->voltage_reference)
    {
        ADC_DISABLE_VOLTAGE_REFRANCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFRANCE();
    }
} void ADC_ISR(void )
{
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
     
}