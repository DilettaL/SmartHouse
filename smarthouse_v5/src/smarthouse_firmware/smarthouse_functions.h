#pragma once
#include "smarthouse_firmware_globals.h"
#include "smarthouse_packets.h"
#include "packet_operations.h"

void Smarthouse_digital(void);
void Smarthouse_analog(void);

// saves the parameter of a sybsystem in eeprom
PacketStatus Smarthouse_paramSave(void);

//reads the parameter of a sybsystem in eeprom
PacketStatus Smarthouse_paramLoad(void);
