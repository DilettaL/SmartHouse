#pragma once
#include "smarthouse_host_globals.h"
#include "packet_operations.h"

void Smarthouse_paramInit(void);

// saves the parameter of a sybsystem in eeprom
PacketStatus Smarthouse_paramSave(void);//uint8_t param_type, int8_t index);

//reads the parameter of a sybsystem in eeprom
PacketStatus Smarthouse_paramLoad(void);//uint8_t param_type, int8_t index);
