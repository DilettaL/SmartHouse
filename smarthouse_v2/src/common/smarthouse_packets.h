#pragma once

#define DIGITAL_MAX 8

typedef enum
{
	DigitalLed=0,
	DigitalDimmer=1,
	DigitalInput=2,
	DigitalOff=3
} DigitalType;

typedef struct
{
	DigitalType type;
	uint8_t led[DIGITAL_MAX];
	uint8_t dimmer[DIGITAL_MAX];
	uint8_t input[DIGITAL_MAX];
	uint8_t intensity;
//	uint8_t result[DIGITAL_MAX];
} DigitalConfig;
