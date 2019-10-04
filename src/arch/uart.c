#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define UART_BUFFER_SIZE 256

typedef struct UART {
  int tx_buffer[UART_BUFFER_SIZE];
  volatile uint8_t tx_start;
  volatile uint8_t tx_end;
  volatile uint8_t tx_size;

  int rx_buffer[UART_BUFFER_SIZE];
  volatile uint8_t rx_start;
  volatile uint8_t rx_end;
  volatile uint8_t rx_size;
  
  int uart_num; // hardware uart;
}UART;

static UART uart_0; //Volendo creare un file con struct tipo pins per le uart

void SetBaud(uint32_t baud)
{
	//non c'è altro modo per settare la uart in quanto serve frequency oscillator interna non c'è nel datasheet dovrei definirla con defin
	//Problema: come setto con define? Va bene così?
	#define BAUD 115200
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
}

struct UART* uart_init(const char* device __attribute__((unused)), uint32_t baud)
{
	//Initialization Uart_0
	UART* uart=&uart_0;
  	uart->uart_num=0;
	uart->tx_start=0;
	uart->tx_end=0;
	uart->tx_size=0;
	uart->rx_start=0;
	uart->rx_end=0;
	uart->rx_size=0;

/*The initialization setting the baud rate, setting frame format and enabling the Transmitter or the Receiver.For interrupt driven USART operation, the Global Interrupt Flag should be cleared (and interrupts globally
disabled) when doing the initialization*/
	//La modalità si sceglie con UCSRnC.USMEL
	//Asynchronous Normal Mode:
	//The data is transmitted and received bit by bit without clock pulses by the predefined baud rate set by the UBBR register.
	//Asynchronous Double Speed Mod
	//The data transferred at double the baud rate is set by the UBBR register and set U2X bits in the UCSRA register.
	//Synchronous Mode
	//Transmitting and receiving the data with respect to clock pulse is set UMSEL=1 in the UCSRC register.	
	//Si sceglie la modalità Asynchronous Double Speed Mode
	
	//Asynchronous Mode
	//UCSRnC.UMSEL1 e UMSEL0 =0 (già a 0)
	//Double Speed Mode
	#ifdef USE_2X
  	UCSR0A |= (1<<U2X0);
	#endif
	SetBaud(baud);
/*The frame format used by the USART is set by the UCSZn2:0, UPMn1:0 and USBSn bits in UCSRnB and UCS-RnC. The Receiver and Transmitter use the same setting.*/
	//No parity Bit and 1 stop bit
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //8bit
	sei();
	return uart;
}

void uart_putChar(struct UART* uart, uint8_t c)
{
	while ( !(UCSR0A & (1<<UDRE0)) );	//	(UCSR0A.UDRE0 != 1 ); //forse non giusto così
	UDR0=c;	
	UCSR0B |= (1<<UDRIE0); //enable transmit interrupt
}

uint8_t uart_getChar(void)
{
	while ( !(UCSR0A & (1<<RXC0)) );	//(UCSRA.RXC0!=1);// forse è sbagliato conviene metterlo così!(UCSR0A & (1<<RXC0)) );
	return UDR0;
}
