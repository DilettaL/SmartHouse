#include "pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "pins.h"

// here we use timers 0-4, in 8 bit mode
// regardless if they are 16 bit

#define TCCRA_MASK (1<<WGM10)               // fast PWM, non inverted
#define TCCRB_MASK ((1<<WGM12)|(1<<CS10))   // fast PWM, non inverted, 16Mhz

// initializes the pwm subsystem
PWMError PWM_init(void){
  cli();

  // disable interrupts

  
  TIMSK0=0;
  TIMSK1=0;
  TIMSK2=0;
  TIMSK3=0;
  TIMSK4=0;

  //8 bit timers manual init
  TCCR0A=(1<<WGM00)|(1<<WGM01);
  TCCR0B=(1<<CS00);
  TCCR2A=TCCR0A;
  TCCR2B=TCCR0B;
  
  // 16 bit timers,
  // clear the upper byte of 16 bit timer compare regs
  TCCR1A=TCCRA_MASK;
  TCCR1B=TCCRB_MASK;
  OCR1AH=0;
  OCR1BH=0;
  OCR1CH=0;
  
  TCCR3A=TCCRA_MASK;
  TCCR3B=TCCRB_MASK;
  OCR3AH=0;
  OCR3BH=0;
  OCR3CH=0;

  sei();

  return PWMSuccess;
}

// how many pwm on this chip?
uint8_t PWM_numChannels(void){
  return PINS_NUM;
}

// what was the period i set in the pwm subsystem
// might only require to adjust the prescaler
PWMError PWM_isEnabled(uint8_t c) {
  if (c>=PINS_NUM)
    return PWMChannelOutOfBound;
  const Pin* pin = pins+c;
  if (!pin->tcc_register)
    return PWMChannelOutOfBound;
  if ((*pin->tcc_register & pin->com_mask)==0)
    return 0;
  return PWMEnabled;
}

// sets the output on a pwm channel
PWMError PWM_enable(uint8_t c, uint8_t enable){
  if (c>=PINS_NUM)
    return PWMChannelOutOfBound;
  const Pin* pin = pins+c;
  if (!pin->tcc_register || !pin->oc_register)
    return PWMChannelOutOfBound;
  *pin->oc_register=0;
  if (enable){
    *pin->tcc_register |= pin->com_mask;
    *pin->dir_register    |= (1<<pin->bit);
  } else {
    *pin->tcc_register &= ~pin->com_mask;
    *pin->dir_register    &= ~(1<<pin->bit);
  }
  return PWMSuccess;
}


// what was the duty cycle I last set?
int16_t PWM_getDutyCycle(uint8_t c){
  if (c>=PINS_NUM)
    return PWMChannelOutOfBound;
  const Pin* pin = pins+c;
  if (!pin->tcc_register || !pin->oc_register)
    return PWMChannelOutOfBound;
  return 255-*pin->oc_register;
}

// sets the duty cycle
 PWMError PWM_setDutyCycle(uint8_t c, uint8_t duty_cycle){
  if (c>=PINS_NUM)
    return PWMChannelOutOfBound;
  const Pin* pin = pins+c;
  if (!pin->tcc_register || !pin->oc_register)
    return PWMChannelOutOfBound;
  *pin->oc_register = 255-duty_cycle;
  return PWMSuccess;
}

