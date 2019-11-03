#include <stdio.h>
#include "packet_handler.h"
#include "buffer_utils.h"

PacketStatus _rxAA(PacketHandler* h, uint8_t c);
PacketStatus _rx55(PacketHandler* h, uint8_t c);
PacketStatus _rxType(PacketHandler* h, uint8_t c);
PacketStatus _rxSize(PacketHandler* h, uint8_t c);
PacketStatus _rxPayload(PacketHandler* h, uint8_t c);
PacketStatus _rxChecksum(PacketHandler* h, uint8_t c);

PacketStatus PacketHandler_initialize(PacketHandler* h)
{
	for(int i=0; i<PACKET_TYPE_MAX; ++i)
	{	h->operations[i]=0;	}

//  h->rx_current_op=0;
//  h->rx_current_packet=0;
	h->rx_checksum=0;
//  h->rx_buffer=0;
//  h->rx_buffer_end=0;
//  h->rx_bytes_to_read=0;
//	h->rxFn=_rxAA;
//  h->tx_size=0;
//  h->tx_start=0;
//  h->tx_end=0;
	return Success;
}

/**********************
Per installare un pacchetto quindi si controlla se è giusto il tipo e si crea una PacketOperations per quel singolo pacchetto. Successivamente si va ad associare l' i-esimo (dove i =tipo) elemento PacketOperations dell'handler al packetOperations in ingresso. 
**********************/
PacketStatus PacketHandler_installPacket(PacketHandler *h, PacketType type)
{
	//I parametri passati a questa funzione sono il packetHandler e gli argomenti di PacketOperations
	//Control type of packet
	if (type>=PACKET_TYPE_MAX)
		{	return PacketInstallError;	}
	//Associate ops argumento to ops struc
	PacketOperations ops =
	{
		type
	};
	if (h->operations[ops.type] != 0)
		{	return PacketInstallError;	}
	h->operations[ops.type] = &ops;
  	return Success;
}

//Receive
//Manca funzione che attiva la ricezione

//Transmitt
