#pragma once
#include "smarthouse_host_globals.h"

typedef int (*CmdFn)(void);//char* response, char** args);

typedef struct
{
	const char* name;
	CmdFn cmd_fn;
	const char* help;
} Command;

extern Command commands[];

Command* findCommand(const char* name);

int executeCommand(const char* line_);
