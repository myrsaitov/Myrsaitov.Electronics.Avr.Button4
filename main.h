#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <util/crc16.h>
#include "uart.h"

#define SENSOR_NAME 32

#define F_CPU 7372800UL
//#define BAUD 9600
#define BAUD 57600
//#define BAUD 115200
#define UBRR_VAL F_CPU/16/BAUD-1

#define TX_EN_DDR        DDRD
#define TX_EN_PORT       PORTD
#define TX_EN_PIN        PD3
#define TX_EN_READ_PORT  PIND
#define TX_EN_PINCONFIG  TX_EN_DDR |= (1 << TX_EN_PIN)
#define TX_EN_ON         TX_EN_PORT |= (1 << TX_EN_PIN);_delay_ms(1)
#define TX_EN_OFF        TX_EN_PORT &= ~(1 << TX_EN_PIN)

#define BUTTON_0_DDR DDRC
#define BUTTON_1_DDR DDRC
#define BUTTON_2_DDR DDRC
#define BUTTON_3_DDR DDRC

#define BUTTON_0_PORT PORTA
#define BUTTON_1_PORT PORTA
#define BUTTON_2_PORT PORTC
#define BUTTON_3_PORT PORTC

#define BUTTON_0_READ_PORT PINA
#define BUTTON_1_READ_PORT PINA
#define BUTTON_2_READ_PORT PINC
#define BUTTON_3_READ_PORT PINC

#define BUTTON_0_PIN PA1
#define BUTTON_1_PIN PA4
#define BUTTON_2_PIN PC7
#define BUTTON_3_PIN PC6

#define BUTTON_0_PINCONFIG BUTTON_0_DDR &= ~(1 << BUTTON_0_PIN)
#define BUTTON_1_PINCONFIG BUTTON_1_DDR &= ~(1 << BUTTON_1_PIN)
#define BUTTON_2_PINCONFIG BUTTON_2_DDR &= ~(1 << BUTTON_2_PIN)
#define BUTTON_3_PINCONFIG BUTTON_3_DDR &= ~(1 << BUTTON_3_PIN)

#define BUTTON_0_PULLUP_EN BUTTON_0_PORT |= (1 << BUTTON_0_PIN)
#define BUTTON_1_PULLUP_EN BUTTON_1_PORT |= (1 << BUTTON_1_PIN)
#define BUTTON_2_PULLUP_EN BUTTON_2_PORT |= (1 << BUTTON_2_PIN)
#define BUTTON_3_PULLUP_EN BUTTON_3_PORT |= (1 << BUTTON_3_PIN)

#define LED_0_DDR DDRA
#define LED_1_DDR DDRA
#define LED_2_DDR DDRA
#define LED_3_DDR DDRA

#define LED_0_PORT PORTA
#define LED_1_PORT PORTA
#define LED_2_PORT PORTA
#define LED_3_PORT PORTA

#define LED_0_PIN PA0
#define LED_1_PIN PA3
#define LED_2_PIN PA6
#define LED_3_PIN PA7

#define LED_0_PINCONFIG LED_0_DDR |= (1 << LED_0_PIN)
#define LED_1_PINCONFIG LED_1_DDR |= (1 << LED_1_PIN) 
#define LED_2_PINCONFIG LED_2_DDR |= (1 << LED_2_PIN)
#define LED_3_PINCONFIG LED_3_DDR |= (1 << LED_3_PIN)

#define LED_0_ON  LED_0_PORT |= (1 << LED_0_PIN)
#define LED_0_OFF LED_0_PORT &= ~(1 << LED_0_PIN)
#define LED_1_ON  LED_1_PORT |= (1 << LED_1_PIN)
#define LED_1_OFF LED_1_PORT &= ~(1 << LED_1_PIN)
#define LED_2_ON  LED_2_PORT |= (1 << LED_2_PIN)
#define LED_2_OFF LED_2_PORT &= ~(1 << LED_2_PIN)
#define LED_3_ON  LED_3_PORT |= (1 << LED_3_PIN)
#define LED_3_OFF LED_3_PORT &= ~(1 << LED_3_PIN)

#define BUTTON_0_NOT_PRESSED ((1 << BUTTON_0_PIN) & BUTTON_0_READ_PORT)
#define BUTTON_1_NOT_PRESSED ((1 << BUTTON_1_PIN) & BUTTON_1_READ_PORT)
#define BUTTON_2_NOT_PRESSED ((1 << BUTTON_2_PIN) & BUTTON_2_READ_PORT)
#define BUTTON_3_NOT_PRESSED ((1 << BUTTON_3_PIN) & BUTTON_3_READ_PORT)

#define INT0_PORT PORTD
#define INT0_DDR DDRD
#define INT0_PIN PD2
#define INT0_INTERNAL_PULLUP_ON   INT0_PORT |= (1<<INT0_PIN) 
#define INT0_PIN_CONF_INPUT       INT0_DDR &= ~(1<<INT0_PIN)
#define INT0_TYPE_LOW_LEVEL       MCUCR |= (0<<ISC01)|(0<<ISC00)
#define INT0_TYPE_LEVEL_CHANGE    MCUCR |= (0<<ISC01)|(1<<ISC00)
#define INT0_TYPE_FALLING_FRONT   MCUCR |= (1<<ISC01)|(0<<ISC00)
#define INT0_TYPE_RISING_FRONT    MCUCR |= (1<<ISC01)|(1<<ISC00)
#define INT0_ENABLE               GICR |= (1<<INT0)

#define GLOBAL_INTERRUPTS_ENABLE sei()

void main(void);
