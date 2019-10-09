#include "uart.h"
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

struct UART* uart;

void printString(char* s){
  int l=strlen(s);
  for(int i=0; i<l; ++i, ++s)
    UART_putChar(uart, (uint8_t) *s);
}


int main(void){
  uart=UART_init("uart_0",9600);
  while(1) {
    char tx_message[300];
    char rx_message[300];
    rx_message[0]=0;
    int size=0;
    while(1){
      sprintf(tx_message, "buffer rx: %d msg: [%s]\n",
	      UART_rxBufferFull(uart),
	      rx_message);
      printString(tx_message);
      uint8_t c= UART_getChar(uart);
      rx_message[size]=c;
      ++size;
      rx_message[size]=0;
      if (c == 0xFF ||c == '\n' || c=='\r' || c==0) {
        break;
      }
      
      _delay_ms(10);
    }
  }
}
