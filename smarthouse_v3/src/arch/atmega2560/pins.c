#include "pins.h"
#include "digio.h"
#include <avr/io.h>

// 2018-02-10: disabled pwm on pins 6,7,8. I need that timer to read the sonars
const Pin pins[] =
  {
    //0
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=0,
      .tcc_register=0,
      .oc_register=0,
      .com_mask=0
    },
    //1
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=1,
      .tcc_register=0,
      .oc_register=0,
      .com_mask=0
    },
    //2
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=4,
      .tcc_register=&TCCR3A,
      .oc_register=&OCR3BL,
      .com_mask=(1<<COM3B0)|(1<<COM3B1)
    },
    //3
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=5,
      .tcc_register=&TCCR3A,
      .oc_register=&OCR3CL,
      .com_mask=(1<<COM3C0)|(1<<COM3C1)
    },
    //4
    {
      .in_register=&PING,
      .out_register=&PORTG,
      .dir_register=&DDRG,
      .bit=5,
      .tcc_register=&TCCR0A, 
      .oc_register=&OCR0B,
      .com_mask=(1<<COM0B0)|(1<<COM0B1)
    },
    //5
    {
      .in_register=&PINE,
      .out_register=&PORTE,
      .dir_register=&DDRE,
      .bit=3,
      .tcc_register=&TCCR3A,
      .oc_register=&OCR3AL,
      .com_mask=(1<<COM3A0)|(1<<COM3A1)
    },
    //6
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=3,
      /* .tcc_register=&TCCR4A, */
      /* .oc_register=&OCR4AL, */
      /* .com_mask=(1<<COM4A0)|(1<<COM4A1) */
      .tcc_register=0,
      .oc_register=0,
      .com_mask=0
    },
    //7
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=4,
      /* .tcc_register=&TCCR4A, */
      /* .oc_register=&OCR4BL, */
      /* .com_mask=(1<<COM4B0)|(1<<COM4B1) */
      .tcc_register=0,
      .oc_register=0,
      .com_mask=0
    },
    //8
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=5,
      /* .tcc_register=&TCCR4A, */
      /* .oc_register=&OCR4CL, */
      /* .com_mask=(1<<COM4C0)|(1<<COM4C1) */
      .tcc_register=0,
      .oc_register=0,
      .com_mask=-0
    },
    //9
    {
      .in_register=&PINH,
      .out_register=&PORTH,
      .dir_register=&DDRH,
      .bit=6,
      .tcc_register=&TCCR2A,
      .oc_register=&OCR2B,
      .com_mask=(1<<COM2B0)|(1<<COM2B1)
    },
    //10
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=4,
      .tcc_register=&TCCR2A,
      .oc_register=&OCR2A,
      .com_mask=(1<<COM2A0)|(1<<COM2A1)
    },
    //11
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=5,
      .tcc_register=&TCCR1A,
      .oc_register=&OCR1AL,
      .com_mask=(1<<COM1A0)|(1<<COM1A1)
    },
    //12
    {
      .in_register=&PINB,
      .out_register=&PORTB,
      .dir_register=&DDRB,
      .bit=6,
      .tcc_register=&TCCR1A,
      .oc_register=&OCR1BL,
      .com_mask=(1<<COM1B0)|(1<<COM1B1)
    },
    //13
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
