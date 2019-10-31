#include "smarthouse_globals.h"
//#include "smarthouse_packets.h"
SystemParamPacket system_params = 
{
/*HEADER  {.type=SYSTEM_PARAM_PACKET_ID,
   .size=sizeof(SystemParamPacket),
   .seq=0
  },
*/
//  .protocol_version=ORAZIO_PROTOCOL_VERSION,
//  .firmware_version=ORAZIO_FIRMWARE_VERSION,
//  .timer_period_ms=10,
	.comm_speed=115200,
//  .comm_cycles=2,
//  .periodic_packet_mask=(PSystemStatusFlag|PJointStatusFlag|PDriveStatusFlag|PSonarStatusFlag),
//  .watchdog_cycles=0,
//  .num_joints=NUM_JOINTS
};
