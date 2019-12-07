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
			LedOff(digital_config[index].header.index);
			break;
		case ledOn:
			LedOn(digital_config[index].header.index);
			break;
		case dimmer:
			Dimmer(digital_config[index].header.index, digital_config[index].intensity);
			digital_status.intensity=digital_config[index].intensity;
			break;
		case input_digital:
			InputDigital(digital_config[index].header.index);
			break;
		default:
			break;
	}
	digital_status.pin_digital=digital_config[index].header.index
	digital_status.set_digital=digital_config[index].set_digital;
//	return &digital_status;
}

//analog function
void Smarthouse_analog(void)
{
	uint16_t* temp;
	SetAdc(analog_config.pin_analog);
	analog_status.pin_analog=analog_config.pin_analog;
	analog_status.samples=analog_config.samples;
	
	temp = RunAdc(analog_config.samples);
	for (int k = 0; k < analog_config.samples ; k++)
		analog_status.result[k]=*(temp+k);
}
