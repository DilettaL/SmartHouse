#include <stdio.h>
#include <stdint.h>
//#include <util/atomic.h>
#include <string.h>
#define UART_BUFFER_SIZE 256


#define BUFFER_PUT(_IDX, _BSIZE_MAX)	\
  ++_IDX ## _end;					\
  if (_IDX ## _end>=_BSIZE_MAX)				\
    _IDX ## _end=0;					\
  ++_IDX ## _size;



struct UART* UART_init(const char* device __attribute__((unused))) {
  UART* uart=&uart_0;
  uart->uart_num=0;

  uart->tx_start=0;
  uart->tx_end=0;
  uart->tx_size=0;
  uart->rx_start=0;
  uart->rx_end=0;
  uart->rx_size=0;
 
  return &uart_0;
}

void UART_putChar(struct UART* uart, uint8_t c) {
  // loops until there is some space in the buffer
  while (uart->tx_size>=UART_BUFFER_SIZE);
  
    uart->tx_buffer[uart->tx_end]=c;
    BUFFER_PUT(uart->tx, UART_BUFFER_SIZE);
  
}



int main (){
typedef struct UART {
  int tx_buffer[UART_BUFFER_SIZE];
  volatile uint8_t tx_start;
  volatile uint8_t tx_end;
  volatile uint8_t tx_size;

  int rx_buffer[UART_BUFFER_SIZE];
  volatile uint8_t rx_start;
  volatile uint8_t rx_end;
  volatile uint8_t rx_size;
  
  int baud;
  int uart_num; // hardware uart;
} UART;

static UART uart_0;
	UART_init();
uint8_t l = 8;
	printf ("%d %u %u %u %d %u %u %u\n", tx_buffer[UART_BUFFER_SIZE], tx_start, tx_end, tx_size, rx_buffer[UART_BUFFER_SIZE], rx_start, tx_end, rx_size);
	UART_putChar(uart_0, l);


printf ("%d %u %u %u %d %u %u %u\n", tx_buffer[UART_BUFFER_SIZE], tx_start, tx_end, tx_size, rx_buffer[UART_BUFFER_SIZE], rx_start, tx_end, rx_size);

return 0;
}
