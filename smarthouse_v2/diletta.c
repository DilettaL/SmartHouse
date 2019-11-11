//_initializeBuffer for firmware

//Questa funzione deve far si che il puntatore di packetheader punti alla corrispettiva porzione di memoria per un determinato pacchetto in modo che, una volta giunti al payload, si possa iniziare a leggere direttamente il contenuto
static PacketHeader* _initializeBuffer_firmware(PacketType type, PacketSize size, void* arg)
{
	PacketHandler* handler=(PacketHandler*)arg;
	return (PacketHeader*) handler->rx_current_packet;
}

//Per capire come fare l'_onReiceve_firmware bisogna capire coem funziona il installPacket
PacketStatus PacketHandler_installPacket()
{

} 

static PacketStatus _onReceive_firmware(PacketHeader *packet, void* arg)
{
	PacketHandler *handler=(PacketHandler*)arg;
//arg deve essere un riferimento alla struc di globals
//packet è il packetheader di quel pacchetto (risultato di intiaizeBuffer) che è stato ricevuto e va copiato in memoria
	memcpy(handler, packet, packet->size);
	return Success;
}
