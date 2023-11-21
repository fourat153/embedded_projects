/* 
 * File:   application.c
 * Author: mm77
 *
 * Created on June 1, 2023, 9:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4620.h>
#include "application.h"
#include "timer3/hal_timer3.h"

//#include "ecu_button.h"
/****************************led*******************************************/

/*pin_config_t led_2 = {
    .port = PORTC_INDEX,
    .pin = PIN1 ,
    .direction = OUTPUT_DIRECTION,
    .logic = LOW 
};*/
/*pin_config_t led_3 = {
    .port = PORTC_INDEX,
    .pin = PIN2 ,
    .direction = OUTPUT_DIRECTION,
    .logic = LOW 
};*/
/*pin_config_t btn1 = {
    .port = PORTD_INDEX,
    .pin = PIN0 ,
    .direction = INPUT_DIRECTION,
    .logic = LOW 
};*/

led_t led1 = {
    .port_name = PORTD_INDEX ,              // 4 the bit for future  upgrade 
    .pin = PIN0 ,
    .led_status  = LOW,    
}; 
led_t led2 = {
    .port_name = PORTC_INDEX ,              // 4 the bit for future  upgrade 
    .pin = PIN1 ,
    .led_status  = LOW,    
};
led_t led3 = {
    .port_name = PORTC_INDEX ,              // 4 the bit for future  upgrade 
    .pin = PIN2 ,
    .led_status  = LOW,    
};

led_t led4 = {
    .port_name = PORTC_INDEX ,              // 4 the bit for future  upgrade 
    .pin = PIN3,
    .led_status  = LOW,    
};



/*******************************push_button*******************************/
/* button_t button_high = { .button_pin.port = PORTC_INDEX ,.button_pin.direction = INPUT_DIRECTION,
.button_pin.pin = PIN2 , .button_pin.logic = LOW, 
.button_connection = BUTTON_ACTIVE_HIGH, // ACTIVE WHEN I PUSH BUTTON 
.button_stats = BUTTON_RELEASED,       
};

button_t button_low = { .button_pin.port = PORTD_INDEX ,.button_pin.direction = INPUT_DIRECTION,
.button_pin.pin = PIN0 , .button_pin.logic = HIGH, 
.button_connection = BUTTON_ACTIVE_LOW, // ACTIVE WHEN I release  BUTTON 
.button_stats = BUTTON_RELEASED,       // INTI STATUS OF BUTTON  
};*/
/**********************************relay ************************************/
/*relay_t relay1 = { .relay_port = PORTC_INDEX  , .relay_pin = PIN0 , .relay_status = RELAY_OFF_STATUS };*/
/**********************************motor**************************************/
/*dc_motor_t motor1 = {
   .dc_motor[0].port = PORTC_INDEX , 
   .dc_motor[0].pin = PIN0 ,
   .dc_motor[0].logic = DC_MOTOR_STATUS_OFF,
   .dc_motor[0].direction = OUTPUT_DIRECTION,
   
   .dc_motor[1].port = PORTC_INDEX , 
   .dc_motor[1].pin = PIN1,
   .dc_motor[1].logic = DC_MOTOR_STATUS_OFF,
   .dc_motor[1].direction = OUTPUT_DIRECTION,
};

dc_motor_t motor2 = {
   .dc_motor[0].port = PORTC_INDEX , 
   .dc_motor[0].pin = PIN2 ,
   .dc_motor[0].logic = DC_MOTOR_STATUS_OFF,
   .dc_motor[0].direction = OUTPUT_DIRECTION,
   
   .dc_motor[1].port = PORTC_INDEX , 
   .dc_motor[1].pin = PIN3,
   .dc_motor[1].logic = DC_MOTOR_STATUS_OFF,
   .dc_motor[1].direction = OUTPUT_DIRECTION,
};*/
//button_stats_t button_status2 = BUTTON_RELEASED;
//button_stats_t button_status1 = BUTTON_RELEASED;
    //uint8 number = 0 ; 
    //uint8 number_bcd = 0 ;
