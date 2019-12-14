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

uint8_t InputDigital(uint8_t pin)
{
	DigIO_setDirection(pin, Input);
	//DigIO_setValue(pin, 1);
	uint8_t value=DigIO_getValue(pin);
	return value;
}

void Smarthouse_digital(void)
{
	uint8_t pint=digital_config.pin_digital;
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
			digital_status[pint].intensity=digital_config.intensity;
			break;
		case input_digital:
			digital_status[pint].inputs=InputDigital(digital_config.pin_digital);
			break;
		default:
			break;
	}
	digital_status[pint].pin_digital=digital_config.pin_digital;
	digital_status[pint].set_digital=digital_config.set_digital;
//	return &digital_status;
}

//analog function
void Smarthouse_analog(void)
{
	uint16_t* temp;
	uint8_t pint=analog_config.pin_analog;
	SetAdc(analog_config.pin_analog);
	analog_status[pint].pin_analog=analog_config.pin_analog;
	analog_status[pint].samples=analog_config.samples;
	
	temp = RunAdc(analog_config.samples);
	for (int k = 0; k < analog_config.samples ; k++)
		analog_status[pint].result[k]=*(temp+k);
}
