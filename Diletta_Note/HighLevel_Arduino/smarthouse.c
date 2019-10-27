#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
//Librerie basso livello
#include "eeprom.h"
#include "digio.h"
#include "adc.h"
//Librerie alto livello
#include "smarthouse_comm.h"

int main(int argc, char** argv)
{
	// initialize devices
	// initialize high level
	Smarthouse_commInit();
	while(1)
	{
		Smarthouse_commHandle();
	}
}
