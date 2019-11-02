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
	DigitalLed=0,
	DigitalDimmer=1,
	DigitalInput=2,
	DigitalOff=3,
	Adc=4,
	Null=5
} FunctionType;

//Tipi di parametri da poter salvare nella eeprom
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
	uint8_t Adc;
	uint8_t samples;	
} AnalogParam;

//Da qui partono i pacchetti
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

typedef struct
{
	PacketIndexed header;
	DigitalParam digitalSet;
} DigitalParamPacket;
#define DIGITAL_PARAM_PACKET_ID 2

typedef struct
{
	PacketIndexed header;
	AnalogParam analogSet;
} AnalogParamPacket;
#define ANALOG_PARAM_PACKET_ID 3

#pragma pack(pop)
