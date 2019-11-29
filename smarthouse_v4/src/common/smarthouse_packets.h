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

typedef enum
{
	ledOff=0,
	ledOn=1,
	dimmer=2,
	input_digital=3
} DigitalOperations;

typedef struct DigitalConfigPacket{
	PacketHeader header;
	uint8_t pin_digital;
	DigitalOperations set_digital;
	uint8_t intensity;
	uint8_t inputs;
}DigitalConfigPacket;
#define DIGITAL_CONFIG_PACKET_ID 3

typedef struct DigitalStatusPacket{
	PacketHeader header;
	DigitalOperations digital_status;
}DigitalStatusPacket;
#define DIGITAL_STATUS_PACKET_ID 4
#pragma pack(pop)
