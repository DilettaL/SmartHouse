#include <stdio.h>
#include "smarthouse_comm.h"
#include "digio.h"


int main (int argc, char** argv)
{
	DigIO_init();
	Smarthouse_commInit();

	while(1)
	{
		Smarthouse_commHandle();
	}
}
