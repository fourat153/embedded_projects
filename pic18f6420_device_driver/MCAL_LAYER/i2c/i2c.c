#include "i2c.h"
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
static void (* I2C_Report_Write_Collosion_InterruptHandler)(void) = NULL ; 
static void (* i2c_defaultinterrupthandler)(void) = NULL ; 
static void (* i2c_report_receive_overflow)(void) = NULL ; 

#endif 
static inline  void MSSP_I2C_MODE_GPIO_CFG(void); 
static inline void i2c_master_mode_clock_cfg (const mssp_i2c_t * i2c_obj );
static inline void i2c_slave_mode_clock_cfg (const mssp_i2c_t * i2c_obj);

std_ReturnType mssp_i2c_init(const mssp_i2c_t * i2c_obj) 
{
    std_ReturnType ret = E_OK ; 
    if(i2c_obj == NULL) 
    {
        ret = E_NOT_ok ;  
    }
    else 
    {
        MSSP_MODULE_DISABLE();
        if(MSSP_I2C_MASTER_MODE == i2c_obj->i2c_config.i2c_mode)
        {
          i2c_master_mode_clock_cfg (i2c_obj);  
        }
        else if (MSSP_I2C_SLAVE_MODE == i2c_obj->i2c_config.i2c_mode)
        { 
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_config.i2c_general_call)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if (I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_config.i2c_general_call)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else {}
            
                SSPCON1bits.WCOL  = 0 ; 
                SSPCON1bits.SSPOV  = 0 ;
                SSPCON1bits.CKP  = 1 ; 
                SSPADD = i2c_obj->i2c_config.i2c_salave_address;
                i2c_slave_mode_clock_cfg (i2c_obj);

            
            
        }
        else 
        {
            
        }
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_config.i2c_slew_rate)
            {
                I2C_SLEW_RATE_ENABLE_CFG();
            }
        else if (I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_config.i2c_general_call)
            {
                 I2C_SLEW_RATE_DISALE_CFG();
            }
        else 
            {
                
            }
            
        if(I2C_SMBus_ENABLE== i2c_obj->i2c_config.i2c_SMBus_control)
            {
                I2C_SMBus_DISABLE_CFG();
            }
        else if (I2C_SMBus_DISABLE== i2c_obj->i2c_config.i2c_SMBus_control)
            {
                 I2C_SMBus_DISABLE_CFG();
            }
        else {}
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
        MSSP_I2C_InterruptEnable(); 
        MSSP_I2C_BUS_COL_InterruptEnable();
        MSSP_I2C_InterruptFlagClear();
        MSSP_I2C_BUS_COL_InterruptFlagClear();
        I2C_Report_Write_Collosion_InterruptHandler = i2c_obj->i2c_report_write_collision;
        i2c_defaultinterrupthandler = i2c_obj->i2c_defaultinterrupthandler ; 
        i2c_report_receive_overflow = i2c_obj->i2c_report_receive_overflow;   
#if INTERRUPT_PRIORITY_LEVELS_ENABLE   == INTERRUPT_FEATURE_ENABLE 
  INTERRUPT_PriorityLevelsEnables();
        if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_config.mssp_i2c_priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             MSSP_I2C_HighPrioritySet();
          
        }
        else if (INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_config.mssp_i2c_priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            MSSP_I2C_LowPrioritySet();
            
        }
        else {}
            
         if(INTERRUPT_HIGH_PRIORITY == i2c_obj->i2c_config.mssp_i2c_bc_priority)
        {
             INTERRUPT_GlobalInterrupthighEnable();
             MSSP_I2C_BUS_COL_HighPrioritySet();
          
        }
        else if (INTERRUPT_LOW_PRIORITY == i2c_obj->i2c_config.mssp_i2c_bc_priority)
        {
            INTERRUPT_GlobalInterruptlowEnable();
            MSSP_I2C_BUS_COL_lowPrioritySet();
        else{}
#else 
        INTERRUPT_GlobalInterruptEnable(); 
        INTERRUPT_PeripheralsInterruptEnable(); 
#endif
#endif 
     
        MSSP_I2C_MODE_GPIO_CFG();  
        MSSP_MODULE_ENABLE(); 
        
        ret = E_OK; 
    }
    return ret ;
}
std_ReturnType mssp_i2c_master_send_stop(const mssp_i2c_t * i2c_obj)
{
    std_ReturnType ret = E_OK ; 
    if(i2c_obj == NULL) 
    {
        ret = E_NOT_ok ; 
      
    }
    else 
    {
        SSPCON2bits.PEN = 1 ; 
        while(SSPCON2bits.PEN); 
        PIR1bits.SSPIF = 0 ; 
        if(STOP_BIT_DETECTED == SSPSTATbits.P)
        {
            ret = E_OK; 
        }
        else
        {
             ret = E_NOT_ok; 
        }
    }
    return ret ;
}

