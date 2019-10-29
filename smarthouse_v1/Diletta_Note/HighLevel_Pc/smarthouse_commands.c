#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "smarthouse_shell_commands.h"

//1d) riporto nella struct le funzioni precedentemente definite in pc.txt
Command commands[] = 
{
	//1e) implemento la funzione di uscita
	{
		.name = "quit",
		//.n_args = 0,
		.cmd_fn=quitFn,
		.help="usage: quit",
 	},
	//1f) implemento la funzione con cui si definisce il nome del dispositivo
	{
		.name = "set_name",
		//.n_args = 0,
		.cmd_fn=setName,
		.help="usage: set_name example_name_device",
 	}
};

//1e)
int quitFn(char* r, char** args)
{
	//run=0;
	return 0;
}


