#include <avr/io.h>
#include "digio.h"

int main(int argc, char *argv[])
{
	while(1)
	{
		ledDimmer(11, 0);
	}
	return 0;
}
