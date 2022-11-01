#include "uart.h"

FIFO(64) uart_tx_fifo;
FIFO(64) uart_rx_fifo;

void uart_init(unsigned int speed)
{
  // устанавливаем скорость Baud Rate
    UBRRH=(char)(speed>>8);
    UBRRL=(char) speed;
    UCSRA=0x00;
  // Разрешение работы передатчика
    UCSRB=(1<<TXEN); 
  // Разрешение работы приемника
    UCSRB|=(1<<RXEN);
  // Разрешение прерываний по приему
    UCSRB|=(1<<RXCIE);
  // Установка формата посылки: 8 бит данных, 1 стоп-бит
    UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

ISR( USART_RXC_vect )
{
  unsigned char rxbyte = UDR;
  if(!FIFO_IS_FULL(uart_rx_fifo))
  {
    FIFO_PUSH(uart_rx_fifo,rxbyte);
  }
}

ISR(USART_UDRE_vect)
{
  if(FIFO_IS_EMPTY(uart_tx_fifo))
  {
    //если данных в fifo больше нет то запрещаем это прерывание
    UCSRB &= ~( 1 << UDRIE );
  }
  else
  {
    //иначе передаем следующий байт
    char txbyte = FIFO_FRONT( uart_tx_fifo );
    FIFO_POP( uart_tx_fifo );
    UDR = txbyte;
  }
}

int uart_putc(char c,FILE *file)
{
  int ret;
  cli(); //запрещаем прерывания
  if( !FIFO_IS_FULL( uart_tx_fifo ) ) {
    //если в буфере есть место, то добавляем туда байт
    FIFO_PUSH( uart_tx_fifo, c );
    //и разрешаем прерывание по освобождению передатчика
    UCSRB |= ( 1 << UDRIE );
    ret = 0;
  }
  else {
    ret = -1; //буфер переполнен
  }
  sei(); //разрешаем прерывания
  return ret;
}

int uart_getc(FILE* file)
{
  int ret;
  cli(); //запрещаем прерывания
  if( !FIFO_IS_EMPTY( uart_rx_fifo ) ) {
    //если в буфере есть данные, то извлекаем их
    ret = FIFO_FRONT( uart_rx_fifo );
    FIFO_POP( uart_rx_fifo );
  }
  else {
    ret = _FDEV_EOF; //данных нет
  }
  sei(); //разрешаем прерывания
  return ret;
}

