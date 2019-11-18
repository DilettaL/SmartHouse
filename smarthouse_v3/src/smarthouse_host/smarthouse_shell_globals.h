#pragma once
#include "smarthouse_client.h"
#include "smarthouse_packets.h"
#include "packet_operations.h"

// the client
extern struct SmarthouseClient* client;

extern SystemParamPacket system_params;
extern SystemStatusPacket system_status;

extern TestPacket test;

extern StringMessagePacket message;
