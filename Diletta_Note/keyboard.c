//gcc -pthread keyboard.c -o keyboard.out

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *listen_keyboard()
{
	int stop_wait=0;
	char ch;
	while(stop_wait!=1)	
	{
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
	printf("OpenShell\n");
	//flushInputBuffer
}

int main(int argc, char *argv)
{
	pthread_t keyboard;
	pthread_attr_t attr_keyboard;
	pthread_attr_init(&attr_keyboard);
	int control=pthread_create(&keyboard, &attr_keyboard, listen_keyboard, NULL);
	if (control)
	{
         	printf("ERROR; return code from pthread_create() is %d\n", control);
         	exit(-1);
      	}
	printf("Insert keyboard input:\n");	
	pthread_join(keyboard, NULL);
	pthread_exit(NULL);
	return 0;
}
