#pragma once
#include "smarthouse_packets.h"

#define SMARTHOUSE_FIRMWARE_VERSION 0x19880304

extern  SystemParamPacket system_params;

extern DigitalParamPacket digital_control[DIGITAL_MAX];
extern AnalogParamPacket analog_control[ANALOG_MAX];
