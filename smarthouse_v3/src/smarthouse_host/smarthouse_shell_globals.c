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

TestPacket test=
{
	.header.type=TEST_PACKET_ID,
	.header.size=sizeof(TestPacket)
};

void Orazio_shellStart(void) 
{
	printf("shell started\n");
	//stuff
	while (run)
	{
		char *buffer = readline("Smarthouse $> ");
		if (buffer)
		{
			char response[10000];
			executeCommand(response, buffer);
			if (*buffer)
			{
				add_history(buffer);
				free(buffer);
			}
		}
		else
		{	run=0;	}

	}
}
