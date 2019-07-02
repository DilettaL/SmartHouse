#include <avr/io.h>
#include "digio.h"

int main(int argc, char *argv[])
{
	while(1)
	{
		ledOn(13);
	}
	return 0;
}
