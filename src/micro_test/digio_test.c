#include <avr/io.h>
#include "digio.h"
#include <util/delay.h>

int main(int argc, char *argv[])
{
//Test ledOn e led Off su pin da 2 a 13:
	while(1)
	{
		for(int i=2; i<14; i++)
		{
			ledOn(i);
			_delay_ms(500);
			ledOff(i);
			_delay_ms(500);
		}
	}
	return 0;
}
