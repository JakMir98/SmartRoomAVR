#ifndef uart_h
#define uart_h                  

#include <avr/io.h>
#include <string.h>
/**************************************************************************************\
* Private definitions
\**************************************************************************************/
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (((FOSC / (BAUD * 16UL))) - 1) 

#define ADC_READ_CHAR 's'
#define RELAY1_CHAR '1'
#define RELAY2_CHAR '2'
#define RELAY3_CHAR '3'
#define RELAY4_CHAR '4'

/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief USART initialization
 */
void USART_Init(unsigned int ubrr);

/**
 * @brief Transmit character through USART
 */
void USART_Transmit(char data);

/**
 * @brief Receive character from USART
 */
char USART_Receive(void);

/**
 * @brief Send string through USART
 */
void sendString(char string[]);

#endif
