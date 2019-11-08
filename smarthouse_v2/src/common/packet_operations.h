#pragma once
#include "packet_header.h"

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

struct PacketOperations;
struct PacketHandler;

typedef PacketStatus  (*PacketFn)(PacketHeader*, void* args);
typedef PacketHeader*  (*PacketGenFn)(PacketType type,
                                      PacketSize size,
                                      void* args);

typedef struct PacketOperations 
{
	PacketType type;
	PacketSize size; // expected size of the payload, -1 if error;
<<<<<<< HEAD
//	PacketGenFn initialize_buffer_fn;
//  void* initialize_buffer_args;
//  PacketFn on_receive_fn;
//  void* on_receive_args;
=======
	PacketGenFn initialize_buffer_fn;
	void* initialize_buffer_args;
	PacketFn on_receive_fn;
	void* on_receive_args;
>>>>>>> 3600cf87bdd0649a224f2b294f80b3fa7ec14540
} PacketOperations;
