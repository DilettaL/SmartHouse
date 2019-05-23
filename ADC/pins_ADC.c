#include <avr/io.h>
#include "pins_ADC.h"
//libreria pin digitali
//Da rivedere mask
//Completare alcuni associati a pin 0
const Pin pins_adc[] =
  {
//Pin analogici (ADC)
//Ogni pin identifica un campo MUX di ADMUX MUXn + ->ADCSRB.MUX5
	//PinAVR 97 PinBoard 0
	{
		//MUX5:0 = 000000
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	}
	//PinAVR 96 PinBoard 1
	{
		//MUX5:0=000001
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);
	}
	//PinAVR 95 PinBoard 2
	{
		//MUX5:0=000010
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0);
	}
	//PinAVR 94 PinBoard 3
	{
		//MUX5:0=000011
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);
	}
	//PinAVR 93 PinBoard 4
	{
		//MUX5:0=000100
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0);
	}
	//PinAVR 92 PinBoard 5
	{
		//MUX5:0=000101
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0);
	}
	//PinAVR 91 PinBoard 6
	{
		//MUX5:0=000110
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0);
	}
	//PinAVR 90 PinBoard 7
	{
		//MUX5:0=000111
		.select_adc= (0<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	}
	//PinAVR 89 PinBoard 8
	{
		//MUX5:0=100000
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	}
	//PinAVR 88 PinBoard 9
	{
		//MUX5:0=100001
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);
	}
	//PinAVR 87 PinBoard 10
	{
		//MUX5:0=100010
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0);
	}
	//PinAVR 86 PinBoard 11
	{
		//MUX5:0=100011
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);
	}
	//PinAVR 85 PinBoard 12
	{
		//MUX5:0=100100
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0);
	}
	//PinAVR 84 PinBoard 13
	{
		//MUX5:0=100101
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0);
	}
	//PinAVR 83 PinBoard 14
	{
		//MUX5:0=100110
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0);
	}
	//PinAVR 82 PinBoard 15
	{
		//MUX5:0=100111
		.select_adc= (1<<MUX5)|(0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	}
};
