#include <util/delay.h>
#include <avr/interrupt.h>
#include <ArduinoJson.h>
#include "./display.h"
#include "./adc.h"
#include "./pwm.h"
#include "./buttons.h"
#include "./utility.h"
#include "./json.h"


// Voltage at VREF (meassured by DMM)
const float VREF = 4.50;
float vin = 0.00;
float vout = 0.00;

void setup()
{
	Serial.begin(9600);

	buttons_setup();
	display_setup();
	adc_setup();
	pwm_setup();
	pwm_set_duty_cycle(0);
	pwm_start();
	attachInterrupt(digitalPinToInterrupt(2), decrease_pwm, HIGH);
	attachInterrupt(digitalPinToInterrupt(3), increase_pwm, HIGH);
 }

void loop(void)
{
	// read ADC
	vin = adc_read(A0, VREF);
	delay(10);
	vout = adc_read(A1, VREF);

	// generate PWM
	pwm_set_duty_cycle(duty_cycle);

	// display stuff
	display_update(vin, vout, duty_cycle);


	// send json data over serial port
	sendData(vin, vout, duty_cycle, "\r\n");
}

void decrease_pwm(void)
{
	if (duty_cycle > DUTY_CYCLE_MIN)
	{
		duty_cycle -= 1;
		delayMicroseconds(500);
	}
}

void increase_pwm(void)
{
	if (duty_cycle < DUTY_CYCLE_MAX)
	{
		duty_cycle += 1;
		delayMicroseconds(500);
	}
}