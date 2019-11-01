#pragma once
#include "packet_operations.h"
#include "smarthouse_packets.h"

PacketStatus Smarthouse_pinsInit(void);
PacketStatus functionsChoice(FunctionType, uint8_t);
