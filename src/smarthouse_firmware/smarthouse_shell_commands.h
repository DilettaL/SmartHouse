#pragma once

//definition of type of function
typedef int (*CmdFn)(char* response, char** args);


//Commands struct
typedef struct{
	//command string to compare with input
	const char* name;
//	int n_args;
	//Function of command
	CmdFn cmd_fn;
	//How to insert the command
	const char* help;
	} Command;

extern Command commands[];

