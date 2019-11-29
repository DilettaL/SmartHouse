#pragma once
#include "packet_header.h"

  // simple macro to initialize a packet
#define INIT_PACKET(var, id)			\
  {						\
    var.header.type=id;				\
    var.header.size=sizeof(var);		\
    var.header.seq=0;				\
  }\

#pragma pack(push, 1)
typedef struct TestConfigPacket{
	PacketHeader header;
	uint8_t prova;
} TestConfigPacket;
#define TEST_CONFIG_PACKET_ID 1

typedef struct TestStatusPacket{
	PacketHeader header;
	uint8_t ack;
} TestStatusPacket;
#define TEST_STATUS_PACKET_ID 2
#pragma pack(pop)
