/*
 * SmartRoom.c
 *
 * Created: 05.02.2021 17:34:15
 * Author : Jakub Mirota
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "inc/gpio.h"
#include "inc/uart.h"
#include "inc/adc.h"
#include <stdio.h>

/**************************************************************************************\
* Private enums
\**************************************************************************************/
typedef enum {
	START,
	SLEEP,
	READ_ADC,
	RELAY_CONTROL,
	PUMP_WATER
} State;

/**************************************************************************************\
* Private variables
\**************************************************************************************/
volatile char received;
volatile int temperature_adc;
volatile int humidity_adc;
volatile State state = START;
volatile uint8_t relays[] = {0,0,0,0};
	
/**************************************************************************************\
* Private prototypes
\**************************************************************************************/
void avrRead(uint8_t);
void relayHandle();
void goToSleep();


ISR(USART_RX_vect)
{
	received = USART_Receive();
	switch(received)
	{
		case RELAY1_CHAR:
			relays[0] ^= 1;
			state = RELAY_CONTROL;
			break;
		case RELAY2_CHAR:
			relays[1] ^= 1;
			state = RELAY_CONTROL;
			break;
		case RELAY3_CHAR:
			relays[2] ^= 1;
			state = RELAY_CONTROL;
			break;
		case RELAY4_CHAR:
			relays[3] ^= 1;
			state = RELAY_CONTROL;
			break;
		case ADC_READ_CHAR:
			state = READ_ADC;
			break;
	}
}

/**************************************************************************************\
* Program start
\**************************************************************************************/
int main(void)
{
	USART_Init(MYUBRR);
	GPIO_Init();
	ADC_Init();
	sei();
	
	state = SLEEP;
	sendString("Initialization completed\r");
	
    while (1) 
    {
		switch(state)
		{
			case READ_ADC:
				avrRead(HUMIDITY_SENSOR_PIN);
				avrRead(TEMPERATURE_SENSOR_PIN);
				state = SLEEP;
				break;
			case RELAY_CONTROL:
				relayHandle();
				state = SLEEP;
				break;
			default:
			case SLEEP:
				// go to sleep wait for interrupt 
				//SET_BIT(PORTB, LED_PIN);
				//RESET_BIT(PORTB, LED_PIN);
				break;
		}
    }
}

void avrRead(uint8_t channel)
{
	uint16_t adcVal = ADC_AverageRead(channel);
	char intAsStr[10];
	if(channel == HUMIDITY_SENSOR_PIN )
	{
		sendString("Humidity sensor: ");
		sprintf( intAsStr, "%i", adcVal );
	}
	else if (channel == TEMPERATURE_SENSOR_PIN)
	{
		sendString("Temperature sensor: ");
		int temperatura = ((adcVal * 5.0) / 1024.0) * 100;
		sprintf( intAsStr,"%i", temperatura );
	}
	sendString(intAsStr);
	USART_Transmit('\r');
	_delay_ms(10);
}

void relayHandle()
{
	relays[0] == 0 ? SET_BIT(PORTD, RELAY1_PIN) : RESET_BIT(PORTD, RELAY1_PIN);
	relays[1] == 1 ? SET_BIT(PORTD, RELAY2_PIN) : RESET_BIT(PORTD, RELAY2_PIN);
	relays[2] == 1 ? SET_BIT(PORTD, RELAY2_PIN) : RESET_BIT(PORTD, RELAY3_PIN);
	relays[3] == 1 ? SET_BIT(PORTB, RELAY4_PIN) : RESET_BIT(PORTB, RELAY4_PIN);
}

void goToSleep()
{
	/*
	// clear various "reset" flags
	MCUSR = 0;
	// allow changes, disable reset, enable Watchdog interrupt
	WDTCSR = bit (WDCE) | bit (WDE);
	// set interval (see datasheet p55)
	WDTCSR = bit (WDIE) | bit (WDP2) | bit (WDP1);    // 128K cycles = approximativly 1 second
	wdt_reset();  // start watchdog timer
	set_sleep_mode (SLEEP_MODE_PWR_DOWN); // prepare for powerdown
	sleep_enable();
	sleep_cpu ();   // power down !
	*/
}


