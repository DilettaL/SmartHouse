#include "serial_linux.h"

int serial_open(const char* name)
{
	int fd = open (name, O_RDWR | O_NOCTTY | O_SYNC );
	return fd;
}
