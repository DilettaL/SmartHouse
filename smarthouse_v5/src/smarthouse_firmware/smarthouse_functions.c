#include "smarthouse_functions.h"
#include "packet_handler.h"
#include "eeprom.h"
#include "digio.h"
#include "adc.h"
#include "pwm.h"

#define DIGITAL_PARAM_OFFSET      (32) 
#define ANALOG_PARAM_OFFSET      (DIGITAL_PARAM_OFFSET+sizeof(DigitalStatusPacket)*NUM_DIGITAL)


//digital functions
void LedOff(uint8_t pin)
{
	PWM_enable(pin, 0);
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 0);
}

void LedOn(uint8_t pin)
{
	PWM_enable(pin, 0);
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
	PWM_enable(pin, 0);
	DigIO_setDirection(pin, Input);
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

//eeprom functions
PacketStatus Smarthouse_paramEeprom()//uint8_t param_type, int8_t index)
{
	if(eeprom.action==0) //save
	{
		switch(eeprom.type_pin)
		{
		case 1: //digital
			EEPROM_write(DIGITAL_PARAM_OFFSET+eeprom.pin*sizeof(DigitalStatusPacket), &digital_status[eeprom.pin], sizeof(DigitalStatusPacket));
			break;
		case 0: //analog
			EEPROM_write(ANALOG_PARAM_OFFSET+eeprom.pin*sizeof(AnalogStatusPacket), &analog_status[eeprom.pin], sizeof(AnalogStatusPacket));
			break;
		default:
    			return GenericError;
  		}
	}
	else if(eeprom.action==1) //load
	{
		switch(eeprom.type_pin)
		{
		case 1://digital
			EEPROM_read(&digital_status[eeprom.pin], DIGITAL_PARAM_OFFSET+eeprom.pin*sizeof(DigitalStatusPacket), sizeof(DigitalStatusPacket));
			digital_config.pin_digital=eeprom.pin;
			digital_config.set_digital=digital_status[eeprom.pin].set_digital;
			digital_config.intensity=digital_status[eeprom.pin].intensity;
			Smarthouse_digital();
			break;
		case 0://analog
			EEPROM_read(&analog_status[eeprom.pin], ANALOG_PARAM_OFFSET+eeprom.pin*sizeof(AnalogStatusPacket), sizeof(AnalogStatusPacket));
			analog_config.pin_analog=eeprom.pin;
			analog_config.samples=analog_status[eeprom.pin].samples;
			Smarthouse_analog();
			break;
		default:
			return GenericError;
		}
	}
	return Success;
}

void Smarthouse_ParamInit(void)
{
	PacketType example;
	for(int i=0; i<NUM_DIGITAL; i++)
	{
		EEPROM_read(&example, DIGITAL_PARAM_OFFSET+i*sizeof(DigitalStatusPacket), sizeof(PacketType));
		if (example==DIGITAL_STATUS_PACKET_ID)	
		{
			EEPROM_read(&digital_status[i], DIGITAL_PARAM_OFFSET+i*sizeof(DigitalStatusPacket), sizeof(DigitalStatusPacket));
			digital_config.pin_digital=i;
			digital_config.set_digital=digital_status[i].set_digital;
			digital_config.intensity=digital_status[i].intensity;
			Smarthouse_digital();
		}
	}
}
