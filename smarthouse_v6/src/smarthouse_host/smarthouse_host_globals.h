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
	char arduino[20];
	char *pt_pin;
	char digital_0[20];//1
	char digital_1[20];
	char digital_2[20];
	char digital_3[20];
	char digital_4[20];
	char digital_5[20];
	char digital_6[20];
	char digital_7[20];
	char digital_8[20];
	char digital_9[20];
	char digital_10[20];
	char digital_11[20];
	char digital_12[20];
	char analog_0[20];//14
	char analog_1[20];
	char analog_2[20];
	char analog_3[20];
	char analog_4[20];
	char analog_5[20];
	char analog_6[20];
	char analog_7[20];
	char analog_8[20];
	char analog_9[20];
	char analog_10[20];
	char analog_11[20];
	char analog_12[20];
	char analog_13[20];
	char analog_14[20];
}NameSet;

extern NameSet name;