//uint8 hours = 23 ;
//uint8 minutes = 59; 
//uint8 secondes = 59; 
/*direction_t led1_direction_status; 
uint8   port_status ;*/

/********************************************************************************/
/*segemnt_type_t seg1 = { 
    .segment_pins[0].port = PORTC_INDEX, 
    .segment_pins[0].pin  = PIN0 ,
    .segment_pins[0].logic = LOW , 
    .segment_pins[0].direction = OUTPUT_DIRECTION,
    
    .segment_pins[1].port = PORTC_INDEX, 
    .segment_pins[1].pin  = PIN1 ,
    .segment_pins[1].logic = LOW , 
    .segment_pins[1].direction = OUTPUT_DIRECTION,
    
    .segment_pins[2].port = PORTC_INDEX, 
    .segment_pins[2].pin  = PIN2 ,
    .segment_pins[2].logic = LOW , 
    .segment_pins[2].direction = OUTPUT_DIRECTION,
    
    .segment_pins[3].port = PORTC_INDEX, 
    .segment_pins[3].pin  = PIN3 ,
    .segment_pins[3].logic = LOW , 
    .segment_pins[3].direction = OUTPUT_DIRECTION,
   
};*/
/**************************************************************************/

std_ReturnType ret = E_NOT_ok; 

const uint8 customChar[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};

uint8 value = 0;

uint8 counter = 1; 
uint8 counter_string[4];

void Int0_APP_ISR(void)
{
    led_turn_toggle(&led1);
   
}

void Int1_APP_ISR(void)
{
    led_turn_toggle(&led2);
}

void Int2_APP_ISR(void)
{
    led_turn_toggle(&led3);
}
Interrupt_INTx_t int0_obj = 
{
    .EXTERNAL_INTRRUPT_HANDLER = Int0_APP_ISR, 
    .edge  = INERRUPT_RISING_EDGE,
    .priority  =INTERRUPT_HIGH_PRIORITY,
    .source = INERRUPT_EXTARNAL_INT0,
    .mcu_pin.direction = INPUT_DIRECTION,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN0,
};

Interrupt_INTx_t int1_obj = 
{
    .EXTERNAL_INTRRUPT_HANDLER = Int1_APP_ISR, 
    .edge  = INERRUPT_RISING_EDGE,
    .priority  =INTERRUPT_LOW_PRIORITY,
    .source = INERRUPT_EXTARNAL_INT1,
    .mcu_pin.direction = INPUT_DIRECTION,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN1,
};

Interrupt_INTx_t int2_obj = 
{
    .EXTERNAL_INTRRUPT_HANDLER = Int2_APP_ISR, 
    .edge  = INERRUPT_RISING_EDGE,
    .priority  =INTERRUPT_HIGH_PRIORITY,
    .source = INERRUPT_EXTARNAL_INT1,
    .mcu_pin.direction = INPUT_DIRECTION,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = PIN2,
};

void RB4_INT_APP_ISR(void)
{
    led_turn_toggle(&led1);
    __delay_ms(500) ;
}

Interrupt_RBx_t int0_1obj = {
    .EXTERNAL_INTRRUPT_HANDLER = RB4_INT_APP_ISR,
    .mcu_pin.direction = INPUT_DIRECTION,
    .mcu_pin.port = PORTB_INDEX,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.pin = PIN4,
};
uint16 adc_res_1 ,adc_res_2,adc_res_3,adc_res_4;
/******************************************************/
void ADC_DefaultInterruptHandler(void);
uint16 volatile adc_res_flag = 0 ;
 adc_config_t ADC_1 = {
        .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
        .adc_channel = ADC_CHANNEL_AN0, 
        .aquisation_time = ADC_12_TAD,
        .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
        .result_format = ADC_RESULT_RIGHT,
        .voltage_reference = ADC_VOLTAGE_REFRANCE_DISABLE,
  };
