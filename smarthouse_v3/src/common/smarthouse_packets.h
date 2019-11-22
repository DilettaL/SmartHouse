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
typedef struct  {
    PacketHeader header;
    uint16_t rx_buffer_size;
    uint16_t rx_packets;
    uint16_t rx_packet_errors;
    uint16_t tx_buffer_size;
    uint16_t tx_packets;
    uint16_t tx_packet_errors;
    uint16_t battery_level;
    int16_t watchdog_count;
    uint16_t rx_seq;
    uint8_t rx_packet_queue;
    uint32_t idle_cycles;
  } SystemStatusPacket;
#define SYSTEM_STATUS_PACKET_ID 2
typedef struct TestPacket
{
	PacketHeader header;
	uint8_t prova;
} TestPacket;
#define TEST_PACKET_ID 3

#define MESSAGE_MAX_SIZE 128
  typedef struct {
    PacketHeader header;
    char message[MESSAGE_MAX_SIZE];
  } StringMessagePacket;
#define MESSAGE_PACKET_ID 4
#pragma pack(pop)
