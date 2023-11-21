#ifndef __MAIN__H 
#define __MAIN__H

#include "Arduino.h"

#define PIN_BUTTON_1    2 
#define PIN_BUTTON_2    3
#define PIN_BUTTON_3    4 
#define PIN_BUZZER      12

//lcd 
#define PIN_LCD_RS  5 
#define PIN_LCD_RW  6 
#define PIN_LCD_EN  7 
#define PIN_LCD_D4  8 
#define PIN_LCD_D5  9 
#define PIN_LCD_D6  10 
#define PIN_LCD_D7  11

#define BUTTON_VALUE_INC_TIME 4   
#define BUTTON_VALUE_DEC_TIME 2
#define BUTTON_VALUE_ABRT     6
#define BUTTON_VALUE_SP       1     




typedef enum
{
    IDLE,
    TIME_SET,
    COUNTDOWN, 
    PAUSE,
    STAT,

}protimer_state; 

typedef enum 
{
    EVENT_HANDLED, 
    EVENT_IGNORED,
    EVENT_TRANSITION,

}event_status_t ;
typedef enum
{
    INC_TIME,
    DEC_TIME,
    TIME_TICK,
    ENTRY,
    STATRT_PAUSE,
    EXIT,
    ABRT,

}signal_t;

typedef enum 
{
    NO_PRESSED,
    BOUNCE,
    PRESSED
}button_status_t ;


typedef struct  
{
    unsigned char sig ; 
}event_t ; 

typedef struct  
{
    event_t super ; 
}protimer_user_event_t;

typedef struct 
{
    event_t super ; 
    unsigned char ss;
}protimer_tick_event_t;

typedef struct 
{
    unsigned int curr_time ; 
    unsigned int elapsed_time ; 
    unsigned int prod_time ; 
    protimer_state active_state; 

}protimer_t;

void protimer_init(protimer_t *mobj );
event_status_t protimer_state_handler_idle( protimer_t * mobj , event_t * e ); 
event_status_t protimer_state_handler_pause( protimer_t * mobj , event_t * e ) ;
event_status_t protimer_state_handler_time_set( protimer_t * mobj , event_t * e );
event_status_t protimer_state_handler_countdown( protimer_t * mobj , event_t * e ) ;
event_status_t protimer_state_handler_stat( protimer_t * mobj , event_t * e ) ;
event_status_t protimer_state_machine(protimer_t *mobj , event_t *e);


void display_time (unsigned int );
void  display_msg (String s , u8 c , u8 r );
void do_beep ();
void display_clear () ;

#endif
