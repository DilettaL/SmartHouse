#include <stdio.h>
#include "smarthouse_comm.h"

int main (int argc, char** argv)
{
	Smarthouse_commInit();
	while(1)
	{
		Smarthouse_commHandle();
	}
	return 0;
}
