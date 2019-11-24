#include "smarthouse_globals.h"

SystemParamPacket system_params = 
{
	{
		.type=SYSTEM_PARAM_PACKET_ID,
		.size=sizeof(SystemParamPacket),
		.seq=0
	},
	.protocol_version= SMARTHOUSE_PROTOCOL_VERSION,
	.firmware_version= SMARTHOUSE_FIRMWARE_VERSION,
//	.timer_period_ms=10,
	.comm_speed=115200
//	.comm_cycles=2,
//	.periodic_packet_mask=(PSystemStatusFlag|PJointStatusFlag|PDriveStatusFlag|PSonarStatusFlag),
//	.watchdog_cycles=0,
//	.num_joints=NUM_JOINTS
};

SystemStatusPacket system_status = {
  {.type=SYSTEM_STATUS_PACKET_ID,
   .size=sizeof(SystemStatusPacket),
   .seq=0
  },
  .rx_seq=0,
  .rx_packet_queue=0,
  .idle_cycles=0
};

TestPacket test=
{
	{
		.type=TEST_PACKET_ID,
		.size=sizeof(TestPacket),
		.seq=0
	},
	.prova=0
};

StringMessagePacket string_message =
{
	{
		.type=MESSAGE_PACKET_ID,
		.size=sizeof(StringMessagePacket),
		.seq=0
	},
	.message=0
};
