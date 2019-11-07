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

	h->rx_current_op=0;
	h->rx_current_packet=0;
	h->rx_checksum=0;
	h->rx_buffer=0;
	h->rx_buffer_end=0;
	h->rx_bytes_to_read=0;
	h->rxFn=_rxAA;
//	h->tx_size=0;
//	h->tx_start=0;
//	h->tx_end=0;
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
PacketStatus _rxAA(PacketHandler* h, uint8_t c){
 	h->rx_checksum=0;
	if (c==0xAA){
		h->rxFn=_rx55;
		return SyncAA;
	}
	return Unsync;
}

PacketStatus _rx55(PacketHandler* h, uint8_t c){
	if (c==0x55) {
		h->rxFn=_rxType;
		h->rx_checksum=0;
		return Sync55;
	}
	h->rxFn=_rxAA;
	return Unsync;
}

//Se si attiva _rxType vuol dire che ho ricevuto correttamente i 2 byte della la trama di sincronia 0xAA 0x55
PacketStatus  _rxType(PacketHandler* h, uint8_t c){
	h->rx_checksum^=c;
	if ( c>=PACKET_TYPE_MAX) {	//condizione di fallimento sul valore dell'ID del Type. Confronto con ops installata
		h->rxFn=_rxAA;
		return Unsync;
	}
	h->rx_current_op=h->operations[c];	
	if (! h->rx_current_op) {
		h->rxFn=_rxAA;
		return UnknownType;
	}
	h->rxFn=_rxSize;
	return SyncType;
}

PacketStatus _rxSize(PacketHandler* h, uint8_t c) {
	if (h->rx_current_op->size!=PACKET_SIZE_ANY && h->rx_current_op->size!=c) {	//condizione di fallimento. Confronto con ops installata
		h->rxFn=_rxAA;
		printf("invalid size, type: %d, desired: %d, received: %d\n",
		h->rx_current_op->type,
		h->rx_current_op->size,
		c);
		return InvalidSize;
	}
	h->rx_current_packet=(*h->rx_current_op->initialize_buffer_fn)
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
}

PacketStatus _rxPayload(PacketHandler* h, uint8_t c) {
	h->rx_checksum^=c;
	*h->rx_buffer_end=c;
	++h->rx_buffer_end;
	--h->rx_bytes_to_read;
	if (! h->rx_bytes_to_read) {
		h->rxFn=_rxChecksum;
		return SyncPayloadComplete;
	}
	return SyncPayload;
}

PacketStatus _rxChecksum(PacketHandler* h, uint8_t c){
	h->rxFn=_rxAA;
	h->rx_buffer=0;
	h->rx_buffer_end=0;
	if (c==h->rx_checksum) {
		if (h->rx_current_op->on_receive_fn)
			(*h->rx_current_op->on_receive_fn)(h->rx_current_packet,
				h->rx_current_op->on_receive_args);
	return SyncChecksum;
	}
	/*else {
		printf("wrong checksum, expected: %02x, got: %02x\n", h->rx_checksum, c);
	}
	*/
	return ChecksumError;
}

static inline void _putTxByte(PacketHandler* h, uint8_t c){
	if (h->tx_size==PACKET_SIZE_MAX)
		return;
	h->tx_buffer[h->tx_end]=c;
	BUFFER_PUT(h->tx, PACKET_SIZE_MAX);
}

uint8_t PacketHandler_txByte(PacketHandler* h){
	if (!h->tx_size) {
	return 0;
	}
	uint8_t c=h->tx_buffer[h->tx_start];
	BUFFER_GET(h->tx, PACKET_SIZE_MAX);
	return c;
}

PacketStatus PacketHandler_sendPacket(PacketHandler* h, PacketHeader* header) {
	// we check if we have enough room in the buffer
	int tx_free=PACKET_SIZE_MAX-h->tx_size;
	int real_size=header->size+3;
	if (tx_free<real_size)
		return TxBufferFull;
	_putTxByte(h, 0xAA);
	_putTxByte(h, 0x55);
	h->tx_checksum=0;
	uint8_t size=header->size;
	uint8_t* buf=(uint8_t*) header;
	while(size){
		h->tx_checksum^=*buf;
		_putTxByte(h,*buf);
		--size;
		++buf;
	}
	_putTxByte(h,h->tx_checksum);
	return Success;
}

