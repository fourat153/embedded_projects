#include "mcal_interrupt_manger.h"


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
void __interrupt() interrutpMangerHigh(void)
{
     if((INTERRUPT_ENABEL == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else
    {
        
    }
      if((INTERRUPT_ENABEL == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
    {
        
    }
}

void __interrupt(low_priority) interrutpMangerLow(void)
{
    if((INTERRUPT_ENABEL == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else
    {
        
    }
}

#else

void __interrupt() interrutpManger(void)
{
    if((INTERRUPT_ENABEL == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        USART_TX_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
       USART_RX_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
    else
    {
        
    }
    
    if((INTERRUPT_ENABEL == PIE1bits.TMR1IE ) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF ))
    {
        TIMER1_ISR();
    }
    else
    {
        
    }
     if((INTERRUPT_ENABEL == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF ))
    {
        TIMER0_ISR();
    }
    else
    {
        
    }
    
    if((INTERRUPT_ENABEL == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF ))
    {
       ADC_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
    {
        
    }
    if((INTERRUPT_ENABEL == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == HIGH))
    {
        RB4_ISR();
    }
    else
    {
        
    }
     if((INTERRUPT_ENABEL == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)  && (PORTBbits.RB4 == LOW))
    {
        RB4_ISR();
    }
    else
    {
        
    }
    
     if((INTERRUPT_ENABEL == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits .CCP1IF) )
    {
       CCP1_ISR();
    }
    else
    {
        
    }
     if((INTERRUPT_ENABEL == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits .CCP2IF))
    {
       CCP2_ISR();
    }
    else
    {
        
    }
    
    if((INTERRUPT_ENABEL == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
      MSSP_I2C_ISR();
    }
    else
    {
        
    }
    
    if((INTERRUPT_ENABEL == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
      MSSP_I2C_BC_ISR();
    }
    else
    {
        
    }
    
   
}


#endif

