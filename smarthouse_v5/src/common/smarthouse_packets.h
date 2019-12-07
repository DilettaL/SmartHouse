#pragma once
#include "packet_header.h"

#define NUM_DIGITAL 13

  // simple macro to initialize a packet
#define INIT_PACKET(var, id)			\
  {						\
    var.header.type=id;				\
    var.header.size=sizeof(var);		\
    var.header.seq=0;				\
  }\

typedef struct
{
	PacketHeader header;
	uint8_t index;
} PacketIndexed;

typedef enum
{
	ledOff=0,
	ledOn=1,
	dimmer=2,
	input_digital=3
} DigitalOperations;
#pragma pack(push, 1)
typedef struct TestConfigPacket{
	PacketIndexed header;
	uint8_t prova;
} TestConfigPacket;
#define TEST_CONFIG_PACKET_ID 1

typedef struct TestStatusPacket{
	PacketIndexed header;
	uint8_t sync;
} TestStatusPacket;
#define TEST_STATUS_PACKET_ID 2


typedef struct DigitalConfigPacket{
	PacketIndexed header;
	uint8_t pin_digital;
	uint8_t set_digital;
	uint8_t intensity;
}DigitalConfigPacket;
#define DIGITAL_CONFIG_PACKET_ID 3

typedef struct DigitalStatusPacket{
	PacketIndexed header;
	uint8_t pin_digital;
	uint8_t set_digital;
	uint8_t intensity;
	uint8_t inputs;
}DigitalStatusPacket;
#define DIGITAL_STATUS_PACKET_ID 4

typedef struct AnalogConfigPacket{
	PacketIndexed header;
	uint8_t pin_analog;
	uint8_t samples;
}AnalogConfigPacket;
#define ANALOG_CONFIG_PACKET_ID 5

#define SAMPLE_MAX 10
typedef struct AnalogStatusPacket{
	PacketIndexed header;
	uint8_t pin_analog;
	uint8_t samples;
	uint16_t result[SAMPLE_MAX];
}AnalogStatusPacket;
#define ANALOG_STATUS_PACKET_ID 6
#pragma pack(pop)
