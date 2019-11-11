#pragma once
#include <stdint.h>

#define SONARS_NUM 8

void Sonar_init(void);
uint8_t Sonar_pollPattern(uint8_t* pattern);
void Sonar_get(uint16_t* ranges);