std_ReturnType mssp_i2c_dinit (const mssp_i2c_t * i2c_obj)
{
    std_ReturnType ret = E_OK ; 
    if(i2c_obj == NULL) 
    {
        ret = E_NOT_ok ; 
        
    }
    else 
    {    
    MSSP_MODULE_DISABLE();
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE == INTERRUPT_FEATURE_ENABLE 
MSSP_I2C_InterruptDisable(); 
MSSP_I2C_BUS_COL_InterruptDisable( ); 

#endif 
        ret = E_OK; 
         
    }
    return ret ;
}
std_ReturnType mssp_i2c_master_send_start(const mssp_i2c_t * i2c_obj)
{
    std_ReturnType ret = E_OK ; 
    if(i2c_obj == NULL) 
    {
        ret = E_NOT_ok ; 
      
    }
    else 
    {
        SSPCON2bits.SEN = 1 ; 
        while(SSPCON2bits.SEN); 
        PIR1bits.SSPIF = 0 ; 
        if(START_BIT_DETECTED == SSPSTATbits.S)
        {
            ret = E_OK; 
        }
        else
        {
             ret = E_NOT_ok; 
        }
    }
    return ret ;
}
std_ReturnType mssp_i2c_master_send_repeated_start(const mssp_i2c_t * i2c_obj)
{
    std_ReturnType ret = E_OK ; 
    if(i2c_obj == NULL) 
    {
        ret = E_NOT_ok ; 
       
    }
    else 
    {
        SSPCON2bits.RSEN = 1 ; 
        while(SSPCON2bits.RSEN ); 
        PIR1bits.SSPIF = 0 ; 
        ret = E_OK; 
         
    }
    return ret ;
}
std_ReturnType mssp_i2c_master_write_blocking_data(const mssp_i2c_t * i2c_obj , uint8 data , uint8 * ack  )
{
    std_ReturnType ret = E_OK ; 
    if(i2c_obj == NULL) 
    {
        ret = E_NOT_ok ; 
      
    }
    else 
    {
        SSPBUF= data ; 
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0 ;
        if (I2C_ACK_RECIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *ack = I2C_ACK_RECIVED_FROM_SLAVE; 
        }
        else 
        {
             *ack = I2C_ACK_NOT_RECIVED_FROM_SLAVE; 
        }
        
        ret = E_OK; 
         
    }
    return ret ;
}
std_ReturnType  mssp_i2c_read_blocking_data(const mssp_i2c_t * i2c_obj , uint8 ack  , uint8 * data )
        {
    std_ReturnType ret = E_OK ; 
    if((i2c_obj == NULL) || (data  == NULL ))  
    {
        ret = E_NOT_ok ; 
      
    }
    else 
    {
       I2C_MASTER_RECEIVE_ENABLE_CFG();
       while(!SSPSTATbits.BF);
       *data = SSPBUF;
       if(I2C_MASTER_SEND_ACK== ack )
       {
           SSPCON2bits.ACKDT =0 ;
           SSPCON2bits.ACKEN = 1 /* init ack sequance     */ ;
       }
       else if(I2C_MASTER_SEND_NOT_ACK == ack) {
           
            SSPCON2bits.ACKDT =1;
           SSPCON2bits.ACKEN = 1 /* init ack sequance     */ ;
           
        }
        else { }
        ret = E_OK;
    }
    return ret ; 
}

static inline void  MSSP_I2C_MODE_GPIO_CFG(void)
{
    TRISCbits.TRISC3 = 1 ; 
    TRISCbits.TRISC4 = 1 ; 
    
}
static inline void i2c_master_mode_clock_cfg (const mssp_i2c_t * i2c_obj)
{
    SSPCON1bits.SSPM = i2c_obj->i2c_config.i2c_mode_cfg ; 
    SSPADD = (uint8)(((_XTAL_FREQ ) / 4.0) / (i2c_obj->i2c_clock) -1 ) ;  
}

static inline void i2c_slave_mode_clock_cfg (const mssp_i2c_t * i2c_obj)
{
    SSPCON1bits.SSPM = i2c_obj->i2c_config.i2c_mode_cfg ; 
    
}


void MSSP_I2C_ISR()
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE   == INTERRUPT_FEATURE_ENABLE 

    MSSP_I2C_InterruptFlagClear();
    if(i2c_defaultinterrupthandler)
    {
        i2c_defaultinterrupthandler();
    }
#endif
}

void MSSP_I2C_BC_ISR()
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENBALE   == INTERRUPT_FEATURE_ENABLE 
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if(I2C_Report_Write_Collosion_InterruptHandler)
    {
        I2C_Report_Write_Collosion_InterruptHandler();
    }
#endif
}