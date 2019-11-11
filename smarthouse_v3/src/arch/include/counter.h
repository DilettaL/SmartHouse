#pragma once
#include <stdint.h>

// returns the value of a progressive counter at 62.500 KHz
void Counter_init(void);
uint16_t Counter_get(void);
