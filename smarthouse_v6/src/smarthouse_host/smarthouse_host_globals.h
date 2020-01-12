#pragma once
#include <stdbool.h>
#include "smarthouse_packets.h"

void printBanner(void);

extern int run;
extern PacketHeader *pointer_packet;

extern TestConfigPacket test_config;

extern DigitalConfigPacket digital_config;
extern DigitalStatusPacket digital_status[NUM_DIGITAL];

extern AnalogConfigPacket analog_config;
extern AnalogStatusPacket analog_status[NUM_ANALOG];

extern EepromPacket eeprom;

typedef struct NameSet
{
	char arduino[10];
	char digital_0[10];
	char analog_0[10];
}NameSet;

extern NameSet name;
