#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "smarthouse_shell_commands.h"

int quitFn(void)
{
	run=0;
	return 0;
}

Command commands[] =
{
	{
		.name = "quit",
		//.n_args = 0,
//Ho capito perché il tipo di questa funzione è CmdFn, però per ora non so se servirà in futuro
		.cmd_fn=quitFn,
		.help="usage: quit",
	}
};
