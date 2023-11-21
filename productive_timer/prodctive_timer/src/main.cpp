#include <Arduino.h>
#include"main.h"
#include "lcd.h"

// put function declarations here:
static void protimer_event_dispatchar(protimer_t * mobj , event_t const * const e );
u8  process_button_pad_value(u8 btn_pad_value) ;
static void display_init(); 
protimer_t protimer ; 

void setup() {
  Serial.begin(115200);
  display_init(); 
  Serial.println("=================productive timer==================");
  Serial.println("===================================================");
  pinMode(PIN_BUTTON_1 , INPUT);
  pinMode(PIN_BUTTON_2 , INPUT);
  pinMode(PIN_BUTTON_3  , INPUT);

 
  protimer_init(&protimer);
}

void loop() {
   static uint32_t current_time = millis();
   static  protimer_tick_event_t te;
   protimer_user_event_t ue ; 
   uint8_t b1 ,b2 ,b3 ,btn_value ; 
   b1 = digitalRead(PIN_BUTTON_1);
   b2 = digitalRead(PIN_BUTTON_2);
   b3 = digitalRead(PIN_BUTTON_3);
   btn_value = (b1 << 2 ) | (b2 << 1)  | b3 ; 
   btn_value = process_button_pad_value(btn_value);
   if (btn_value)
   {
      if(btn_value == BUTTON_VALUE_INC_TIME)
      {
          ue.super.sig = INC_TIME ;
      }
      else if(btn_value == BUTTON_VALUE_DEC_TIME)
      {
          ue.super.sig = DEC_TIME ;
      }
     else  if(btn_value == BUTTON_VALUE_SP)
      {
          ue.super.sig = STATRT_PAUSE ;
      }
      else if(btn_value == BUTTON_VALUE_ABRT)
      {
          ue.super.sig = ABRT ;
      }

     protimer_event_dispatchar(&protimer , &ue.super) ;
   }
  // tick event every 100ms 
  if (millis() - current_time >= 100) 
  {
    current_time = millis() ; 
    ++te.ss;
    if(++te.ss > 10)
    {
      te.ss = 1 ; 
      protimer_event_dispatchar(&protimer , &te.super);
    }
  }

}
static void protimer_event_dispatchar(protimer_t * mobj , event_t const * const e )
{
  event_status_t status ; 
  protimer_state source , target  ;
  source = mobj->active_state ;  

  status = protimer_state_machine(mobj , e);
  if (status ==  EVENT_TRANSITION)
  {
    event_t  ee; 
    //run exit event 
    target = mobj->active_state;
    ee.sig = EXIT;
    protimer_state_machine(mobj, &ee); 
    //run entry action 
    source = mobj->active_state;
    ee.sig = ENTRY;
    protimer_state_machine(mobj, &ee); 
  }

}

u8  process_button_pad_value(u8 btn_pad_value) 
{
  static u8 btn_state  = NO_PRESSED;
  static u32 curr_time = millis();
  switch (btn_pad_value)
  {
  case NO_PRESSED:
  {
    if(btn_pad_value) 
    {
      btn_state = BOUNCE; 
      curr_time = millis(); 
    }
    break;

  }
  case  BOUNCE :
  {
  if (millis() - curr_time >= 50 )
  {
    if(btn_pad_value)
    {
      btn_state = PRESSED; 
      return btn_pad_value;
    }
    else
    {

      btn_state = NO_PRESSED;
    }
    break;
  }
  }   
  case PRESSED: 
   {
    if(!btn_pad_value )
    {
      btn_state = BOUNCE;
      curr_time = millis();
    }
    break; 
   }
  default:
    break;
  }


 return 0 ; 
}
static void display_init()
{
  lcd_begin(16,2);
  lcd_clear();
  lcd_move_cursor_L_to_R();
  lcd_set_cursor(0,0);
  lcd_no_auto_scroll();
  lcd_cursor_off();

}