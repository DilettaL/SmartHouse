#include <stdio.h>
#include "packet_handler.h"
#include "buffer_utils.h"

PacketStatus PacketHandler_initialize(PacketHandler* h)
{
//  for(int i=0; i<PACKET_TYPE_MAX; ++i)
//    h->operations[i]=0;

//  h->rx_current_op=0;
//  h->rx_current_packet=0;
//  h->rx_checksum=0;
//  h->rx_buffer=0;
//  h->rx_buffer_end=0;
//  h->rx_bytes_to_read=0;
	h->rxFn=_rxAA;
//  h->tx_size=0;
//  h->tx_start=0;
//  h->tx_end=0;
	return Success;
}
