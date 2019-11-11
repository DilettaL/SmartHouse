#include <string.h>
#include "packet_handler.h"
#include "uart.h"
#include "delay.h"


#pragma pack(push, 1)

typedef struct Packet0 {
  PacketHeader header;
  float f;
} Packet0;
#pragma pack(pop)

#define PACKET0_TYPE 0
#define PACKET0_SIZE (sizeof(Packet0))

PacketHandler packet_handler;

Packet0 packet0_buffer;

PacketOperations packet0_ops = {
  0,
  sizeof (Packet0),
  _initializeBuffer,
  0,
  _onReceive,
  0
};

#pragma pack(push, 1)

typedef struct Packet1 {
  PacketHeader header;
  float f1;
  float f2[3];
} Packet1;
#pragma pack(pop)

#define PACKET1_TYPE 1
#define PACKET1_SIZE (sizeof(Packet1))

Packet1 packet1_buffer;


PacketOperations packet1_ops = {
  1,
  sizeof (Packet1),
  _initializeBuffer,
  0,
  _onReceive,
  0
};

struct UART* uart;

void flushBuffers(void) {
  // we read all what we have to read
  while (UART_rxBufferFull(uart))
    PacketHandler_rxByte(&packet_handler, UART_getChar(uart));
  // we write all what we have to write
  while (packet_handler.tx_size)
    UART_putChar(uart, PacketHandler_txByte(&packet_handler));
}

int main(int argc, char** argv) {
  uart = UART_init(0, 115200);

  PacketHandler_initialize(&packet_handler);
  PacketHandler_installPacket(&packet_handler, &packet0_ops);
  PacketHandler_installPacket(&packet_handler, &packet1_ops);


  int seq = 0;
  Packet0 p0 = {
    {PACKET0_TYPE, PACKET0_SIZE, 0}, 0.0f
  };
  Packet1 p1 = {
    {PACKET1_TYPE, PACKET1_SIZE, 0}, 0.1,
    {.1, .2, .3}
  };

  while (1) {
    while (PacketHandler_sendPacket(&packet_handler, (PacketHeader*) & p0) != Success) {
      flushBuffers();
    }
    p0.header.seq = seq;
    seq++;
    while (PacketHandler_sendPacket(&packet_handler, (PacketHeader*) & p1) != Success) {
      flushBuffers();
    }
    p1.header.seq = seq;
    seq++;
    delayMs(100);
  }
}

//_initializeBuffer for firmware

//Questa funzione deve far si che il puntatore di packetheader punti alla corrispettiva porzione di memoria per un determinato pacchetto in modo che, una volta giunti al payload, si possa iniziare a leggere direttamente il contenuto
static PacketHeader* _initializeBuffer(PacketType type, PacketSize size, void* arg)
{
	PacketHandler* handler=(PacketHandler*)arg;
	return (PacketHeader*) handler->rx_current_packet;
}


static PacketStatus _onReceive(PacketHeader *packet, void* arg)
{
	PacketHandler *handler=(PacketHandler*)arg;
//arg deve essere un riferimento alla struc di globals
//packet è il packetheader di quel pacchetto (risultato di intiaizeBuffer) che è stato ricevuto e va copiato in memoria
	memcpy(handler, packet, packet->size);
	return Success;
}
