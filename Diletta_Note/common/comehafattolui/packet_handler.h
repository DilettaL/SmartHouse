//Smarthouse
#pragma once
#include <stdint.h>
#include "packet_operations.h"

//Funzione per la gestione degli stati dei pacchetti
typedef PacketStatus (*PacketHandlerRxFn)(struct PacketHandler*, uint8_t c);
