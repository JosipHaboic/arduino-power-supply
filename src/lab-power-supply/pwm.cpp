#include "Arduino.h"
#include "stdint.h"

const uint8_t DUTY_CYCLE_MIN = 0;
const uint8_t DUTY_CYCLE_MAX = 255;

void pwm_setup(void)
{
	// Output on digital port 5 and 6
	DDRD |= (1 << DDD6) | (1 << DDD5);
	// These bits control the output compare pin(OC0A) behavior and  pin (OC0B) behavior
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);

	// WGM01:0: Waveform Generation Mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00);

	// Set initial value to  output compare registers, this is the duty cycle value 8bit
	OCR0A = 0;
	OCR0B = 0;
	// TIMSK0 &= (1 << OCIE0A | 1 << TOIE0);
}

void pwm_start(void)
{
	// 62500Hz
	TCCR0B = TCCR0B & (0b11111000 | 0b00000001);
}

void pwm_set_duty_cycle(uint8_t pin, uint8_t duty_cycle)
{
	if (pin == 6) {
		OCR0A = duty_cycle;
		return;
	}
	if (pin == 5) {
		OCR0B = duty_cycle;
		return;
	}
}

void decrease_pwm(uint8_t pin)
{
	uint8_t register_value;

	if (pin == 6) {
		// read in value from Output Compare Register A
		register_value = OCR0A;
		// dont go bellow zero
		if (register_value == DUTY_CYCLE_MIN)
		{
			return;
		}
		OCR0A = register_value - 1;
		return;
	}

	if (pin == 5) {
		register_value = OCR0B;
		if (register_value == DUTY_CYCLE_MIN)
		{
			return;
		}
		OCR0B = register_value - 1;
		return;
	}
}

void increase_pwm(uint8_t pin)
{
	uint8_t register_value;

	if (pin == 6)
	{
		// read in value from Output Compare Register A
		register_value = OCR0A;
		// dont go bellow zero
		if (register_value == DUTY_CYCLE_MAX)
		{
			return;
		}
		OCR0A = register_value + 1;
		return;
	}

	if (pin == 5)
	{
		register_value = OCR0B;
		if (register_value == DUTY_CYCLE_MAX)
		{
			return;
		}
		OCR0B = register_value + 1;
		return;
	}
}

