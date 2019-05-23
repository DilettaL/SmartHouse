#include <stdint.h>

// #define PINS_NUM_DIGITAL 11 pin (da board dal 2 al 13

typedef struct{
	volatile uint8_t* select_adc;
}  Pin;



extern const Pin pins_adc[];
