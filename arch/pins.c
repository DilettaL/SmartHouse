#include <avr/io.h>
#include "pins.h"
//libreria pin digitali
//Da rivedere mask
//Completare alcuni associati a pin 0
const Pin pins[] =
  {
//Pin digitali i/o
	//PinAVR 2 PinBoard 0
	{
	      .in_register=&PINE,
	      .out_register=&PORTE,
	      .dir_register=&DDRE,
	      .bit=0,
		//PWM
		.tcc_register=0, 		//TCCRnX
		.oc_register_high=0,	//OCRnXH
		.oc_register_low=0,	//OCRnXL
		.com_mask=0	  		//bit in others registers
	
        },
   	//PinAVR 3 PinBoard 1
 	{
	      .in_register=&PINE,
	      .out_register=&PORTE,
	      .dir_register=&DDRE,
	      .bit=1,
		//PWM
		.tcc_register=0, 		//TCCRnX
		.oc_register_high=0,	//OCRnXH
		.oc_register_low=0,	//OCRnXL
		.com_mask=0	  		//bit in others registers
	
	},
	
	//PinAVR 6 PinBoard 2
	{
		.in_register=&PINE,
		.out_register=&PORTE,
		.dir_register=&DDRE,
		.bit=4,
		//PWM
		.tcc_register=&TCCR3B, 		//TCCRnX
		.oc_register_high=&OCR3BH,	//OCRnXH
		.oc_register_low=&OCR3BL,	//OCRnXL
		.com_mask=(1<<COM3B0)|(1<<COM3B1)	  		//bit in others registers
	},
	//PinAVR 7 PinBoard 3
	{
		.in_register=&PINE,
		.out_register=&PORTE,
		.dir_register=&DDRE,
		.bit=5,
		//PWM
		.tcc_register=&TCCR3C,
		.oc_register_high=&OCR3CH,	//OCRnXH
		.oc_register_low=&OCR3CL,	//OCRnXL
		.com_mask=(1<<COM3C0)|(1<<COM3C1)	
	},
	//PinAVR 1 PinBoard 4
	{
		.in_register=&PING,
		.out_register=&PORTG,
		.dir_register=&DDRG,
		.bit=5,
		//PWM
		.tcc_register=&TCCR0B,//&TCRR0B
		.oc_register_high=0,
		.oc_register_low=&OCR0B, //&OCR0B
		.com_mask=(1<<COM0B0)|(1<<COM0B1)	//settano TCRR0A
	},
	//PinAVR 5 PinBoard 5
	{
		.in_register=&PINE,
		.out_register=&PORTE,
		.dir_register=&DDRE,
		.bit=3,
		//PWM
		.tcc_register=&TCCR3A,
		.oc_register_high=&OCR3AH,	//OCRnXH
		.oc_register_low=&OCR3AL,	//OCRnXL
		.com_mask=(1<<COM3A0)|(1<<COM3A1)	
	},
	//PinAVR 15 PinBoard 6
	{
		.in_register=&PINH,
		.out_register=&PORTH,
		.dir_register=&DDRH,
		.bit=3,
		//PWM
		.tcc_register=&TCCR4A,
		.oc_register_high=&OCR4AH,	//OCRnXH
		.oc_register_low=&OCR4AL,	//OCRnXL
		.com_mask=(1<<COM4A0)|(1<<COM4A1)
	},
	//PinAVR 16 PinBoard 7
	{
		.in_register=&PINH,
		.out_register=&PORTH,
		.dir_register=&DDRH,
		.bit=4,
		//PWM
		.tcc_register=&TCCR4B,
		.oc_register_high=&OCR4BH,	//OCRnXH
		.oc_register_low=&OCR4BL,	//OCRnXL
		.com_mask=(1<<COM4B0)|(1<<COM4B1)
	},
	//PinAVR 17 PinBoard 8
	{
		.in_register=&PINH,
		.out_register=&PORTH,
		.dir_register=&DDRH,
		.bit=5,
		//PWM
		.tcc_register=&TCCR4C,
		.oc_register_high=&OCR4CH,	//OCRnXH
		.oc_register_low=&OCR4CL,	//OCRnXL
		.com_mask=(1<<COM4C0)|(1<<COM4C1)
	},
	//PinAVR 18 PinBoard 9
	{
		.in_register=&PINH,
		.out_register=&PORTH,
		.dir_register=&DDRH,
		.bit=6,
		//PWM
		.tcc_register=&TCCR2B,
		.oc_register_high=0,	//OCRnXH
		.oc_register_low=&OCR2B,	//OCRnXL
		.com_mask=(1<<COM2B0)|(1<<COM2B1)
	},
	//PinAVR 23 PinBoard 10
	{
		.in_register=&PINB,
		.out_register=&PORTB,
		.dir_register=&DDRB,
		.bit=4,
		//PWM
		.tcc_register=&TCCR2A,
		.oc_register_high=0,	//OCRnXH
		.oc_register_low=&OCR2A,	//OCRnXL
		.com_mask=(1<<COM2A0)|(1<<COM2A1)
	},
	//PinAVR 24 PinBoard 11
	{
		.in_register=&PINB,
		.out_register=&PORTB,
		.dir_register=&DDRB,
		.bit=5,
		//PWM
		.tcc_register=&TCCR1A,
		.oc_register_high=&OCR1AH,	//OCRnXH
		.oc_register_low=&OCR1AL,	//OCRnXL
		.com_mask=(1<<COM1A0)|(1<<COM1A1)
	},
	//PinAVR 25 PinBoard 12
	{
		.in_register=&PINB,
		.out_register=&PORTB,
		.dir_register=&DDRB,
		.bit=6,
		//PWM
		.tcc_register=&TCCR1B,
		.oc_register_high=&OCR1BH,	//OCRnXH
		.oc_register_low=&OCR1BL,	//OCRnXL
		.com_mask=(1<<COM1B0)|(1<<COM1B1)
	},
	//PinAVR 26 PinBoard 13 OC0A/OC1C
	{
		.in_register=&PINB,
		.out_register=&PORTB,
		.dir_register=&DDRB,
		.bit=7,
		//PWM
		.tcc_register=&TCCR1C,
		.oc_register_high=&OCR1CH,	//OCRnXH
		.oc_register_low=&OCR1CL,	//OCRnXL
		.com_mask=(1<<COM1C0)|(1<<COM1C1)
	}
};
