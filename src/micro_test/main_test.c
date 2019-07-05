#include <avr/io.h>
#include "digio.h"
#include <util/delay.h>

int main(int argc, char *argv[])
{
	while(1)
	{
	int i;
		for(i=3; i<13; i++)
		{
			ledOn(i);
			_delay_ms(500);
			ledOff(i);
			if(i==12)
			{i=2;}
		}
	}
	return 0;
}
