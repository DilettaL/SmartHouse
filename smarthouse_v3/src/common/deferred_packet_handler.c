#include <string.h>
#include <assert.h>
#include "buffer_utils.h"
#include "deferred_packet_handler.h"




// when a buffer is requested, we pick one from the ring buffer, if available
static PacketHeader* _initializeBuffer(PacketType type,
                                       PacketSize size,
                                       void* args ) {
  DeferredPacketHandler* handler=(DeferredPacketHandler*) args;
  DeferredPacketOps* info=handler->packet_infos +type;
  // if no buffer available, return
  if (info->packet_buffers_size>=info->packet_buffers_max)
    return 0;
  // otherwise we return the last buffer
  return info->packet_buffers[info->packet_buffers_end];
}

// a packet is complete, we know it is the last one in the pool
// we advance the pointer
static PacketStatus _onReceive(PacketHeader* packet,
                               void* args) {
  
  DeferredPacketHandler* handler=(DeferredPacketHandler*) args;
  DeferredPacketOps* info=handler->packet_infos + packet->type;
  // the packet should be the one we were writing
  assert(packet==info->packet_buffers[info->packet_buffers_end]);

  if (handler->pending_packets_size>=PENDING_PACKETS_MAX)
    return Success; // there is no room in the buffer to process this packet

  handler->pending_packets[handler->pending_packets_size]=packet;
  // this will advance the end pointer and the packet will become available
  // for deferred processing
  BUFFER_PUT(info->packet_buffers, info->packet_buffers_max);
  ++handler->pending_packets_size;
  return Success;
}

PacketStatus DeferredPacketHandler_installPacket(DeferredPacketHandler* h,
                                                 PacketType type,
                                                 PacketSize size,
                                                 void* buffer,
                                                 int num_buffers,
                                                 PacketFn action,
                                                 void* action_args){
  //is the type already registered?
  if (type>=PACKET_TYPE_MAX)
    return PacketInstallError;
  DeferredPacketOps src_info=
    {
      {type,
       size,
       _initializeBuffer,
       (void*)h,
       _onReceive,
       (void*)h,
      },
      {0,0},
      num_buffers,
      0,
      0,
      0,
      action,
      action_args
    };
  char* b=buffer;
  for (int i=0; i<num_buffers; ++i){
    src_info.packet_buffers[i]=(PacketHeader*) b;
    b+=size;
  }
  
  DeferredPacketOps* dest_info=h->packet_infos+type;
  *dest_info=src_info;
  return PacketHandler_installPacket(&h->base_handler, &dest_info->ops);
}

void DeferredPacketHandler_processPendingPackets(DeferredPacketHandler* h){
  for (int pnum=0; pnum<h->pending_packets_size; ++pnum){
    PacketHeader* p=h->pending_packets[pnum];
    DeferredPacketOps* info=h->packet_infos+p->type;

    // we check that the packet is the first in its own buffer
    assert(p==info->packet_buffers[info->packet_buffers_start]);
    // if an action is present, we execute it
    if (info->deferred_action_fn)
      (*info->deferred_action_fn)(p, info->deferred_action_args);
    // we clear the buffer
    BUFFER_GET(info->packet_buffers, info->packet_buffers_max);
  }
  h->pending_packets_size=0;
}

void DeferredPacketHandler_initialize(DeferredPacketHandler* h){
  PacketHandler_initialize(&h->base_handler);
  memset(&h->packet_infos, 0, sizeof(h->packet_infos));
  h->pending_packets_size=0;
}

