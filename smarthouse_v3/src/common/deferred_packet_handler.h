#pragma once
#include "packet_handler.h"


#ifdef __cplusplus
extern "C" {
#endif

#define PENDING_PACKETS_MAX 8
#define PACKETS_PER_TYPE_MAX 2

  typedef struct {
    PacketOperations ops;
    PacketHeader* packet_buffers[PACKETS_PER_TYPE_MAX]; // buffers for a message
    int packet_buffers_max;         // maximum number of messages
    int packet_buffers_size;        // number of good messages of a type
    int packet_buffers_start;       // first message idx
    int packet_buffers_end;         // last message idx
    PacketFn deferred_action_fn;    // this function is called out of an ISR, to process
                                    // the incoming packet
    void*   deferred_action_args;  
  }  DeferredPacketOps;

  typedef struct {
    PacketHandler base_handler;
    DeferredPacketOps    packet_infos[PACKET_TYPE_MAX];
    PacketHeader*  pending_packets[PENDING_PACKETS_MAX];
    int  pending_packets_size;
  }  DeferredPacketHandler;


  void DeferredPacketHandler_initialize(DeferredPacketHandler* h);

  PacketStatus DeferredPacketHandler_installPacket(DeferredPacketHandler* h,
                                                   PacketType type,
                                                   PacketSize size,
                                                   void* buffer,
                                                   int num_buffers,
                                                   PacketFn action,
                                                   void* action_args);

  void DeferredPacketHandler_processPendingPackets(DeferredPacketHandler* h);

#ifdef __cplusplus
}
#endif
