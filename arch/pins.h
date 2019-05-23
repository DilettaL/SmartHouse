#include <stdint.h>

// #define PINS_NUM_DIGITAL 11 pin (da board dal 2 al 13
// #define PINS_NUM_ANALOG


typedef struct{
	volatile uint8_t* in_register;
	volatile uint8_t* out_register;
	volatile uint8_t* dir_register;
	uint8_t bit;

 	// timer registers for PWM
  	volatile uint8_t* tcc_register;
  	volatile uint8_t* oc_register;
  	const uint8_t com_mask;
}  Pin;



extern const Pin pins[];
