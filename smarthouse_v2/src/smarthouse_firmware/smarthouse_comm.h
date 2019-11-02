#pragma once
//initializes the communication
// opens the uart
// initializes the packet handler
// registers all packets and the corresponding handlers
void Smarthouse_commInit(void);

//flushes the input buffers
//calls the deferred actions
//initiates the transmission in the output buffers
void Smarthouse_commHandle(void);
