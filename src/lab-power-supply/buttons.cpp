#include "Arduino.h";

void buttons_setup(void)
{
	// set pin D2 and D3 as input (they are on port D)
	DDRD &= ~(1 << PD2 | 1 << PD3);
	// enable internal pull-up resistors
	PORTD |= (1 << PD2 | 1 << PD3);
}