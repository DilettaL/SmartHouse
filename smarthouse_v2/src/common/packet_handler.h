#pragma once
#include <stdint.h>
#include "packet_operations.h"

struct PacketHandler;
typedef PacketStatus (*PacketHandlerRxFn)(struct PacketHandler*, uint8_t c);

typedef struct PacketHandler {
	PacketOperations *operations[PACKET_TYPE_MAX];

  // used while reading a packet
//PacketOperations* rx_current_op;
//PacketHeader* rx_current_packet;
	uint8_t rx_checksum;
//uint8_t* rx_buffer;
//uint8_t* rx_buffer_end;
//PacketSize rx_bytes_to_read;
//PacketHandlerRxFn rxFn;

//uint8_t tx_buffer[PACKET_SIZE_MAX];
//int tx_start;
//int tx_end;
//int tx_size;
//uint8_t tx_checksum;
} PacketHandler;

PacketStatus PacketHandler_initialize(PacketHandler* h);

PacketStatus PacketHandler_installPacket(PacketHandler* h, PacketType type);