void ADC_DefaultInterruptHandler(void)
{
    std_ReturnType ret = E_NOT_ok; 
    ret = ADC_GetConversionResult (&ADC_1 , &adc_res_1  ) ; 
};
uint16 volatile flag_t = 0 ; 
void Timer0_DefaultInterruptHandler(void)
{
    std_ReturnType ret = E_NOT_ok; 
    led_turn_toggle(&led1);
};
uint8 adc_res1_txt[6];

timer0_t timer0_0bj = {
    .TIMER0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_TIMER_MODE, 
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG  ,
    .prescaler_value = timer0_prescaler_div8,
    .timer0_preload_value = 3036
};
/********************************************************************/
volatile uint32 counter_timer1 = 0 ; 
void Timer1DefaultInterruptHandler(void)
{
    counter_timer1++;
    led_turn_toggle(&led1);
}
void init_timer1()
{
    timer1_t obj_timer1 ; 
    obj_timer1.TIMER1_InterruptHandler = Timer1DefaultInterruptHandler;
    obj_timer1.priority = INTERRUPT_LOW_PRIORITY;
    obj_timer1.timer1_mode = TIMER1_TIMER_MODE;
    obj_timer1.timer1_prescaler_value = timer1_prescaler_div8; 
    obj_timer1.timer1_preload_value = 15536;
    obj_timer1.timer1_reg_wr_mode = TIMER1_16BIT_REGISTER_MODE;
    Timer1_init(&obj_timer1);
}

volatile uint32 counter_timer3 = 0 ; 
void Timer3DefaultInterruptHandler(void)
{
    counter_timer3++;
    led_turn_toggle(&led1);
}



volatile uint32 counter_timer2 = 0 ; 
void Timer2DefaultInterruptHandler(void)
{
    counter_timer2++;
    led_turn_toggle(&led1);
}
volatile uint8 ccp_interrupt_flag_counter = 0 ; 
void  CCP1_InterruptHandler()
    {
       ccp_interrupt_flag_counter = 5;
    }
uint8 volatile counter_usart = 0 ;
uint8 volatile counter_usart1 = 0 ;

void  USART_TxInterruptHandler()
    {
    counter_usart++;
    }
void  USART_RxInterruptHandler()
    {
    uint8 data_temp = 0;
    counter_usart1++;
    data_temp = RCREG; 
    }

void usart_module_init()
    {
        usart_t usart_obj ; 
        std_ReturnType ret = E_NOT_ok ; 
        usart_obj.bauderate = 9600 ; 
        usart_obj.baude_config = BAUDERATE_ASYN_8BIT_LOW_SPEED;
        usart_obj.usart_tx_config.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
        usart_obj.usart_tx_config.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE ; 
        usart_obj.usart_tx_config.usart_tx_reserved = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE; 
        
        usart_obj.usart_rx_config.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
        usart_obj.usart_rx_config.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE ; 
        usart_obj.usart_rx_config.usart_rx_reserved = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE; 
        
        usart_obj.EUSART_RX_INTERRUPT_HANDLER =  USART_RxInterruptHandler ; 
        usart_obj.EUSART_FRAMERROR_INTERRUPT_HANDLER = NULL ; 
        usart_obj.EUSART_OVERRUN_INTERRUPT_HANDLER  = NULL ; 
        usart_obj.EUSART_TX_INTERRUPT_HANDLER= USART_TxInterruptHandler;
        
        ret = usart_async_Init(&usart_obj);
    }
   uint8 ret_uart = 0 ; 
 uint8 ack ;
 mssp_i2c_t i2c_obj; 
 void mssp_i2c_send_1_byte(uint8 slave_address , uint8  data )
 {
    std_ReturnType ret = E_NOT_ok ; 
    ret = mssp_i2c_master_send_start(&i2c_obj);
    ret = mssp_i2c_master_write_blocking_data(&i2c_obj , slave_address ,&ack ); 

      
    ret = mssp_i2c_master_write_blocking_data(&i2c_obj , 0x33 ,&ack ); 

    ret = mssp_i2c_master_send_stop(&i2c_obj);
        
 }
