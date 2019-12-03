#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "smarthouse_shell.h"
uint8_t setPin(void)
{
	uint8_t pin;
	print("insert pin:\n");
	scanf("%ld\n", &pin);
	if(pin >=0 && pin<=15)
	{	return pin;	}
	else
	{	return -1;	}
}

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
	uint8_t set_pin=setPin();
	if(set_pin<=-1)
	{	return -1;	}
	digital_config.pin_digital=set_pin;
	digital_config.set_digital=ledOff;
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
		.hel="usage: request"
	}
};
