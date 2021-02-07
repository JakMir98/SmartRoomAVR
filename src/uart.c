#include "/Projekty/AVR projects/SmartRoom/SmartRoom/inc/uart.h"

void USART_Init(unsigned int ubrr)
{
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	//Enable receiver and transmitter 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  
	
	UCSR0B |= ( 1 << RXCIE0);
}

void USART_Transmit(char data)
{
	// Wait for empty transmit buffer 
	while (!(UCSR0A & (1<<UDRE0))) ;
	// Put data into buffer, sends the data 
	UDR0 = data;
}

char USART_Receive(void)
{
	// Wait for data to be received 
	while (!(UCSR0A & (1<<RXC0)));
	
	// Get and return received data from buffer 
	return UDR0;
}

void sendString(char string[])
{
	for (int i=0; i < strlen(string); i++)
		USART_Transmit(string[i]);
}
