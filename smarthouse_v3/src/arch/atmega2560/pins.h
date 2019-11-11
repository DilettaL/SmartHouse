#include <stdint.h>

typedef struct{
  volatile uint8_t* in_register;
  volatile uint8_t* out_register;
  volatile uint8_t* dir_register;
  uint8_t bit;

  // timer registers for PWM
  volatile uint8_t* tcc_register;
  volatile uint8_t* oc_register;
  const uint8_t com_mask;

  // interrupt
}  Pin;

#define PINS_NUM 14

extern const Pin pins[];