#define slave1 0x060  
#define slave2 0x062 
 volatile uint8 counter_i2c2 = 0 ; 
 volatile uint8 data2 ; 
 void i2c_mssp_defaultinterrupthandler2()
 {
     I2C_CLOCK_STRETCH_ENABLE();
     if((SSPSTATbits.R_nW == 0 )  && (SSPSTATbits.D_nA == 0))
     {
         uint8 dummy_buffer = SSPBUF;
         while(!SSPSTATbits.BF);
         data2 = SSPBUF;
     }
     else{}
     I2C_CLOCK_STRETCH_DISABLE();
 }
int main() {



i2c_obj.i2c_clock = 100000; 
i2c_obj.i2c_config.i2c_mode = MSSP_I2C_SLAVE_MODE;
i2c_obj.i2c_config.i2c_salave_address = slave2 ; 
i2c_obj.i2c_config.i2c_mode_cfg = I2C_SLAVE_MODE_7BITS_ADDRESS; 
i2c_obj.i2c_config.i2c_SMBus_control = I2C_SMBus_DISABLE;
i2c_obj.i2c_config.i2c_slew_rate = I2C_SLEW_RATE_DISABLE; 
i2c_obj.i2c_config.i2c_general_call = I2C_GENERAL_CALL_DISABLE ; 
i2c_obj.i2c_report_receive_overflow = NULL; 
i2c_obj.i2c_defaultinterrupthandler = i2c_mssp_defaultinterrupthandler2; 
i2c_obj.i2c_report_write_collision = NULL; 

ret = mssp_i2c_init(&i2c_obj);
//ret = mssp_i2c_master_send_start(&i2c_obj);
//__delay_ms(1000);
////ret = mssp_i2c_master_send_repeated_start(&i2c_obj);
//ret = mssp_i2c_master_write_blocking_data(&i2c_obj , 0x022 ,&ack ); 
//__delay_ms(1000);
//ret = mssp_i2c_master_send_stop(&i2c_obj);
//__delay_ms(1000);
/*******************************************************************************/    
//    std_ReturnType ret = E_NOT_ok; 
//     ret = led_initialize(&led1); 
//     usart_module_init() ; 
//     
  
    //ret= Timer0_init(&timer0_0bj);
  // ret= Interrupt_RBTx_Init(&int0_1obj);
   //application_intialize();
   //ret = Interrupt_INTx_Init(&int0_1obj);
   // ret = Interrupt_INTx_Init(&int1_obj);
   // ret = Interrupt_INTx_Init(&int2_obj);
   
   // ret = led_initialize(&led2); 
   // ret = led_initialize(&led3); 
    //ret = lcd_4bit_send_char(&lcd1, 'D');
   
   //ret= lcd_4bit_send_string_data(&lcd1 ,"Aaaaa" );
    
    //ret =  initialize_button (&button_high);
    //ret =  initialize_button (&button_low);
    //int flag = 0;
   // ret = lcd_8bit_send_string_data_pos(&lcd2 , 1 , 1 , "counter: ");
    //ret= Data_eeprom_write_byte(0x3ff, 0 );
    //uint8 result_eeprom_read = 0  ; 
    /*************************************************************************/
  // ret=  lcd_8bit_send_string_data_pos(&lcd2 , 1, 7, "ADC TEST"  );
  // __delay_ms(2000);
  // ret = lcd_8bit_send_command(&lcd2 ,_LCD_CLEAR);
  // ret=  lcd_8bit_send_string_data_pos(&lcd2 , 1, 1, "POT0 :"  );
  // ret=  lcd_8bit_send_string_data_pos(&lcd2 , 2, 1, "POT1 :"  );
  // ret=  lcd_8bit_send_string_data_pos(&lcd2 , 3, 1, "POT2 :"  );
  // ret=  lcd_8bit_send_string_data_pos(&lcd2 , 4, 1, "POT3 :"  );
  
   // ret = ADC_Init(&ADC_1);
  /****************************************************************************/
   // init_timer1();
  /*****************************************************************************/
   /* timer2_t timer2 ; 
    timer2.TIMER2_InterruptHandler = NULL;
    timer2.timer2_postscaler_value = ccp_postscaler_div1; 
    timer2.timer2_preloaded_value = ccp_prescaler_div1; 
    timer2.timer2_prescaler_value = timer2_prescaler_div1; 
    //timer2.priority = INTERRUPT_LOW_PRIORITY;

    ret = Timer2_init(&timer2) ; */
    /****************************************************************************/
   /* timer3_t obj_timer3 ; 
    obj_timer3.TIMER3_InterruptHandler = Timer3DefaultInterruptHandler;
    obj_timer3.priority = INTERRUPT_LOW_PRIORITY;
    obj_timer3.timer3_mode = TIMER3_TIMER_MODE;
    obj_timer3.timer3_prescaler_value = timer3_prescaler_div8; 
    obj_timer3.timer3_preload_value = 15536;
    obj_timer3.timer3_reg_wr_mode = TIMER3_16BIT_REGISTER_MODE;
    Timer3_init(&obj_timer3);*/
   /* uint16 volatile result_timer3 = 0 ; 
    timer3_t obj_timer3_counter ; 
    obj_timer3_counter.TIMER3_InterruptHandler = NULL;
    obj_timer3_counter.priority = INTERRUPT_LOW_PRIORITY;
    obj_timer3_counter.timer3_mode = TIMER3_COUNTER_MODE;
    obj_timer3_counter.timer3_prescaler_value = timer3_prescaler_div1; 
    obj_timer3_counter.timer3_preload_value = 0;
    obj_timer3_counter.timer3_reg_wr_mode = TIMER3_16BIT_REGISTER_MODE;
    obj_timer3_counter.timer3_counter_mode = TIMER3_SYNC_COUNTER_MODE;
   // Timer3_init(&obj_timer3_counter);*/
    /*********************************************************************************/
    /* ccp_t ccp2_obj ; 
    ccp2_obj.CCP1_InterruptHandler = NULL ; 
    ccp2_obj.CCP1_mode = CCP_PWM_MODE_SELECT ; 
    ccp2_obj.ccp_instance = ccp2_select;
    ccp2_obj.PWM_Frequency = 20000; // using equation 
    ccp2_obj.timer2_postscaler_value = ccp_postscaler_div1 ; 
    ccp2_obj.timer2_prescaler_value = ccp_prescaler_div1 ; 
    ccp2_obj.pin.direction = OUTPUT_DIRECTION; 
    ccp2_obj.pin.port= PORTC_INDEX;
    ccp2_obj.pin.pin = PIN1;
    CCP_Init(&ccp2_obj);
    ret = CCP_PWM_Mode_Set_Duty(75, &ccp2_obj);
    ret =  CCP_PWM_Start(&ccp2_obj);
    */
    
   /* ccp_t ccp1_obj ; 
    ccp1_obj.CCP1_InterruptHandler = CCP1_InterruptHandler;
    ccp1_obj.ccp_sub_mode = CCP_CAPTURE_MODE_1_RAISING_EDGE;
    //ccp1_obj.capture_timer_sele = ccp1_ccp2_time1 ;
    ccp1_obj.ccp_instance = ccp1_select;
    ccp1_obj.CCP_mode = CCP_CAPTURE_MODE_SELECT ;
    ccp1_obj.pin.direction = INPUT_DIRECTION; 
    ccp1_obj.pin.port= PORTC_INDEX;
    ccp1_obj.pin.pin = PIN2;
    ret = CCP_Init(&ccp1_obj);*/
    
    /********************************************************************/
 
   
    
    while (1)   
    {      
       
//        ret = mssp_i2c_master_send_start(&i2c_obj);
//        __delay_ms(1000);
//        //ret = mssp_i2c_master_send_repeated_start(&i2c_obj);
//        ret = mssp_i2c_master_write_blocking_data(&i2c_obj , 0x33 ,&ack ); 
//       // __delay_ms(1000);
//        ret = mssp_i2c_master_send_stop(&i2c_obj);
//        __delay_ms(1000);
        
       // ret = usart_async_WriteStringByteBlocking("python\r" , 5);
       // ret = usart_async_WriteByteBlocking( 'a' ); 
       // __delay_ms(500); 
       // ret = usart_async_WriteByteBlocking( 'b' ); 
       // __delay_ms(500);
        //ret = usart_async_WriteStringByteBlocking("ahmed \r" , 5);
        //__delay_ms(500);
       // ret = usart_async_ReadByteBlocking(&ret_uart);
        //ret = Timer3_read_value(&obj_timer3_counter , &result_timer3);
       // ret = ADC_GetConversion_Blocking(&ADC_1 , ADC_CHANNEL_AN0 , &adc_res_1);
       // ret = ADC_GetConversion_Blocking(&ADC_1 , ADC_CHANNEL_AN1 , &adc_res_2);
       // ret = ADC_GetConversion_Blocking(&ADC_1 , ADC_CHANNEL_AN2 , &adc_res_3);
       // ret = ADC_GetConversion_Blocking(&ADC_1 , ADC_CHANNEL_AN3 , &adc_res_4);
        // ret = ADC_GetConversion_interrupt(&ADC_1 ,ADC_CHANNEL_AN0 );
        // ret = convert_short_to_string(adc_res_1 , &adc_res1_txt);
        // ret=  lcd_8bit_send_string_data_pos(&lcd2 , 1, 7, &adc_res1_txt );
       /*  ret= Data_eeprom_write_byte(0x3ff, counter++);
        
         __delay_ms(1000);
         ret = Data_eeprom_read_byte(0x3ff,&result_eeprom_read);
         if (5 == result_eeprom_read)
         {
             ret = led_turn_on(&led1);
         } */
        
       //  ret = lcd_8bit_send_custom_charactare(&lcd2 , 1  , 20 , customChar , 0);
       // ret = convert_byte_to_string(counter ,counter_string );
       // ret = lcd_8bit_send_string_data_pos(&lcd2 , 1 , 12 , counter_string); 
        
       // ret = led_turn_on(&ledA);
       // _delaywdt(1000000);
       // ret = led_turn_off(&ledA);
       // _delaywdt(1000000);
        //ret = read_button_status(&button_high, &button_status1);
        //ret = read_button_status(&button_low, &button_status2);
        //if ((button_status1 == BUTTON_PRESSED) && flag == 0 )
        //{
            //ret = led_turn_on(&ledA);
           // flag = 1 ; 
            
       // }
        //else if ((button_status1 == BUTTON_PRESSED) && flag == 1 )
        //{
            //ret  = led_turn_off(&ledA);
           // flag =0; 
       // }
        //ret =relay_turn_on(&relay1);
      // _delay(5000000); 
       //ret = relay_turn_off(&relay1);
      // _delay(5000000);   
        
       
       // ret = dc_motor_move_left(&motor2);
       // ret = dc_motor_move_left(&motor1);
         
        //_delay(3000000);
        
       // ret = dc_motor_stop(&motor2);
        //ret = dc_motor_stop(&motor1);
       
        
        //_delay(3000000);
        //ret = dc_motor_move_right(&motor2);
       // ret = dc_motor_move_right(&motor1);
       // _delay(3000000);
      
       // number_bcd = (( (number % 10 ) | ((number / 10) << 4 )));
       // ret = gpio_port_wirte_logic(PORTC_INDEX, number_bcd);
       // number++ ;         
       // ret = gpio_port_wirte_logic(PORTC_INDEX , 5 );
       //  _delay(2000000);
       // ret = gpio_port_wirte_logic(PORTD_INDEX ,0xFF );
      //  _delay(2000000);
      //  ret = gpio_port_wirte_logic(PORTC_INDEX , 6 );
      //   ret = gpio_port_wirte_logic(PORTD_INDEX ,0x00 );
      //  _delay(2000000);
  /**********************************************************************/
        
    /*    for (int i = 0  ; i<50 ; i++)
        {
        ret = gpio_port_wirte_logic(PORTD_INDEX , 0x3E );
        ret = gpio_port_wirte_logic(PORTC_INDEX , hours / 10 );
        
        __delay_us(3333); 
                
        ret = gpio_port_wirte_logic(PORTD_INDEX , 0x3D );
        ret = gpio_port_wirte_logic(PORTC_INDEX , hours % 10 );
         _delay(3333);               
        ret = gpio_port_wirte_logic(PORTD_INDEX , 0x3B);
        ret = gpio_port_wirte_logic(PORTC_INDEX , minutes / 10 );
        
        __delay_us(3333);
        
        ret = gpio_port_wirte_logic(PORTD_INDEX , 0x37 );
        ret = gpio_port_wirte_logic(PORTC_INDEX , minutes % 10 );
        
        __delay_us(3333);
        
        ret = gpio_port_wirte_logic(PORTD_INDEX , 0x2F );
        ret = gpio_port_wirte_logic(PORTC_INDEX , secondes / 10 );
        
       __delay_us(3333);
        
        ret = gpio_port_wirte_logic(PORTD_INDEX , 0x1F );
        ret = gpio_port_wirte_logic(PORTC_INDEX ,secondes % 10 );
        __delay_us(3333);
        
     }
        secondes++ ;
        if ( secondes == 60)
        {
         minutes++; 
         secondes = 0 ;
        }
        if (minutes == 60 ) 
        {
            minutes =0 ;
            hours++ ; 
        }
        if (hours == 24) 
        {
            hours = 0 ;
        }  */
   /*******************************************************************************/
       /* for (uint8 i = 0; i < 10 ; i++)
        {
        ret = seven_segment_write_number(&seg1 , i) ;
        __delay_ms(2000);
        }
}*/
    
  
   
   // ret = keypad_get_value(&key_pad_obj , &value ) ;
    
}
   return (EXIT_SUCCESS);
}
void application_intialize(void)
{
     /* ret = gpio_pin_read_logic(&btn1,&push_button_status);
        ret = gpio_pin_intialize(&led_3); 
        if(push_button_status == HIGH)
        {
            ret = gpio_pin_wirte_logic(&led_1 ,HIGH);
        } 
        else
        {
            ret = gpio_pin_wirte_logic(&led_1,LOW);
        }*/
        //ret = gpio_pin_toggle_logic(&led_3);
        //_delaywdt(100000);
     //ret = gpio_port_initialize_port(PORTC_INDEX , 0x00);
    //ret = gpio_port_get_direction_status(PORTC_INDEX  , &port_status );
        //ret = gpio_port_wirte_logic(PORTC_INDEX , 0x55);
        //ret = gpio_port_wirte_logic(PORTC_INDEX , 0xAA);
         //led_initialize(&ledA) ;
         //led_initialize(&ledB) ;
         //relay_initialize(&relay1);
         //ret =dc_motor_intialize(&motor1);
         //  ret =dc_motor_intialize(&motor2);
    //ret = gpio_port_initialize(PORTC_INDEX  , 0x0) ;
    //ret = gpio_port_initialize(PORTD_INDEX  , 0xc0) ; // intilaize only first 6 bits in port c to 0 because it's a common cathode  
  
   // ret = seven_segment_initialize(&seg1); // spacial case to test the code cuz the compiler optimiz the code and that prevetn seg to be vizilized in debuging 
    //std_ReturnType ret = E_NOT_ok ;
      //ecu_layer_intialize();
    
}

