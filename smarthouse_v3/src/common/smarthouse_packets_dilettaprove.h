#pragma once
#include "packet_header.h"

#define SMARTHOUSE_PROTOCOL_VERSION 0x19880314

typedef struct {
	PacketHeader header;
	uint8_t index;
} PacketIndexed;

typedef struct {
	ledOn=0,
	dimmer=1,
	digitalInput=2,
	ledOff=3
} FunctionDigitalType;

#pragma pack(push, 1)
typedef struct
{
	PacketHeader header;
	uint16_t rx_buffer_size;
	uint16_t rx_packets;
	uint16_t rx_packet_errors;
/*	uint16_t tx_buffer_size;
	uint16_t tx_packets;
	uint16_t tx_packet_errors;
	uint16_t battery_level;
	int16_t watchdog_count;
*/	uint16_t rx_seq;
/*	uint8_t rx_packet_queue;
	uint32_t idle_cycles;
*/} SystemStatusPacket;
#define SYSTEM_STATUS_PACKET_ID 1

typedef struct SystemParamPacket
{
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
#define SYSTEM_PARAM_PACKET_ID 2
////////////////DIGITALI
typedef struct
{
	FunctionDigitalType type;
	uint8_t pin_digital;
	uint8_t input;			//quanti ingressi
	uint8_t intensity;		//quanto dimmero
} DigitalParam;

typedef struct
{
	FunctionDigitalType type;
	DigitalParam setting;
	uint8_t *input_result;
}DigitalStatus;

typedef struct
{
	PacketIndexed header;
	DigitalStatus digitalinfo;
}DigitalStatusPacket;
#define DIGITAL_STATUS_PACKET_ID 3

typedef struct
{
	PacketIndexed header;
	DigitalParam digitalSet;
} DigitalParamPacket;
#define DIGITAL_PARAM_PACKET_ID 4
///////////ANALOGICI
typedef struct
{
	uint8_t pin_analog;
	uint8_t samples;
}AnalogParam;

typedef struct
{
	AnalogParam setting;
	uint8_t *adc_result;
}AnalogStatus;

typedef struct
{
	PacketIndexed header;
	AnalogStatus analoginfo;
} AnalogStatusPacket;
#define ANALOG_STATUS_PACKET_ID 5


typedef struct
{
	PacketIndexed header;
	AnalogParam analogset;
}AnalogParamPacket;
#define ANALOG_PARAM_PACKET_ID 6
//*****PROVA DA CAMBIARE NUMERO OVVIAMENTE
typedef struct
{
	PacketHeader header;
	uint8_t test_status;
} PacketStatusTest;
#define TEST_PACKET_STATUS_ID 7

typedef struct
{
	PacketHeader header;
	uint8_t test_param;
} PacketParamTest;
#define TEST_PACKET_PARAM_ID 8


#pragma pack(pop)
