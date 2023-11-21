#include "main.h"
#include "lcd.h"
void protimer_init(protimer_t *mobj )
{
    event_t ee; 
    mobj->active_state =IDLE; 
    mobj->prod_time = 0 ; 
    protimer_state_machine(mobj , &ee );  
}
event_status_t  protimer_state_machine(protimer_t *mobj , event_t *e)
{
    switch (mobj->active_state)
    {
    case IDLE:
        return protimer_state_handler_idle(mobj , e); 
    case TIME_SET :
        return  protimer_state_handler_time_set(mobj , e) ; 
    case COUNTDOWN:
       return protimer_state_handler_countdown(mobj , e); 
    case STAT :
       return  protimer_state_handler_stat(mobj , e) ;     
    case PAUSE :
       return  protimer_state_handler_pause(mobj , e) ; 
    default:
        break;
    }
}


event_status_t protimer_state_handler_idle( protimer_t * mobj , event_t * e ) 
{
    switch (e->sig) // implement a case for all signal entry , exit ......
    {
    case ENTRY:
            mobj->curr_time = 0 ; 
            mobj->elapsed_time = 0 ; 
            display_time(0);
            display_msg("set time"); 
            return EVENT_HANDLED;  

    case EXIT:
             display_clear();
            return EVENT_HANDLED;
    case STATRT_PAUSE:
            mobj->active_state = STAT;      
            return EVENT_TRANSITION; 
    case INC_TIME:
            mobj->curr_time +=60 ;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSITION;
    case DEC_TIME:
         break;
    case TIME_TICK:
        if( ((protimer_tick_event_t * )e)->ss == 5)
        {       
                do_beep();
                return EVENT_HANDLED;
        } 
        return EVENT_IGNORED;
    default:
        break;
    }
    return EVENT_IGNORED;

}
event_status_t protimer_state_handler_stat( protimer_t * mobj , event_t * e ) 
{
       switch (e->sig) // implement a case for all signal entry , exit ......
    {
    case ENTRY:
            mobj->curr_time = 0 ; 
            mobj->elapsed_time = 0 ; 
            display_time(mobj->prod_time);
            display_msg("productive time"); 
            return EVENT_HANDLED;  

    case EXIT:
             display_clear();
            return EVENT_HANDLED;
    case STATRT_PAUSE:
           break;
    case INC_TIME:
          break;
    case DEC_TIME:
         break;
    case TIME_TICK:
        if( ((protimer_tick_event_t * )e)->ss == 10)
        {       
                mobj->active_state = IDLE;
                return EVENT_HANDLED;
        } 
        return EVENT_IGNORED;
    default:
        break;
    }
    return EVENT_IGNORED;

    
}
event_status_t protimer_state_handler_pause( protimer_t * mobj , event_t * e ) 
{
    
       switch (e->sig) // implement a case for all signal entry , exit ......
    {
    case ENTRY:
            display_msg("paused"); 
            return EVENT_HANDLED;  

    case EXIT:
             display_clear();
            return EVENT_HANDLED;
    case STATRT_PAUSE:
           mobj->active_state = COUNTDOWN;  
           return EVENT_TRANSITION;
    case INC_TIME:
         mobj->curr_time +=60; 
         mobj->active_state = TIME_SET;
         return EVENT_TRANSITION;
         
    case DEC_TIME:
         if(mobj->curr_time >= 60) 
         {
         mobj->curr_time -=60; 
         mobj->active_state = TIME_SET;
         return EVENT_TRANSITION;
         }
    case TIME_TICK: 
        return EVENT_IGNORED;
    default:
        break;
    }
    return EVENT_IGNORED;


    
}
event_status_t protimer_state_handler_time_set( protimer_t * mobj , event_t * e ) 
{

       switch (e->sig) // implement a case for all signal entry , exit ......
    {
    case ENTRY:
            display_time(mobj->curr_time);
            return EVENT_HANDLED;  

    case EXIT:
             display_clear();
            return EVENT_HANDLED;
    case STATRT_PAUSE:
           mobj->active_state = COUNTDOWN;  
           return EVENT_TRANSITION;
    case INC_TIME:
         mobj->curr_time += 60;
         display_time(mobj->curr_time);
         return EVENT_HANDLED;
    case DEC_TIME:
         if(mobj->curr_time >= 60) 
         {
         mobj->curr_time -=60; 
         }
         display_time(mobj->curr_time);
         return EVENT_HANDLED;
         
    case TIME_TICK:
        return EVENT_IGNORED;
    default:
        break;
    }
    return EVENT_IGNORED;
    
}
event_status_t protimer_state_handler_countdown( protimer_t * mobj , event_t * e ) 
{

switch (e->sig) // implement a case for all signal entry , exit ......
    {
    case ENTRY:
            return EVENT_IGNORED;

    case EXIT:
            mobj->prod_time += mobj->elapsed_time ; 
            mobj->elapsed_time = 0 ; 
            return EVENT_HANDLED;
    case STATRT_PAUSE:
            mobj->active_state = STAT;      
            return EVENT_TRANSITION; 
    case INC_TIME:
         return EVENT_IGNORED;

    case DEC_TIME:
           return EVENT_IGNORED;

    case TIME_TICK:
        if( ((protimer_tick_event_t * )e)->ss == 10)
        {       --mobj->curr_time; 
                ++mobj->elapsed_time;
                display_time(mobj->curr_time);
            if(mobj->curr_time == 0 )
            {
                mobj->active_state =IDLE;
                return EVENT_TRANSITION;
            }
        } 
        return EVENT_HANDLED;
    default:
        break;
    }
    return EVENT_IGNORED;
    
}
//////////////// helper fucntion //////////////

void display_time (unsigned int time  )
{
        char buf[7]; 
        String time_msg; 
        u8  m = time /60 ; 
        u8  s = time % 60 ;
        sprintf(buf , "%03d:%02d", m,s ); 
        time_msg = (String)buf ; 
        lcd_set_cursor(5 , 0); 
        lcd_print_string(time_msg);  
}
void  display_msg (String s , u8 c , u8 r )
{
    lcd_set_cursor(c ,r ); 
    lcd_print_string(s);
}

void do_beep () 
{
        tone(PIN_BUZZER , 4000 , 25);
}

void display_clear () 
{
   lcd_clear(); 
}