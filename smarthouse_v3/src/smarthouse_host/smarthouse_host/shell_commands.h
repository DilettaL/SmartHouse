#pragma once
#include "shell_globals.h"

typedef int (*CmdFn)(void);

typedef struct 
{
	const char* name;
	CmdFn cmd_fn;
	const char* help;
} Command;
extern Command commands[];

extern const int num_commands;

Command* findCommand(const char* name);

int executeCommand(const char* line_);

