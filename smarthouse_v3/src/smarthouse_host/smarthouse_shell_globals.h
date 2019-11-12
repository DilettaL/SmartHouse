#pragma once
#include "smarthouse_client.h"
#include "smarthouse_packets.h"
#include "packet_operations.h"

// the client
extern struct SmarthouseClient* client;

extern struct SystemParamPacket system_params;

extern struct TestPacket test;
