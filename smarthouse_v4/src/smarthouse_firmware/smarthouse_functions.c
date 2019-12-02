#include "smarthouse_functions.h"
#include "digio.h"

//digital functions
void LedOff(uint8_t pin)
{
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 0);
}

void LedOn(uint8_t pin)
{
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 1);
}

void Smarthouse_digital(DigitalConfigPacket *packet)
{
	switch (packet->set_digital)
	{
		case ledOff:
			LedOff(packet->pin_digital);
			break;
		case ledOn:
			LedOn(packet->pin_digital);
			break;
		case dimmer:
			LedOff(packet->pin_digital);
			break;
		case input_digital:
			LedOff(packet->pin_digital);
			break;
		default:
			break;
	}
	digital_status.pin_digital=digital_config.pin_digital;
	digital_status.set_digital=digital_config.set_digital;
//	return &digital_status;
}
