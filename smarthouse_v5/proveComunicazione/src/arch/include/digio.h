#pragma once
#include <stdint.h>

// initializes the digital io pins of the chip
void DigIO_init(void);

// returns the number of digital io pins on the chip
uint8_t  DigIO_numChannels(void);

typedef enum {
  Input=0x0,
  Output=0x1
} PinDirection;


// all the functions below return -1 on error
// >=0 on success
int8_t DigIO_setDirection(uint8_t pin, PinDirection dir);

int8_t DigIO_getDirection(uint8_t pin);

int8_t DigIO_setValue(uint8_t pin, uint8_t value);

int8_t DigIO_getValue(uint8_t pin);



