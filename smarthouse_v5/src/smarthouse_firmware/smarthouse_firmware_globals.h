#pragma once
#include "smarthouse_packets.h"

extern TestConfigPacket test_config;

extern DigitalConfigPacket digital_config;
extern DigitalStatusPacket digital_status[NUM_DIGITAL];

extern AnalogConfigPacket analog_config;
extern AnalogStatusPacket analog_status[NUM_ANALOG];

extern EepromPacket eeprom;
