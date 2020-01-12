#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  // here are the limits
  typedef uint8_t PacketType;
  typedef uint8_t PacketSize;
  typedef uint16_t PacketSeq;
#define PACKET_SIZE_ANY 0xFF
#define PACKET_TYPE_MAX 20        // this is the maximum number of different packet types
#define PACKET_SIZE_MAX 254       // maximum length of a packet, including the header and        

#pragma pack(push, 1)
  typedef struct {
    PacketType type;  // type of the packet < PACKET_TYPE_MAX
    PacketSize size;  // size of the packet in bytes
    PacketSeq  seq;   // sequential number always increased
  } PacketHeader;
#pragma pack(pop)


#ifdef __cplusplus
}
#endif
