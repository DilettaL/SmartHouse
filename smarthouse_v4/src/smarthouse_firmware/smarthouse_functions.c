#include "smarthouse_functions.h"
#include "digio.h"
#include "adc.h"
#include "pwm.h"

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

void Dimmer(uint8_t pin, uint8_t intensity)
{	
	PWM_enable(pin, 1);
	PWM_setDutyCycle(pin, intensity);
}

void InputDigital(uint8_t pin)
{
	DigIO_setDirection(pin, Input);
	//DigIO_setValue(pin, 1);
	digital_status.inputs=DigIO_getValue(pin);
}

void Smarthouse_digital(void)
{
	switch (digital_config.set_digital)
	{
		case ledOff:
			LedOff(digital_config.pin_digital);
			break;
		case ledOn:
			LedOn(digital_config.pin_digital);
			break;
		case dimmer:
			Dimmer(digital_config.pin_digital, digital_config.intensity);
			digital_status.intensity=digital_config.intensity;
			break;
		case input_digital:
			InputDigital(digital_config.pin_digital);
			break;
		default:
			break;
	}
	digital_status.pin_digital=digital_config.pin_digital;
	digital_status.set_digital=digital_config.set_digital;
//	return &digital_status;
}

//analog function
void Smarthouse_analog(void)
{
	SetAdc(analog_config.pin_analog);
	analog_status.result=RunAdc(analog_config.samples);
}
