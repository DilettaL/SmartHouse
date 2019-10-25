#include "smarthouse_globals.h"
//#include "orazio_pins.h" bisogna ancora crearlo questo file

//these packets are global variables that contain the state of our system and of the parameters
//they are updated automatically by the communication routines the status packets are updated and sent by various subsystems

SystemParamPacket system_params = {
	//questa è l'inizializzazione del PacketHeader
	{
		.type=SYSTEM_PARAM_PACKET_ID,
		.size=sizeof(SystemParamPacket),
		.seq=0
	},
	//questa non so dove.protocol_version=ORAZIO_PROTOCOL_VERSION,
	.firmware_version=SMARTHOUSE_FIRMWARE_VERSION, //dichiarato in smarthouse_globals.h
	//.timer_period_ms=10,
	.comm_speed=115200, //baudrate
	//.comm_cycles=2,
	//.periodic_packet_mask=(PSystemStatusFlag|PJointStatusFlag|PDriveStatusFlag|PSonarStatusFlag),
	//.watchdog_cycles=0,
	//.num_joints=NUM_JOINTS
};

