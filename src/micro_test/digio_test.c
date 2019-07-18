#include <avr/io.h>
#include "digio.h"
#include <util/delay.h>

int main(int argc, char *argv[])
{
//Test ledOn e led Off su pin da 2 a 13:
	while(1)
	{
	int i;
		for(i=2; i<13; i++)
		{
			_delay_ms(500);
			ledOn(i);
			_delay_ms(500);
			ledOff(i);
			if(i==12)
			{i=2;}
		}
	}
	return 0;
}
