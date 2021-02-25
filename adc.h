void adc_setup(void)
{
	analogReference(EXTERNAL);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	ADCSRA |= (1 << ADPS1 | 1 << ADPS0); // prescaler of 8
}

float adc_read(uint8_t adc, float vref)
{
	float sum = 0.0;
	for (int i = 0; i <= 255; i += 1)
	{
		sum += (analogRead(adc) / 1024.00) * vref;
	}
	return sum / 255.00;
}
