#include <stdio.h>
#include "serial_linux.h"

int main(int argc, char **argv) {
  int fd=serial_open(argv[1]);
  if (fd<0) {
    return -1;
  }
  int attrib_ok=serial_set_interface_attribs(fd, 19200, 0);
  serial_set_blocking(fd, 1);
  printf("attr: %d\n", attrib_ok);
  while(1) {
    char c;
    read(fd, &c, 1);
    printf("letto %02x\n", (unsigned int)c);
  }
}
