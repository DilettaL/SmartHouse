#pragma once
#include <stdint.h>

void digio_init (void);
void ledOn (uint8_t);
void ledOff (uint8_t );
void ledDimmer (uint8_t, uint8_t );
uint8_t digitalInput (uint8_t);
uint8_t getDDR (uint8_t pin);
uint8_t getPORT (uint8_t pin);
uint8_t getPIN (uint8_t pin);
