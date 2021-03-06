#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smarthouse_shell.h"
#include "packet_header.h"

int idx;

int helpFn (void)
{
	printBanner();	
	return 0;
}

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
	int control;
	printf("Insert pin (from 2 to 13):\n");
	if((control=scanf("%d", &idx))<1 || idx <2 )
	{	
		printf("Error\n");
		return 0;	
	}
	digital_config.pin_digital= idx;
	digital_config.set_digital=ledOff;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int ledOnFn(void)
{
	int control;
	printf("Insert pin (from 2 to 13):\n");
	if((control=scanf("%d", &idx))<1 || idx <2 )
	{	
		printf("Error\n");
		return 0;	
	}
	digital_config.pin_digital= idx;
	digital_config.set_digital=ledOn;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int dimmerFn(void)
{
	int control;
	int intensity;
	printf("Insert pin (from 2 to 13):\n");
	if((control=scanf("%d", &idx))<1 || idx <2 )
	{	
		printf("Error\n");
		return 0;	
	}
	printf("Insert intensity:\n");
	if((control=scanf("%d", &intensity))<1)
	{	
		printf("Error\n");
		return 0;	
	}
	digital_config.set_digital=dimmer;
	digital_config.pin_digital=idx;
	digital_config.intensity=intensity;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int digitalInputFn(void)
{
	int control;
	printf("Insert pin (from 2 to 13):\n");
	if((control=scanf("%d", &idx))<1 || idx <2 )
	{	
		printf("Error\n");
		return 0;	
	}
	digital_config.pin_digital=idx;
	digital_config.set_digital=input_digital;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int adcFn(void)
{
	int control;
	int samples;
	printf("Insert pin:\n");
	if((control=scanf("%d", &idx))<1){printf("Error\n");}
	printf("Insert samples:\n");
	if((control=scanf("%d", &samples))<0 || samples > 10)
	{	
		printf("Error. max samples = 10\n");
		return 0;	
	}
	analog_config.pin_analog=idx;
	analog_config.samples=samples;
	pointer_packet=(PacketHeader*)&analog_config;
	return 0;
}

int requestFn(void)
{
	int control;
	char string[8];
	printf("Insert pin:\n");
	if((control=scanf("%d", &idx))<1)
	{	
		printf("Error\n");
		return 0;	
	}
	printf("Insert type of packet (analog or digital):\n");
	if((control=scanf("%s", string))<0){printf("Error\n");}
	if( (control=strcmp(string, "analog"))==0)
	{
		pointer_packet=(PacketHeader*)&analog_status[idx];
	}
	else if( (control=strcmp(string, "digital"))==0)
	{
		pointer_packet=(PacketHeader*)&digital_status[idx];
	}
	else
	{
		printf("Incorrect setting\n");
	}
	return 0;
}

int saveFn(void)
{
	int control;
	char string[7];
	eeprom.action=0;
	printf("Insert pin:\n");
	if((control=scanf("%d", &idx))<1)
	{	
		printf("Error\n");
		return 0;	
	}
	eeprom.pin=idx;	
	printf("Insert type of packet (analog or digital):\n");
	if((control=scanf("%s", string))<0){printf("Error\n");}
	if( (control=strcmp(string, "analog"))==0)
	{
		eeprom.type_pin=0;
	}
	else if ( (control=strcmp(string, "digital"))==0)
	{
		eeprom.type_pin=1;
	}
	else
	{
		printf("Incorrect setting\n");
	}
	pointer_packet=(PacketHeader*)&eeprom;
	return 0;
}

int loadFn(void)
{
	int control;
	char string[7];
	eeprom.action=1;
	printf("Insert pin:\n");
	if((control=scanf("%d", &idx))<1)
	{	
		printf("Error\n");
		return 0;	
	}
	eeprom.pin=idx;	
	printf("Insert type of packet (analog or digital):\n");
	if((control=scanf("%s", string))<1)
	{	
		printf("Error\n");
		return 0;	
	}
	if( (control=strcmp(string, "analog"))==0)
	{
		eeprom.type_pin=0;
	}
	else if ( (control=strcmp(string, "digital"))==0)
	{
		eeprom.type_pin=1;
	}
	else
	{
		printf("Incorrect setting\n");
	}
	pointer_packet=(PacketHeader*)&eeprom;
	return 0;
}

Command commands[] =
{
	{
		.name= "help",
		.cmd_fn=helpFn,
		.help="usage: help"
	},
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
	},	
	{
		.name= "save",
		.cmd_fn=saveFn,
		.help="usage: save"
	},	
	{
		.name= "load",
		.cmd_fn=loadFn,
		.help="usage: load"
	}
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

int executeCommand(const char* line_)
{
	char line[1024];
	int retval=0;
	strcpy(line, line_);
  	char* name=strtok(line," ");
	if (! name)
	{	
		printf ("Command not found. Reload the program and insert correct name command\n");
		name="help";
//		return -1;
	} 
	Command* cmd=findCommand(name); 	
	if (! cmd)
	{
		printf("ERROR: unknown command [%s]\n", name);
		return -1;
	}
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

