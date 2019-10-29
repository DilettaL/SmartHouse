#pragma once
#include <stdint.h>

struct UART;

struct UART* uart_init(const char* device, uint32_t );
void uart_putChar(struct UART*, uint8_t );
uint8_t uart_getChar(void);


