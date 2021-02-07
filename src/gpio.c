#include "/Projekty/AVR projects/SmartRoom/SmartRoom/inc/gpio.h"

void GPIO_Init(void)
{
	SET_PIN_AS_OUTPUT(PORTB, PUMP_PIN);
	SET_PIN_AS_OUTPUT(PORTB, RELAY4_PIN);
	
	SET_PIN_AS_OUTPUT(PORTD, TEST_LED_PIN);
	SET_PIN_AS_OUTPUT(PORTD, RELAY1_PIN);
	SET_PIN_AS_OUTPUT(PORTD, RELAY2_PIN);
	SET_PIN_AS_OUTPUT(PORTD, RELAY3_PIN);
	
	// setup INT0 for UART INTERRUPT
	SET_PIN_AS_INPUT_PULLUP(DDRD, PORTD, 2);
	
	// setup interrupt on pin 3 PORTB (PCINT2)
	SET_PIN_AS_INPUT_PULLUP(DDRB, PORTB, PUSH_BUTTON_PIN);
	PCICR = (1 << PCIE0);  //enable pin change interrupt on pins PCINT7 through PCINT0
	PCMSK0 = (1 << PCINT2);
	
	// INT1 interrupt setup
	//PUSH_BUTTON_PIN = 3 on PORTD 
	//SET_PIN_AS_INPUT_PULLUP(DDRD, PORTD, PUSH_BUTTON_PIN);
	//EIMSK |= (1 << INT1); // INT1 interrupt 
	//EICRA |= (1 << ISC10) | (0 << ISC11); // falling edge of INT1 
	
	RESET_BIT(PORTB, PUMP_PIN);
	SET_BIT(PORTD, RELAY1_PIN);
	SET_BIT(PORTD, RELAY2_PIN);
	SET_BIT(PORTD, RELAY3_PIN);
	SET_BIT(PORTB, RELAY4_PIN);
}

//INT1 interrupt
/* 
ISR(INT1_vect) 
{
	testLedState ^= 1;
}
*/
