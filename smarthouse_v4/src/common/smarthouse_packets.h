#pragma once
#include "packet_header.h"

  // simple macro to initialize a packet
#define INIT_PACKET(var, id)			\
  {						\
    var.header.type=id;				\
    var.header.size=sizeof(var);		\
    var.header.seq=0;				\
  }\

typedef enum
{
	ledOff=0,
	ledOn=1,
	dimmer=2,
	input_digital=3
} DigitalOperations;
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


typedef struct DigitalConfigPacket{
	PacketHeader header;
	uint8_t pin_digital;
	uint8_t set_digital;
	uint8_t intensity;
}DigitalConfigPacket;
#define DIGITAL_CONFIG_PACKET_ID 3

typedef struct DigitalStatusPacket{
	PacketHeader header;
	uint8_t pin_digital;
	uint8_t set_digital;
	uint8_t intensity;
	uint8_t inputs;
}DigitalStatusPacket;
#define DIGITAL_STATUS_PACKET_ID 4

typedef struct AnalogConfigPacket{
	PacketHeader header;
	uint8_t pin_analog;
	uint8_t samples;
}AnalogConfigPacket;
#define ANALOG_CONFIG_PACKET_ID 5

typedef struct AnalogStatusPacket{
	PacketHeader header;
	uint8_t pin_analog;
	uint8_t samples;
	uint16_t *result;
//manca i valori di ritorno
}AnalogStatusPacket;
#define ANALOG_STATUS_PACKET_ID 6
#pragma pack(pop)
