#pragma once
#include "packet_header.h"

#define DIGITAL_MAX 8
#define ANALOG_MAX 8
#define SMARTHOUSE_PROTOCOL_VERSION 0x19880314
//Struct dati per l'indicizzazione
typedef struct {
	PacketHeader header;
	uint8_t index;
} PacketIndexed;


//Tipologie di azioni con i pin digitali
typedef enum
{
	ledOn=0,
	dimmer=1,
	digitalInput=2,
	ledOff=3,
	Adc=4,
	Null=5
} FunctionType;

//Tipi di parametri da poter salvare nella eeprom e non solo
typedef enum
{
	ParamSystem = 0,
	ParamDigital =1,
	ParamAnalog =2
} ParamType;


#pragma pack(push, 1)
typedef struct
{
	FunctionType type;
	uint8_t ledOn;
	uint8_t ledOff;
	uint8_t dimmer;
	uint8_t input;
	uint8_t intensity;
} DigitalParam;

typedef struct
{
	FunctionType type;
	uint8_t Adc;
	uint8_t samples;	
} AnalogParam;

//Da qui partono i pacchetti

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

typedef struct
{
	PacketIndexed header;
	DigitalParam digitalSet;
} DigitalParamPacket;
#define DIGITAL_PARAM_PACKET_ID 3

typedef struct
{
	PacketIndexed header;
	AnalogParam analogSet;
} AnalogParamPacket;
#define ANALOG_PARAM_PACKET_ID 4

typedef struct
{
	FunctionType type;
	uint8_t pintest;
} TestParam;

//*****PROVA
typedef struct
{
	PacketHeader header;
	TestParam test;
} PacketTest;
#define TEST_PACKET_ID 5
//*****PROVA
#pragma pack(pop)
