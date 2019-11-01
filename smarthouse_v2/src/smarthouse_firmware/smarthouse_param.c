#include "smarthouse_param.h"
#include "eeprom.h"
//*************TEST********
#include <stdio.h>
//*************************
#define PROTOCOL_VERSION_OFFSET (32)
#define FIRMWARE_VERSION_OFFSET (PROTOCOL_VERSION_OFFSET+sizeof(uint32_t))
#define SYSTEM_PARAM_OFFSET     (FIRMWARE_VERSION_OFFSET+sizeof(uint32_t))

void Smarthouse_paramInit(void)
{
	uint32_t cpv;
	uint32_t cfv;
	EEPROM_read(&cpv, PROTOCOL_VERSION_OFFSET, sizeof(uint32_t));
	EEPROM_read(&cfv, FIRMWARE_VERSION_OFFSET, sizeof(uint32_t));
	if( (cpv!=system_params.protocol_version) || (cfv!=system_params.firmware_version) )
	{
		EEPROM_write(PROTOCOL_VERSION_OFFSET, &system_params.protocol_version, sizeof(uint32_t));
		EEPROM_write(FIRMWARE_VERSION_OFFSET, &system_params.firmware_version, sizeof(uint32_t));
		//Salvare i parametri del sistema
		Smarthouse_paramSave(ParamSystem);
	}
//******************************************************************************	
//1o TEST STAMPARE IL PROTOCOLLO E IL FIRMWARE
EEPROM_read(&cpv, PROTOCOL_VERSION_OFFSET, sizeof(uint32_t));
printf("1oTest\tProtocolVersion: %ld\n", cpv);
EEPROM_read(&cfv, FIRMWARE_VERSION_OFFSET, sizeof(uint32_t));
printf("1oTest\tFirmwareVersion: %ld\n", cfv);
//2o TEST SEMPRE PER STAMPARE PROTOCOLLO E FIRMWARE
Smarthouse_paramLoad(ParamSystem);
printf("2oTest\tProtocolVersion: %ld\n", system_params.protocol_version);
Smarthouse_paramLoad(ParamSystem);
printf("2oTest\tFirmwareVersion: %ld\n", system_params.firmware_version);
//******************************************************************************
	//Salvare la configurazione dei pin digitali
	for(int i=0; i<DIGITAL_MAX; i++)
	{

	}
	//salvare la configurazione dei pin analogici
	for(int i=0; i<ANALOG_MAX; i++)
	{

	}
}

PacketStatus Smarthouse_paramSave(uint8_t param_type)//, int8_t index){
{
	switch(param_type)
	{
		case ParamSystem:
			EEPROM_write(SYSTEM_PARAM_OFFSET, &system_params, sizeof(system_params));
			break;
		default:
    			return GenericError;
  	}
	return Success;
}

PacketStatus Smarthouse_paramLoad(uint8_t param_type)//, int8_t index){
{
	switch(param_type)
	{
		case ParamSystem:
			EEPROM_read(&system_params, SYSTEM_PARAM_OFFSET, sizeof(system_params));
			break;
		default:
			return GenericError;
	}
	return Success;	
}
