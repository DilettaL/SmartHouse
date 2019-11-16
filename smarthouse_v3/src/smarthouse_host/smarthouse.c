#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "smarthouse_client.h"
#include "smarthouse_shell_globals.h"

const char *banner[]={
	"Smarthouse",
	"usage:",
	"$>Smarthouse	...",
	"to choice operation insert one of this commands(then choice the pin and other settings):",
	"$>Smarthouse	ledOn",
	"$>Smarthouse	dimmer",
	"$>Smarthouse	digital input",
	"$>Smarthouse	ledOff",
	"$>Smarthouse	adc",
	"to request a status packet insert(then choice packet type):",
	"$>Smarthouse	request",
	"to exit insert:",
	"$>Smarthouse	quit"
};

void printBanner(void)
{
	const char*const* line=banner;
	while (*line)
	{
		printf("%s\n",*line);
		line++;
	}
}
//Si prova a far accendere il pin 10 con ledOn

int main(int argc, char** argv)
{
	const char* device="/dev/tty"; //non capisco per ora se va bene 0 come lui o tutto il percorso dell'usb
	uint32_t baudrate = 19200;
//*************************INIZIO: PACCHETTO DI PROVA
//Il pacchetto di prova è inizializzato dentro SmarthouseClient_init();
	printBanner();
	printf("initialization...\n");
	client=SmarthouseClient_init(device, baudrate);
	if (! client)
	{
		printf("Failed\n");
		exit(-1);
	}
	printf("Success\n");
//Invio il pacchetto di prova
	while (1)
	{
		SmarthouseClient_sendPacket(client, (PacketHeader*)&test);
	}
/*************************FINE: PACCHETTO DI PROVA*/
	//Creare il thread per la lettura dalla seriale
//	printf("looping...");
	//Smarthouse_shellStart();
	return 0;
}
