#pragma once
#include <stdint.h>

//3a)
typedef enum
{
	/*error conditions*/
	UnknownType=-1,
	RxBufferError=-2,
	InvalidSize=-3,
	ChecksumError=-4,
	Unsync=-5,
	PacketTypeOutOfBounds=-6,
	PacketInstallError=-7,
	PacketUninstallError=-8,
	TxBufferFull=-9,
	NoHandler=-10,
	Timeout=-11,
	WrongPins=-12,
	VersionMismatch=-13,
	GenericError=-127,  
	/*success conditions*/
	Success=0,
	SyncAA=1,
	Sync55=2,
	SyncType=3,
	SyncSize=4,
	SyncPayload=5,
	SyncPayloadComplete=6,	
	SyncChecksum=7
} PacketStatus;

//3b)
struct PacketHandler; //questa inizializzazione presente nel file packet_handler.h non so se ci va
typedef struct PacketHandler
{
	//4f)
	PacketOperations *operations[PACKET_TYPE_MAX];

	//5a)
	// used while reading a packet
	PacketOperations* rx_current_op;
	//6) 
	PacketHeader* rx_current_packet;
	//7)	
	uint8_t rx_checksum;
  	uint8_t* rx_buffer;
	uint8_t* rx_buffer_end;
	PacketSize rx_bytes_to_read;
	//8b)
	PacketHandlerRxFn rxFn;

	//9)
	uint8_t tx_buffer[PACKET_SIZE_MAX];
	int tx_start;
	int tx_end;
	int tx_size;
	uint8_t tx_checksum;
} PacketHandler;

//4a)
#define PACKET_TYPE_MAX 20
//13a)
#define PACKET_SIZE_ANY 0xFF

//4b)
struct PacketOperations;
typedef struct PacketOperations {
	//5b)
	PacketType type;
	PacketSize size; // expected size of the payload, -1 if error;

	//5c)
	*PacketGenFn initialize_buffer_fn;
 	void* initialize_buffer_args;
	PacketFn on_receive_fn;
	void* on_receive_args;
} PacketOperations;

//4d)
typedef uint8_t PacketType;
typedef uint8_t PacketSize;
typedef uint16_t PacketSeq;
#pragma pack(push, 1)
typedef struct
{
	PacketType type;  // type of the packet < PACKET_TYPE_MAX
	PacketSize size;  // size of the packet in bytes
	PacketSeq  seq;   // sequential number always increased
} PacketHeader;
#pragma pack(pop)

//5d)
typedef PacketStatus  (*PacketFn)(PacketHeader*, void* args);
typedef PacketHeader*  (*PacketGenFn)(PacketType type,
                                      PacketSize size,
                                      void* args);

//8a)
typedef PacketStatus (*PacketHandlerRxFn)(struct PacketHandler*, uint8_t c);

//16a)
// initializes an empty packet handler
PacketStatus PacketHandler_initialize(PacketHandler* h);

//17a)
// installs the manager for packet operations
PacketStatus PacketHandler_installPacket(PacketHandler* h, PacketType type, PacketSize size, void* buffer, PacketFn action, void* action_args);
// removes a packet
PacketStatus PacketHandler_uninstallPacket(PacketHandler* h, PacketType type);


//18a)
// processes a byte if available from the rx buffer
PacketStatus PacketHandler_rxByte(PacketHandler* handler, uint8_t c);
