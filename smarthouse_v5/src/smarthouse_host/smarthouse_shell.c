#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smarthouse_shell.h"
#include "packet_header.h"

int idx;

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
	int control;
	printf("Insert pin:\n");
	if((control=scanf("%d", &idx))<0){printf("Error\n");}
	digital_config.pin_digital= idx;
	digital_config.set_digital=ledOff;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int ledOnFn(void)
{
/*	printf("insert pin:\n");
	char *pinc = readline("");
	int pin = atoi(pinc)+atoi(pinc+1);
	printf("DEBUG:%s-%d\n", pinc, pin);
	uint8_t pint = (uint8_t)pin;//(uint8_t)pin;
	if(*pinc)
	{	free(pinc);	}
*/
	int control;
	printf("Insert pin:\n");
scanf("%d", &idx);

	digital_config.pin_digital= idx;
	digital_config.set_digital=ledOn;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int dimmerFn(void)
{/*
	int intensity=0;
	int pin;
	printf("insert pin:\n");
	
	uint8_t pint = (uint8_t)pin;
	digital_config[index].pin_digital=index;
	digital_config.set_digital=dimmer;
	printf("Insert intensity:\n");
	if(control>=0)
	{
		digital_config.intensity=(uint8_t)intensity%256;
		pointer_packet=(PacketHeader*)&digital_config;
		return 0;
	}
	else
	{	return -1;	}
*/
return 0;
}

int digitalInputFn(void)
{
/*	int pin;
	printf("insert pin:\n");

	uint8_t pint = (uint8_t)pin;
	digital_config.pin_digital=pint;
	digital_config.set_digital=input_digital;
	pointer_packet=(PacketHeader*)&digital_config;
*/	return 0;
}

int adcFn(void)
{/*
	int sample;
	int pin;
	printf ("Insert pin\n");

	uint8_t pint = (uint8_t)pin;
	digital_config.pin_digital=pint;
	printf("Insert number of samples:\n");
	if(scanf("%d", &sample)>=0)
	{
		analog_config.samples=(uint8_t)sample;
		pointer_packet=(PacketHeader*)&analog_config;
		return 0;
	}
	else
	{	return -1;	}
*/
return 0;
}

int requestFn(void)
{
	//Inserimento tipo pin
	//Inserimento pin
	idx=10;
	digital_status[idx].pin_digital=idx;
	pointer_packet=(PacketHeader*)&digital_status[idx];
//	pointer_packet=(PacketHeader*)analog_status[idx];
	return 0;
}

int saveFn(void)
{
	//decidere operazione se su digital o analog
	//tipo di pin
	pointer_packet=(PacketHeader*)&eeprom_write;
	return 0;
}

int loadFn(void)
{
	//decidere operazione se su digital o analog
	//tipo di pin
	pointer_packet=(PacketHeader*)&eeprom_read;
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
	},
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
	strcpy(line, line_);
  	char* name=strtok(line," ");
	if (! name)
		return -1;
	Command* cmd=findCommand(name);
  	if (! cmd)
	{
		printf("ERROR: unknown command [%s]\n", name);
		return -1;
	}
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

