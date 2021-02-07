#include "/Projekty/AVR projects/SmartRoom/SmartRoom/inc/timer.h"

void OVERFLOW_TIMER_Init()
{
	// TIMER0 - 8 bit  
	TCCR0A = 0b00000000; // normal port operation
	TCCR0B = (1 << CS02) | (1 << CS00); // 0b00000101 clock / 1024
	TIMSK0 = (1 << TOIE0); // 0b00000001 enable Timer/Counter 0 Overflow Interrupt

	// TIMER1 - 16 bit
	TCCR1A = 0b00000000; // normal port operation
	TCCR1B = (1 << CS12) | (1 << CS10); //0b00000010 clock / 1024
	TCCR1C = 0b00000000;
	TIMSK1 = (1 << TOIE1); // 0b00000001  enable Timer/Counter 1 Overflow Interrupt
}

void COMPARE_TIMER_Init()
{
	//F_CPU=16MHz: Clock time period = 1000ms / 16000000Hz = 0.0000625ms
	//Timer count = (Required Delay / Clock Time Period)-1 = (1000ms / 0.0000625ms) = 15999999
	//The clock has already ticked 15999999 times to give a delay of 1s!
	// tick every 1 sec
	
	TCCR1B |= (1 << WGM12)|(1 << CS12); // set up timer with prescaler = 256 and CTC mode
	TCNT1 = 0; // initialize counter
	OCR1A = 62500; // initialize compare value
	TIMSK1 |= (1 << OCIE1A); // enable compare interrupt
	
}

//TIMER0 overflow interrupt
/* 
ISR(TIMER0_OVF_vect) 
{
	//testLedState ^= 1;
}

//TIMER1 overflow interrupt
ISR(TIMER1_OVF_vect) 
{
	testLedState ^= 1;
}

// TIMER1 compare interrupt
ISR (TIMER1_COMPA_vect)
{
	testLedState ^= 1;
}
*/
