#include "sonar.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "counter.h"

uint16_t counters[SONARS_NUM];

// the pattern we asked for
uint8_t triggers=0;

// raised by isr when a falling edge of the echo is received
uint8_t echos=0;

void Sonar_init() {
  Counter_init();
  
  // set all pins on port C (37-30) as output for the trigger 
  DDRC=0xFF;
  // level low
  PORTC=0x0;

  // set all pins on port  K (A8-A15) as input to get the echo
  DDRK=0x0;
  // enable pull_up resistors
  PORTK=0xFF;

  triggers=0;
  echos=0;
    
  // mask all echoes
  PCMSK2=triggers;

  // enable interrupts
  PCICR|=(1<<PCIE2);

}

uint8_t Sonar_pollPattern(uint8_t* pattern){
  // if a reading is in progress return a failure
  /* echos=PINC; */
  /* if(echos) */
  /*   return 0; */

  triggers=*pattern;

  // clear timers
  for (uint8_t s=0; s<SONARS_NUM; ++s){
      counters[s]=0;
  }

  // send a trigger and wait 10 us
  PORTC=triggers;
  _delay_us(10);
  PORTC=0;

  sei();
  // enable interrupt on change for selected sonars
  PCMSK2=triggers;
  cli();
  return 1;
}

void Sonar_get(uint16_t* ranges){
  for (uint8_t s=0; s<SONARS_NUM; ++s){
    if (triggers&(1<<s))
      ranges[s]=counters[s];
    else
      ranges[s]=0;
  } 
}


ISR(PCINT2_vect) {
  uint16_t current_time=Counter_get();
  uint8_t current_echo=PINK;
  cli();
  for (uint8_t s=0; s<SONARS_NUM; ++s){
    // look only at the current bit
    uint8_t mask=(1<<s);

    // ignore the bits we neglected
    if (! (triggers & mask))
      continue;

    // if nothing happened on that sonar, we skip
    if ((current_echo&mask)==(echos&mask))
      continue;

    // in case of a rising  edge, we save the timer
    if (current_echo&mask) {
      counters[s]=current_time;
    } else {
    // otherwise we put in the counters[s] the duration (echo end)
      counters[s]=current_time-counters[s];
    }
  }
  echos=current_echo;
  sei();
}
