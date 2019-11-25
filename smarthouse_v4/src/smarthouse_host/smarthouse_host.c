#include <stdio.h>
#include <stdlib.h>
#include "packet_handler.h"
#include "serial_linux.h"

#pragma pack(push, 1)
typedef struct TestPacket{
  PacketHeader header;
  uint8_t prova;
} TestPacket;
#pragma pack(pop)

#define TEST_PACKET_ID 1

int main (int argc, char **argv)
{
	return 0;
}
