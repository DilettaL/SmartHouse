#include <avr/io.h>
#include "digio.h"
#include "delay.h"

int main(int argc, char *argv[])
{
	while(1)
	{
		for(int i=2; i<13; i++)
		{
			ledOn(i);
			_delay_ms(1000);
			ledOff(i);
			if(i==12)
			{i=2;}
		}
	}
	return 0;
}
