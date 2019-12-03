#pragma once
#include "smarthouse_host_globals.h"

typedef int (*CmdFn)(char* response, char** args);

typedef struct
{
	const char* name;
	CmdFn cmd_fn;
	const char* help;
} Command;

extern Command commands[];

