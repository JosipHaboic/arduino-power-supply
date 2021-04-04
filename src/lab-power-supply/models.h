struct ADC {
	float vin;
	float vout;
};

struct PWM {
	short int dutyCycle;
};

struct Data {
	ADC adc;
	PWM pwm;
};