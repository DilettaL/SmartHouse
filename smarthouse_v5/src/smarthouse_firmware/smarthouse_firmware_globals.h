#pragma once
#include "smarthouse_packets.h"

extern TestConfigPacket test_config;
extern TestStatusPacket test_status;

extern DigitalConfigPacket digital_config[NUM_DIGITAL];
extern DigitalStatusPacket digital_status;

extern AnalogConfigPacket analog_config;
extern AnalogStatusPacket analog_status;
