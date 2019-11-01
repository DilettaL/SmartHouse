#include "smarthouse_pin.h"
#include "smarthouse_globals.h"

PacketStatus Smarthouse_pinInit(void)
{
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		//memset devo vedere a cosa serve questa funzione
		
	}
	for(i=0; i<ANALOG_MAX; i++)
	{

	}
	return Success;
}
