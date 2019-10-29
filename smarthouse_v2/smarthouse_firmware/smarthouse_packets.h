#pragma once
#include "packet_avr_common.h"

//1)
// simple macro to initialize a packet
#define INIT_PACKET(var, id)			\
{						\
	var.header.type=id;				\
	var.header.size=sizeof(var);		\
	var.header.seq=0;				\
}\

#define ADC_MAX 8
#define DIGITAL_MAX 8

//2)
typedef struct
{
	PacketHeader header;
	uint8_t index;
} PacketIndexed;

typedef enum
{
	DigitalTypeLed=0,
	DigitalTypeDimmer=1,
	DigitalTypeInput=2,
} DigitalType;

//3)
#pragma pack(push, 1)

//4) Pacchetto di stato dei pin analogici
typedef struct
{
	PacketHeader header;
	uint16_t range_adc[ADC_MAX];
}AnalogStatus;
#define ANALOG_STATUS_PACKET_ID 1

//5)Pacchetto di configurazione dei pin analogici
typedef struct
{
	PacketHeader header;
	uint16_t numb_adc; //numero di adc da utilizzare
	uint8_t numb_samples;//numero di campioni per ogni adc
}AnalogConfig;
#define ANALOG_CONFIG_PACKET_ID 2

//6)Pacchetto di stato dei pin digitali
typedef struct
{
	PacketHeader header;
	uint16_t range_digital[DIGITAL_MAX];
	uint8_t totLed;
	uint8_t totDimmer;
	uint8_t totInput;
	uint8_t resultInput;
}DigitalStatus;
#define DIGITAL_STATUS_PACKET_ID 3

//7)Pacchetto di configurazione dei pin digitali
typedef struct
{
	PacketHeader header;
	uint16_t numb_Led;
	uint16_t numb_Dimmer;
	uint16_t numb_input;
	uint8_t intensity;
}DigitalConfig;
#define DIGITAL_CONFIG_PACKET_ID 4

//8)Pacchetto dei parametri gnerali del sistema
typedef struct SystemParamPacket
{
	PacketHeader header;
//	uint32_t protocol_version;
	uint32_t firmware_version;
//	int16_t timer_period_ms;
	uint32_t comm_speed;
//	uint16_t comm_cycles;
//	uint8_t  periodic_packet_mask;    // this is a mask of packets we want to receive at each cycle 
} SystemParamPacket;
#define SYSTEM_PARAM_PACKET_ID 5

typedef struct
{
	PacketHeader header;
	uint16_t rx_buffer_size;
	uint16_t rx_packets;
	uint16_t rx_packet_errors;
	uint16_t tx_buffer_size;
	uint16_t tx_packets;
	uint16_t tx_packet_errors;
	uint16_t battery_level;
	int16_t watchdog_count;
	uint16_t rx_seq;
	uint8_t rx_packet_queue;
	uint32_t idle_cycles;
} SystemStatusPacket;
#define SYSTEM_STATUS_PACKET_ID 6
#pragma pack(pop)
