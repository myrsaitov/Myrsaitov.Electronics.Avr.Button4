#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "fifo.h"

void uart_init(unsigned int speed);
int uart_putc(char c,FILE *file);
int uart_getc(FILE* file);
ISR(USART_RXC_vect);
ISR(USART_UDRE_vect);




















