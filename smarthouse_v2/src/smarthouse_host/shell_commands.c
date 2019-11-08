#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell_commands.h"
#include "smarthouse_client.h"

uint8_t setPin(void)
{
	uint8_t pin;
	print("insert pin:\n");
	scanf("%ld\n", &pin);
}

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOnFn(void)
{
	uint8_t set_pin=setPin();
	if(set_pin>=0 && set_pin<=20)
	{
		cl->digital_params+set_pin.type=ledOn;
		return 0;	
	}
	else
	{	return 1;	}
}

int dimmerFn(void)
{
	uint8_t set_pin=setPin();
	uint8_t intensity=0;
	if(set_pin>=0 && set_pin<=20)
	{	
		cl->digital_params+set_pin.type=dimmer;
		printf("Insert intensity:\n");
		scanf("%ld", &intensity);
		cl->digital_params+set_pin.intensity=intensity;
		return 0;	
	}
	else
	{	return 1;	}
}

int digitalInputFn(void)
{
	uint8_t set_pin=setPin();
	uint8_t numb_input=0;
	if(set_pin>=0 && set_pin<=20)
	{	
		cl->digital_params+set_pin.type=digitalInput;
		printf("Insert number of digital inputs:\n");
		scanf("%ld", &numb_input);
		cl->ditgital_params+set_pin.input=numb_input;
		return 0;	
	}
	else
	{	return 1;	}
	
}

int adcFn(void)
{
	uint8_t set_pin=setPin();
	uint8_t numb_samples=0;
	if(set_pin>=0 && set_pin<=20)
	{	
		cl->analog_params+set_pin.type=Adc;
		printf("Insert number of samples:\n");
		scanf("%ld", &numb_samples);
		cl->analog_params+set_pin.samples=numb_samples;
		return 0;	
	}
	else
	{	return 1;	}
}

int ledOffFn(void)
{
	uint8_t set_pin=setPin();
	if(set_pin>=0 && set_pin<=20)
	{	
		cl->digital_params+set_pin.type=ledOff;
		return 0;	
	}
	else
	{	return 1;	}
}

int requestFn(void)
{
	printf("implementare");
	return 0;
}

Command commands[] = {
	{
		.name = "quit",
		.cmd_fn=quitFn,
		.help="usage: quit",
	},
	{
		.name = "ledOn",
		.cmd_fn=ledOnFn,
		.help="usage: ledOn",
	}
	{
		.name = "dimmer",
		.cmd_fn=dimmerFn,
		.help="usage: dimmer",
	},
	{
		.name = "digital_input",
		.cmd_fn=digitalInputFn,
		.help="usage: digital_input",
	},
	{
		.name = "ledOff",
		.cmd_fn=ledOffFn,
		.help="usage: ledOff",
	},
	{
		.name = "adc",
		.cmd_fn=adcFn,
		.help="usage: adc",
	},
	{
		.name= "request",
		.cmd_fn=requestFn,
		.hel="usage: request"
	}
};

const int num_commands=sizeof(commands)/sizeof(Command);

Command* findCommand(const char* name)
{
	int cmd_idx=0;
	while(cmd_idx<num_commands)
	{
		if (! strcmp(commands[cmd_idx].name, name)){
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
	{	return -1;	}
	Command* cmd=findCommand(name);
	if (! cmd)
	{
		printf("ERROR: unknown command [%s]\n", name);
		return -1;
	}
	int retval=0;
	if (cmd->cmd_fn)
	{
		retval=(*cmd->cmd_fn);
		if (retval)
		{	printf("ERROR %d\n", retval);	}
	}
	else
	{
		printf("ERROR: command not issued. Wrong setting\n %s\n", cmd->help);
	}
}
