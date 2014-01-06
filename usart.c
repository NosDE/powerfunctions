#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <avr/io.h>

#include "usart.h"
#include "pfparser.h"


//----------------------------------------------------------------------------
//Init serielle Schnittstelle
void usart_init(unsigned long baudrate)
{
	
	unsigned int ubrr = F_CPU/16/baudrate-1;

	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, N, 1stop bit */
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}


void usart_write_char(uint8_t c)
{
	//Warten solange bis Zeichen gesendet wurde
	while(!(UCSR0A & (1<<UDRE0)));
	//Ausgabe des Zeichens
	UDR0 = c;
	return;
}


//----------------------------------------------------------------------------
//Empfang eines Zeichens
ISR (USART_RX_vect)
{
    //unsigned char c;
	uint8_t c;
    c = (UDR0);
    pf_parser(c);
	//usart_write_char(c);
	return;
}
