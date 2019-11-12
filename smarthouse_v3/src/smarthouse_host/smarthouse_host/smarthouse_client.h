#pragma once
#include "shell_globals.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"

struct SmarthouseClient;

// creates a new smarthouse client, opening a serial connection on device at the selected baudrate
struct SmarthouseClient* SmarthouseClient_init(const char* device, uint32_t baudrate);

// sends a packet
PacketStatus SmarthouseClient_sendPacket(struct SmarthouseClient* cl, PacketHeader* p);//int time_out);

