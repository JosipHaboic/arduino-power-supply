void pwm_setup(void) {
	DDRD |= (1 << DDD6);
	TCCR0A |= (1 << COM0A1);
	TCCR0A |= (1 << WGM01 ) | (1 << WGM00);
	OCR0A = 0;
	// TIMSK0 &= (1 << OCIE0A | 1 << TOIE0);
}

void pwm_set_duty_cycle(uint8_t duty_cycle) {
	OCR0A = duty_cycle;
}

void pwm_start(void) {
	// 62500Hz
	TCCR0B = TCCR0B & (0b11111000 | 0b00000001);
}