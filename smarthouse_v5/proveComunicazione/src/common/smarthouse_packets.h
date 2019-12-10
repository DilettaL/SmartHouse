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

typedef struct TestAck{
	PacketHeader header;
	uint16_t feedback_seq;
} TestAck;
#define TEST_ACK_ID 1

typedef struct TestConfig{
	PacketHeader header;
	uint8_t prova;
} TestConfig;
#define TEST_CONFIG_ID 2

typedef struct TestStatus{
	PacketHeader header;
	uint8_t prova;
} TestStatus;
#define TEST_STATUS_ID 3

#pragma pack(pop)
