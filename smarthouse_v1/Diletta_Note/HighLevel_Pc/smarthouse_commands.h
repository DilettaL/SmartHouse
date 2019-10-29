#pragma once

//1a)definizione della struct che permette di implementare i comandi
typedef struct 
{
	const char* name;
//    int n_args;
	CmdFn cmd_fn;
	const char* help;
} Command;

//1b)Si definisce la struct da utilizzare esternamente
extern Command commands[];

//1c) è la definizione generica del puntatore a funzione della struct
typedef int (*CmdFn)(char* response, char** args);
