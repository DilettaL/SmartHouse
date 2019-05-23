#include <avr/io.h>
#include "pins.h"
//libreria pin digitali

const Pin pins[] =
  {
//Pin digitali i/o
	//PinAVR 6 PinBoard 2
	{
		.in_register=&PINE,
		.out_register=&PORTE,
		.dir_register=&DDRE,
		.bit=4,
		//PWM
		.tcc_register=0,
		.oc_register=0,
		.com_mask=0
	},
	//PinAVR 7 PinBoard 3
	{
		.in_register=&PINE,
		.out_register=&PORTE,
		.dir_register=&DDRE,
		.bit=5,
		//PWM
		.tcc_register=0,
		.oc_register=0,
		.com_mask=0
	},
	//PinAVR 1 PinBoard 4
	{
		.in_register=&PING,
		.out_register=&PORTG,
		.dir_register=&DDRG,
		.bit=5,
		//PWM
		.tcc_register=0,
		.oc_register=0,
		.com_mask=0
	},
	//PinAVR 5 PinBoard 5
	{
		.in_register=&PINE,
		.out_register=&PORTE,
		.dir_register=&DDRE,
		.bit=3,
		//PWM
		.tcc_register=0,
		.oc_register=0,
		.com_mask=0
	},
	//PinAVR 15 PinBoard 6
	{
		.in_register=&PINH,
		.out_register=&PORTH,
		.dir_register=&DDRH,
		.bit=3,
		//PWM
		.tcc_register=0,
		.oc_register=0,
		.com_mask=0
	},
	//PinAVR 16 PinBoard 7
	{
		.in_register=&PINH,
		.out_register=&PORTH,
		.dir_register=&DDRH,
		.bit=4,
		//PWM
		.tcc_register=0,
		.oc_register=0,
		.com_mask=0
	},
	//PinAVR 17 PinBoard 8
	//PinAVR 18 PinBoard 9
	//PinAVR 23 PinBoard 10
	//PinAVR 24 PinBoard 11
	//PinAVR 25 PinBoard 12
	//PinAVR 26 PinBoard 13
};
