#include "encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_ENCODERS 2
// all port B is used to handle 4 encoders
#define ENCODER_MASK 0x0F

typedef uint16_t EncoderValueType;

// status of encoder as the previous bits of port B
uint8_t _encoder_status;
EncoderValueType _encoder_current_value[NUM_ENCODERS];
EncoderValueType _encoder_sampled_value[NUM_ENCODERS];

// initializes the encoder subsystem
void Encoder_init(void){
  cli();
  // clear counters and status
  for (int i=0; i<NUM_ENCODERS; ++i){
    _encoder_current_value[i]=0;
    _encoder_sampled_value[i]=0;
  }
  _encoder_status=0;
  // configure port and interrupts
  DDRB &= ~ENCODER_MASK; //set encoder pins as input
  PORTB |= ENCODER_MASK; //enable pull up resistors
  PCICR |= (1 << PCIE0); // set interrupt on change, looking up PCMSK0
  PCMSK0 |= ENCODER_MASK;   // set PCINT0 to trigger an interrupt on state change 
  sei();                     // turn on interrupts
}

// samples the encoders, saving the respective values in a temporary storage
void Encoder_sample(void){
  cli();
  register EncoderValueType* s=_encoder_sampled_value;
  register EncoderValueType* c=_encoder_current_value;
  for (uint8_t i=0; i<NUM_ENCODERS; ++i, ++s, ++c)
    *s=*c;
  sei();
}

// returns the number of the encoder 
uint8_t Encoder_numEncoders(void){
  return NUM_ENCODERS;
}

// returns the value of an encoder, when sampled with the Encoder_sample();
uint16_t Encoder_getValue(uint8_t num_encoder){
  return _encoder_sampled_value[num_encoder];
}

static const int8_t _transition_table []=
  {
      0,  //0000
      1, //0001
     -1,  //0010
      0,  //0011
     -1,  //0100
      0,  //0101
      0,  //0110
      1, //0111
      1, //1000
      0,  //1001
      0,  //1010
     -1,  //1011
      0,  //1100
     -1,  //1101
      1,  //1110
      0   //1111
    };


ISR(PCINT0_vect) {
  cli();
  uint8_t port_value=PINB&ENCODER_MASK;
  register uint8_t ns=port_value;
  register uint8_t ps=_encoder_status;
  register const int8_t* ttable=_transition_table;
  register EncoderValueType* c=_encoder_current_value;
  for (uint8_t enc_num=0; enc_num<NUM_ENCODERS; ++enc_num, ++c){
    uint8_t idx=(ns&0x03)|((ps&0x03)<<2);
    *c += ttable[idx];
    ns>>=2;
    ps>>=2;
  }
  _encoder_status=port_value; 
  sei();
}
