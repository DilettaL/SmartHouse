#ifdef __SMARTHOUSE_FUNCTIONS_H__
#define __SMARTHOUSE_FUNCTIONS_H__

#include <stdint.h>
#include "digio.h" //per Pindirection
//file da mettere in common
#include "smarthouse_avr_common.h"
//1)
PacketStatus Digital_Pin(const DigitalType type);
//(struct HBridge* bridge, const HBridgeType type, int8_t* pins);

//2)
typedef struct
{
	PinDirection dir;
	uint8_t value;
} PDigital;

#endif
