//gcc -pthread keyboard.c -o keyboard.out
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>//per open
#include <fcntl.h>
#include <unistd.h> //per read in listen_serial
void *listen_keyboard()
{
	
	int stop_wait=0;
	char ch;
	while(stop_wait!=1)	
	{
		printf("Insert keyboard input:\n");	
		ch=getchar();
		if(ch < 0)
		{
            		if (ferror(stdin))
			{
              			clearerr(stdin);
			}	        
		}
		else
		{ stop_wait = 1; }
	}
	//apertura shell per l'invio dei comandi
	//flushInputBuffer
}

void *listen_serial()
{
	printf("Seriale\n");
	int serial=open ("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC );
  	if (serial < 0)
	{
    		printf ("error opening serial, serial %d\n", serial);
  	}
	char c;
//	while(c!=EOF)
//	{
		read(serial, &c, 1);
		printf("letto %02x\n", (unsigned int)c);
//	}
/*

int serial_set_interface_attribs(int fd, int speed, int parity) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
    printf ("error %d from tcgetattr", errno);
    return -1;
  }
  switch (speed){
  case 19200:
    speed=B19200;
    break;
  case 57600:
    speed=B57600;
    break;
  case 115200:
    speed=B115200;
    break;
  default:
    printf("cannot sed baudrate %d\n", speed);
    return -1;
  }
  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);
  cfmakeraw(&tty);
  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);               // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;      // 8-bit chars

  if (tcsetattr (fd, TCSANOW, &tty) != 0) {
    printf ("error %d from tcsetattr", errno);
    return -1;
  }
  return 0;
}

void serial_set_blocking(int fd, int should_block) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
      printf ("error %d from tggetattr", errno);
      return;
  }
*/

/*serial test:  int fd=serial_open(argv[1]);
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
  }*/
}

int main(int argc, char *argv)
{
	pthread_t keyboard, serial;
	pthread_attr_t attr_keyboard, attr_serial;
	pthread_attr_init(&attr_keyboard);
	pthread_attr_init(&attr_serial);
	int control1=pthread_create(&keyboard, &attr_keyboard, listen_keyboard, NULL);
	int control2=pthread_create(&serial, &attr_serial, listen_serial, NULL);
	if (control1 || control2)
	{
         	printf("ERROR; return code from pthread_create()\n");
         	exit(-1);
      	}
	while(	pthread_join(keyboard, NULL)!=0 || pthread_join(serial, NULL)!=0 );
	pthread_exit(NULL);
	return 0;
}
