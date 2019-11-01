#pragma once
#include "packet_header.h"

#define DIGITAL_MAX 8
#define ANALOG_MAX 8
#define SMARTHOUSE_PROTOCOL_VERSION 0x20180915
//Tipologie di azioni con i pin digitali
typedef enum
{
	DigitalLed=0,
	DigitalDimmer=1,
	DigitalInput=2,
	DigitalOff=3
} DigitalType;

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
	DigitalType type;
	uint8_t ledOn[DIGITAL_MAX];
	uint8_t ledOff[DIGITAL_MAX];
	uint8_t dimmer[DIGITAL_MAX];
	uint8_t input[DIGITAL_MAX];
	uint8_t intensity;
//	uint8_t result[DIGITAL_MAX];
} DigitalConfig;

typedef struct
{
	uint8_t Adc[ANALOG_MAX];
	uint8_t samples;	
} AnalogConfig;

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

#pragma pack(pop)
