#pragma once
#include "smarthouse_packets.h"

extern int run;
extern PacketHeader *pointer_packet;

extern TestConfigPacket test_config[NUM_TEST];
extern TestStatusPacket test_status[NUM_TEST];

extern DigitalConfigPacket digital_config[NUM_DIGITAL];
extern DigitalStatusPacket digital_status[NUM_DIGITAL];

extern AnalogConfigPacket analog_config[NUM_ANALOG];
extern AnalogStatusPacket analog_status[NUM_ANALOG];
