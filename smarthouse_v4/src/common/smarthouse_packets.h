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
typedef struct TestPacket{
	PacketHeader header;
	uint8_t prova;
} TestPacket;
#define TEST_PACKET_ID 1

typedef struct ReturnPacket{
	PacketHeader header;
	uint8_t ack;
} ReturnPacket;
#define RETURN_PACKET_ID 2
#pragma pack(pop)
