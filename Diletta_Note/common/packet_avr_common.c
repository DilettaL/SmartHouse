#include <stdio.h>
#include "buffer_utils.h"
#include "packet_avr_common.h"

//2)
PacketStatus _rxAA(PacketHandler* h, uint8_t c);
PacketStatus _rx55(PacketHandler* h, uint8_t c);
PacketStatus _rxType(PacketHandler* h, uint8_t c);
PacketStatus _rxSize(PacketHandler* h, uint8_t c);
PacketStatus _rxPayload(PacketHandler* h, uint8_t c);
PacketStatus _rxChecksum(PacketHandler* h, uint8_t c);

//10)
PacketStatus _rxAA(PacketHandler* h, uint8_t c)
{
	h->rx_checksum=0;
	if (c==0xAA)
	{
		h->rxFn=_rx55;
		return SyncAA;
	}
	return Unsync;
}

//11)
PacketStatus _rx55(PacketHandler* h, uint8_t c)
{
	if (c==0x55)
	{
		h->rxFn=_rxType;
		h->rx_checksum=0;
		return Sync55;
	}
	h->rxFn=_rxAA;
	return Unsync;
}

//12
PacketStatus _rxType(PacketHandler* h, uint8_t c)
{
	h->rx_checksum^=c;
	if ( c>=PACKET_TYPE_MAX)
	{
		h->rxFn=_rxAA;
		return Unsync;
	}
	h->rx_current_op=h->operations[c];
	if (! h->rx_current_op)
	{
    		h->rxFn=_rxAA;
		return UnknownType;
	}
	h->rxFn=_rxSize;
	return SyncType;
}

//13)
PacketStatus _rxSize(PacketHandler* h, uint8_t c)
{
	if (h->rx_current_op->size!=PACKET_SIZE_ANY && h->rx_current_op->size!=c)
	{
 		h->rxFn=_rxAA;
		printf("invalid size, type:%d,desired:%d, received:%d\n", h->rx_current_op->type, h->rx_current_op->size, c);
		return InvalidSize;
	}
/*  h->rx_current_packet=(*h->rx_current_op->initialize_buffer_fn)
    (h->rx_current_op->type,
     h->rx_current_op->size,
     h->rx_current_op->initialize_buffer_args);
  if ( !h->rx_current_packet ) {
    h->rxFn=_rxAA;
    return RxBufferError;
  }
  h->rx_checksum^=c;
  h->rx_bytes_to_read=c-sizeof(PacketHeader)+sizeof(PacketSeq);
  h->rx_buffer=(uint8_t*) h->rx_current_packet;
  h->rx_buffer[0]=h->rx_current_op->type;
  h->rx_buffer[1]=h->rx_current_op->size;
  h->rx_buffer_end=h->rx_buffer+2;
  h->rxFn=_rxPayload;
  return SyncSize;
*/}

//16b)
PacketStatus PacketHandler_initialize(PacketHandler* h)
{
	for(int i=0; i<PACKET_TYPE_MAX; ++i)
	{	h->operations[i]=0;	}
	h->rx_current_op=0;
	h->rx_current_packet=0;
	h->rx_checksum=0;
	h->rx_buffer=0;
	h->rx_buffer_end=0;
	h->rx_bytes_to_read=0;
	h->rxFn=_rxAA;
	h->tx_size=0;
	h->tx_start=0;
	h->tx_end=0;
	return Success;
}

//17)

//18b)
PacketStatus PacketHandler_rxByte(PacketHandler* handler, uint8_t c)
{
	PacketStatus status = (*handler->rxFn)(handler, c);
	return status;
}

//19
