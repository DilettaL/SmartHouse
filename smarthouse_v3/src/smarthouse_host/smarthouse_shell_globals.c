#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smarthouse_shell_globals.h"
#include "smarthouse_client.h"


struct SmarthouseClient* client=0;
int run=1;

SystemParamPacket system_params=
{
  .header.type=SYSTEM_PARAM_PACKET_ID,
  .header.size=sizeof(SystemParamPacket)
};

SystemStatusPacket system_status=
{
  .header.type=SYSTEM_STATUS_PACKET_ID,
  .header.size=sizeof(SystemStatusPacket)
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

StringMessagePacket string_message={
  .header.type=MESSAGE_PACKET_ID,
	.header.size=sizeof(StringMessagePacket)
};
