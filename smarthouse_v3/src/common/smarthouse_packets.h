#pragma once
#include "packet_header.h"

#define SMARTHOUSE_PROTOCOL_VERSION 0x19880314

#pragma pack(push, 1)

typedef struct SystemParamPacket{
	PacketHeader header;
	uint32_t protocol_version;
	uint32_t firmware_version;
//	int16_t timer_period_ms;
	uint32_t comm_speed;
//	uint16_t comm_cycles;
//	uint8_t  periodic_packet_mask;    // this is a mask of packets we want to receive at each cycle 
//	uint16_t watchdog_cycles;
//	uint8_t num_joints;
  } SystemParamPacket;
#define SYSTEM_PARAM_PACKET_ID 1

typedef struct TestPacket
{
	PacketHeader header;
	uint8_t prova;
} TestPacket;
#define TEST_PACKET_ID 2
#pragma pack(pop)
