#include <stdio.h>
#include "uart.h"

void Smarthouse_comm_init(void)
{
	//inizializzo la uart
	uart_init("uart_0", 115200); //lui lo prende da una struct, ma è un valore definito
	//Inizializzaregestorepacchetti
	//inizializzarepacchetti
}
