#include <avr/io.h>
#include "pins.h"
//libreria pin digitali
//Da rivedere mask
//Completare alcuni associati a pin 0
const Pin pins[] =
  {
//PinAVR 2 PinBoard 0
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=0,
      .tcc_register=0,
      .oc_register=0,
      .com_mask=0
    },
//PinAVR 3 PinBoard 1
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=1,
      .tcc_register=0,
      .oc_register=0,
      .com_mask=0
    },
//PinAVR 6 PinBoard 2
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=4,
      .tcc_register=&TCCR3A,
      .oc_register=&OCR3BL,
      .com_mask=(1<<COM3B0)|(1<<COM3B1)
    },
//PinAVR 7 PinBoard 3
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=5,
      .tcc_register=&TCCR3A,
      .oc_register=&OCR3CL,
      .com_mask=(1<<COM3C0)|(1<<COM3C1)
    },
//PinAVR 1 PinBoard 4
    {
      .in_register=&PING,
      .out_register=&PORTG,
      .dir_register=&DDRG,
      .bit=5,
      .tcc_register=&TCCR0A, 
      .oc_register=&OCR0B,
      .com_mask=(1<<COM0B0)|(1<<COM0B1)
    },
//PinAVR 5 PinBoard 5
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=3,
      .tcc_register=&TCCR3A,
      .oc_register=&OCR3AL,
      .com_mask=(1<<COM3A0)|(1<<COM3A1)
    },
//PinAVR 15 PinBoard 6
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=3,
      .tcc_register=&TCCR4A, 
      .oc_register=&OCR4AL,
      .com_mask=(1<<COM4A0)|(1<<COM4A1)
    },
//PinAVR 16 PinBoard 7
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=4,
      .tcc_register=&TCCR4A,
      .oc_register=&OCR4BL, 
      .com_mask=(1<<COM4B0)|(1<<COM4B1)
    },
//PinAVR 17 PinBoard 8
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=5,
      .tcc_register=&TCCR4A,
      .oc_register=&OCR4CL, 
      .com_mask=(1<<COM4C0)|(1<<COM4C1) 
    },
//PinAVR 18 PinBoard 9
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=6,
      .tcc_register=&TCCR2A,
      .oc_register=&OCR2B,
      .com_mask=(1<<COM2B0)|(1<<COM2B1)
    },
//PinAVR 23 PinBoard 10
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=4,
      .tcc_register=&TCCR2A,
      .oc_register=&OCR2A,
      .com_mask=(1<<COM2A0)|(1<<COM2A1)
    },
//PinAVR 24 PinBoard 11
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=5,
      .tcc_register=&TCCR1A,
      .oc_register=&OCR1AL,
      .com_mask=(1<<COM1A0)|(1<<COM1A1)
    },
//PinAVR 25 PinBoard 12
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=6,
      .tcc_register=&TCCR1A,
      .oc_register=&OCR1BL,
      .com_mask=(1<<COM1B0)|(1<<COM1B1)
    },
//PinAVR 26 PinBoard 13 OC0A/OC1C
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=7,
      .tcc_register=&TCCR1A,
      .oc_register=&OCR1CL,
      .com_mask=(1<<COM1C0)|(1<<COM1C1)
    }
};


//libreria pin digitali
//Da rivedere mask
//Completare alcuni associati a pin 0
const Pin_analog pins_analog[] =
  {
//Pin analogici (ADC)
//Ogni pin identifica un campo MUX di ADMUX MUXn + ->ADCSRB.MUX5
	//PinAVR 97 PinBoard 0
	{
		//MUX5:0 = 000000
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 96 PinBoard 1
	{
		//MUX5:0=000001
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 95 PinBoard 2
	{
		//MUX5:0=000010
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 94 PinBoard 3
	{
		//MUX5:0=000011
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 93 PinBoard 4
	{
		//MUX5:0=000100
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 92 PinBoard 5
	{
		//MUX5:0=000101
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 91 PinBoard 6
	{
		//MUX5:0=000110
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 90 PinBoard 7
	{
		//MUX5:0=000111
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(0<<MUX5)
	},
	//PinAVR 89 PinBoard 8
	{
		//MUX5:0=100000
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 88 PinBoard 9
	{
		//MUX5:0=100001
		.select_adc_mux=(0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 87 PinBoard 10
	{
		//MUX5:0=100010
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 86 PinBoard 11
	{
		//MUX5:0=100011
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 85 PinBoard 12
	{
		//MUX5:0=100100
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 84 PinBoard 13
	{
		//MUX5:0=100101
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 83 PinBoard 14
	{
		//MUX5:0=100110
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	},
	//PinAVR 82 PinBoard 15
	{
		//MUX5:0=100111
		.select_adc_mux= (0<<MUX4)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0),
		.select_adc_adcsrb=(1<<MUX5)
	}
};
