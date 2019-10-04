#pragma once
#include <stdint.h>

void initDigio(void);
void ledOn(uint8_t);
void ledOff(uint8_t );
void ledDimmer(uint8_t, uint8_t );
uint8_t digitalInput(uint8_t);
