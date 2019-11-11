#pragma once
#include <sys/types.h>//per open
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int serial_open(const char* );

int serial_set_interface_attribs(int fd, int speed, int parity);
