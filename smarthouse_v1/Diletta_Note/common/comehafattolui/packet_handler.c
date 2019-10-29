//Smarthouse
#include <stdio.h>
#include "packet_handler.h"
#include "buffer_utils.h"

//Il gestore dei pacchetti non è altro che la macchina a stati vista a lezione
//Ogni stato corrisponde ad una funzione, che attende il verificarsi di qualcosa prima di poter richiamare la successiva
//La trama di inizio pacchetto è AA55, quindi
//S1.a attendo che venga inviato AA
PacketStatus _rxAA(PacketHandler* h, uint8_t c);
//S1.b attendo che venga inviato 55
PacketStatus _rx55(PacketHandler* h, uint8_t c);
//S2 si legge il tipo del pacchetto in PacketHeader
PacketStatus _rxType(PacketHandler* h, uint8_t c);
//S3 si legge la dimensione del pacchetto in PacketHeader
PacketStatus _rxSize(PacketHandler* h, uint8_t c);
//S4 si legge il payload ovvero il contenuto vero e proprio del pacchetto
PacketStatus _rxPayload(PacketHandler* h, uint8_t c);
//S5 una volta letto il checksum si ritorna in attesa
PacketStatus _rxChecksum(PacketHandler* h, uint8_t c);
//-------------------------------------------------------------------------------------------------------------------------


