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
const float VREF = 5.10;

float vin = 0.00;
float vout = 0.00;
// resistor divider at vin adc
const float VIN_R1 = 99.6e3;
const float VIN_R2 = 94.6e3;
const float VIN_FACTOR = (VIN_R2 / (VIN_R1 + VIN_R2));

const float VOUT_R1 = 98.6e3;
const float VOUT_R2 = 100.2e3;
const float VOUT_FACTOR = (VOUT_R2 / (VOUT_R1 + VOUT_R2));

const uint8_t VOLTAGE_REGULATOR_PIN = 6;
const uint8_t CURRENT_REGULATOR_PIN = 5;

String incommingData;
StaticJsonDocument<48> incommingJson;


void setup()
{
	Serial.begin(9600);

	buttons_setup();
	display_setup();
	adc_setup();
	pwm_setup();
	pwm_set_duty_cycle(VOLTAGE_REGULATOR_PIN, 0);
	pwm_set_duty_cycle(CURRENT_REGULATOR_PIN, 0);
	pwm_start();
	// attachInterrupt(digitalPinToInterrupt(2), decrease_pwm, HIGH);
	// attachInterrupt(digitalPinToInterrupt(3), increase_pwm, HIGH);
 }

void loop(void)
{
	// read ADC
	vin = ((1.0 / VIN_FACTOR) * (adc_read(A0, VREF)));
	delay(10);
	vout = ((1.0 / VOUT_FACTOR) * (adc_read(A1, VREF)));

	// generate PWM
	pwm_set_duty_cycle(VOLTAGE_REGULATOR_PIN ,voltage_duty_cycle);
	pwm_set_duty_cycle(CURRENT_REGULATOR_PIN ,current_duty_cycle);

	// display stuff
	display_update(vin, vout, voltage_duty_cycle);


	// send json data over serial port
	sendData(vin, vout, voltage_duty_cycle, current_duty_cycle, "\r\n");

	// read json data over serial port
	if (Serial.available() > 0) {
		incommingData = Serial.read();

		Serial.println(incommingData);

		// incommingJson = deserialize(incommingData);
		// if (incommingData["dutyCycle"]) {
		// 	duty_cycle = (u8) incommingData["dutyCycle"];
		// }
	}
}
