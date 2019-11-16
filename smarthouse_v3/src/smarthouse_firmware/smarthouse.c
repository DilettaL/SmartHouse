#include <stdio.h>
#include "smarthouse_comm.h"
#include "digio.h"

int main (int argc, char** argv)
{
	DigIO_init();
	Smarthouse_commInit();
	int k = 1;
	while(k)
	{
		Smarthouse_commHandle();
		--k;
	}
	return 0;
}
