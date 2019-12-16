#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smarthouse_shell.h"
#include "packet_header.h"

int pin;

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
	digital_config.pin_digital=(uint8_t)pin;
	digital_config.set_digital=ledOff;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int ledOnFn(void)
{
	digital_config.pin_digital= (uint8_t)pin;
	digital_config.set_digital=ledOn;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int dimmerFn(void)
{	
	int intensity;
	digital_config.pin_digital= (uint8_t)pin;
	digital_config.set_digital=dimmer;
	printf("Insert intensity:\n");
	if( scanf("%d", &intensity)<0){printf("Errore");} 
	digital_config.intensity=(uint8_t)intensity;	
return 0;
}

int digitalInputFn(void)
{
	digital_config.pin_digital=(uint8_t)pin;
	digital_config.set_digital=input_digital;
	return 0;
}

int adcFn(void)
{
	digital_config.pin_digital=(uint8_t)pin;
	int sample;	
	printf("Insert number of samples:\n");
	if(scanf("%d", &sample)>=0)
	{
		analog_config.samples=(uint8_t)sample;
	}
	return 0;
}

int requestFn(void)
{
	char insert[20];
	printf("Insert the status packet type\t(Es. digital\tor\tanalog)\n");
	if(scanf("%s", insert)<0){printf("Errore\n");}
	if(strcmp(insert, "digital"))
	{
		digital_status.pin_digital=(uint8_t)pin;
		pointer_packet=(PacketHeader*)&digital_status;
	}
	else if(strcmp(insert,"analog"))
	{
		analog_status.pin_analog=(uint8_t)pin;
		pointer_packet=(PacketHeader*)&analog_status;
	}
	else
	{
		printf("Error status packet\n");
	}
	return 0;
}
Command commands[] =
{
	{
		.name = "quit",
		.cmd_fn=quitFn,
		.help="usage: quit"
	},
	{
		.name = "ledOff",
		.cmd_fn=ledOffFn,
		.help="usage: ledOff"
	},
	{
		.name = "ledOn",
		.cmd_fn=ledOnFn,
		.help="usage: ledOn"
	},
	{
		.name = "dimmer",
		.cmd_fn=dimmerFn,
		.help="usage: dimmer"
	},
	{
		.name = "digital_input",
		.cmd_fn=digitalInputFn,
		.help="usage: digital_input"
	},
	{
		.name = "adc",
		.cmd_fn=adcFn,
		.help="usage: adc"
	},
	{
		.name= "request",
		.cmd_fn=requestFn,
		.help="usage: request"
	}/*,
	{
		.name= "loadFn",
		.cmd_fn=requestFn,
		.help="usage: request"

	},
	{
		.name= "request",
		.cmd_fn=requestFn,
		.help="usage: request"

	}*/
};

const int num_commands=sizeof(commands)/sizeof(Command);

Command* findCommand(const char* name)
{
	int cmd_idx=0;
	while(cmd_idx<num_commands)
	{
		if (! strcmp(commands[cmd_idx].name, name))
		{
			return &commands[cmd_idx];
		}
		cmd_idx++;
	}
	return 0;
}

int executeCommand(void)//const char* line_)
{
	printf("Insert function:\n");
	char name[20];
	if(scanf("%s", name)<0){printf("Errore\n");}	
	Command* cmd=findCommand(name);
  	if (! cmd)
	{
		printf("ERROR: unknown command [%s]\n", name);
		return -1;
	}
	printf("Insert pin:\n");
	if(scanf("%d", &pin)<0){printf("Errore\n");}
	int retval=0;
	if (cmd->cmd_fn)
	{
		retval=(*cmd->cmd_fn)();
		if (retval)
		{	printf("ERROR %d\n", retval);	}
		else
		{	printf("Packet transmitt\n");		}
	}
	else
	{	printf("ERROR: no handler for command\n");	}
	return retval;

}

