#pragma once
#include <stdint.h>
#include "packet_operations.h"

#ifdef __cplusplus
extern "C" {
#endif


struct PacketHandler;

typedef PacketStatus (*PacketHandlerRxFn)(struct PacketHandler*, uint8_t c);

typedef struct PacketHandler {
  PacketOperations *operations[PACKET_TYPE_MAX];

  // used while reading a packet
  PacketOperations* rx_current_op;
  PacketHeader* rx_current_packet;
  uint8_t rx_checksum;
  uint8_t* rx_buffer;
  uint8_t* rx_buffer_end;
  PacketSize rx_bytes_to_read;
  PacketHandlerRxFn rxFn;

  uint8_t tx_buffer[PACKET_SIZE_MAX];
  int tx_start;
  int tx_end;
  int tx_size;
  uint8_t tx_checksum;
} PacketHandler;
  
// initializes an empty packet handler
PacketStatus PacketHandler_initialize(PacketHandler* h);

// installs the manager for packet operations
PacketStatus PacketHandler_installPacket(PacketHandler* h, PacketOperations* ops);

// removes a packet
PacketStatus PacketHandler_uninstallPacket(PacketHandler* h, PacketType type);

// sends a packet. If returning failure, the packet is not sent
PacketStatus PacketHandler_sendPacket(PacketHandler* handler, PacketHeader* header);

/* functions to be connected to the UART*/

// sends a byte if available in the tx buffer
uint8_t PacketHandler_txByte(PacketHandler* h);

// processes a byte if available from the rx buffer
PacketStatus PacketHandler_rxByte(PacketHandler* handler, uint8_t c);

#ifdef __cplusplus
}
#endif
