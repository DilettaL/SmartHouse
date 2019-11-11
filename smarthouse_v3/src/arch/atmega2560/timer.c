#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>


// here we hook to timer 5 which is not used in any of the primary arduino pins
// its 16 bit and allows us a decent resolution

#include "timer.h"
// just 1 timer for the user
// we hook to timer 5
#define  NUM_TIMERS 1

typedef struct Timer{
  int timer_num;
  uint16_t duration_ms;
  TimerFn fn;
  void* args;
} Timer;

static Timer timers[NUM_TIMERS];

void Timers_init(void){
  memset(timers, 0, sizeof(timers));
  for (int i=0; i<NUM_TIMERS; ++i)
    timers[i].timer_num=i;
}

// creates a timer that has a duration of ms milliseconds
// bound to the device device
// each duration_ms the function timer_fn will be called
// with arguments timer args
Timer* Timer_create(char* device,
		    uint16_t duration_ms,
		    TimerFn timer_fn,
		    void* timer_args){
  Timer* timer=0;
  if (!strcmp(device,"timer_0"))
    timer=timers;
  else
    return 0;
  timer->duration_ms=duration_ms;
  timer->timer_num=0;
  timer->fn=timer_fn;
  timer->args=timer_args;
  return timer;
}

// stops and destroyes a timer
void Timer_destroy(struct Timer* timer){
  Timer_stop(timer);
  cli();
  int timer_num=timer->timer_num;
  memset(timer, 0, sizeof(Timer));
  timer->timer_num=timer_num;
  sei();
}

void _timer0_start(struct Timer* timer){
  uint16_t ocrval=(uint16_t)(15.62*timer->duration_ms);
  TCCR5A = 0;
  TCCR5B = 0;
  OCR5A = ocrval;
  TCCR5B |= (1 << WGM52) | (1 << CS50) | (1 << CS52);
  TIMSK5 |= (1 << OCIE5A);
}


// starts a timer
void Timer_start(struct Timer* timer){
  cli();
  if (timer->timer_num==0)
    _timer0_start(timer);
  sei();
}


// stops a timer
void Timer_stop(struct Timer* timer){
  if (timer->timer_num!=0)
    return;
  cli();
  TIMSK5 &= ~(1 << OCIE5A);
  sei();
}


ISR(TIMER5_COMPA_vect) {
  TCNT5 = 0;
  if(timers[0].fn)
    (*timers[0].fn)(timers[0].args);
}
