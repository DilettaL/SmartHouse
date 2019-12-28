#pragma once
#include <stdbool.h>
#include "smarthouse_packets.h"

extern int run;
extern PacketHeader *pointer_packet;

extern TestConfigPacket test_config;
extern TestStatusPacket test_status;

extern DigitalConfigPacket digital_config;
extern DigitalStatusPacket digital_status[NUM_DIGITAL];

extern AnalogConfigPacket analog_config;
extern AnalogStatusPacket analog_status[NUM_ANALOG];

extern EepromWritePacket eeprom_write;
extern EepromReadPacket eeprom_read;
