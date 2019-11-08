#pragma once
#include "smarthouse_client.h"
#include "smarthouse_packets.h"
#include "packet_operations.h"

// the client
extern struct SmarthouseClient* client;

extern SystemStatusPacket system_status;
extern SystemParamPacket system_params;

extern DigitalParamPacket digital_control[DIGITAL_MAX];
extern AnalogParamPacket analog_control[ANALOG_MAX];

//*****PROVA
extern PacketTest test;
//*****PROVA

void Smarthouse_shellStart(void);
