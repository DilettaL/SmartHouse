//Smarthouse
#pragma once
#include "packet_header.h"

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

/*Lui scrive delle enum con le modalità di utilizzo dei joint e del ponte H, immaginiamo che sia per capire le modalità di
utilizzo di uno stesso componente. Non sappiamo se questo è necessario
typedef enum
{
	Adc_Off=0,
	Adc_On=1
}ADCMode;

typedef enum
{
	Digital_disable=0,
	Digital_on=1,
	Digital_input=2,
	Digital_dimmer=3
}DigitalMode;*/

#pragma pack(push, 1)

typedef struct
{
	PacketHeader header;
	uint8_t digital_status;
	uint8_t number_digital;
}DigitalPacket;
#define LED_PACKET_ID 0

typedef struct
{
	PacketHeader header;
	uint8_t adc_status;
	uint8_t	number_adc;
}AnalogPacket;
#define ADC_PACKET_ID 1
/*
typedef enum {
	ParamSystem = 0,
	ParamJointsSingle = 1,
	ParamDrive  = 2,
	ParamSonar  = 3
} ParamType;
*/
typedef enum
{
	ParamRequest = 0,
	ParamLoad = 1,
	ParamSave  = 2
} ParamAction;

typedef struct
{
	PacketHeader header;
	//0: send current params
	//1: load params from eeprom and send them
	//2: write current params to eeprom, read them and send them
	uint8_t action;

	// identifies the parameter class on which command will be executed
	// 0: system
 	// 1: joints
    	// 2: drive
//    	uint8_t param_type;

    	// the index (in case of multiple instances of a device
    	uint8_t index;
} ParamControlPacket;
#define PARAM_CONTROL_PACKET_ID 2
#pragma pack(pop)
