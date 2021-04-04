#include <util/delay.h>
#include <avr/interrupt.h>
#include <ArduinoJson.h>
#include "./display.h"
#include "./adc.h"
#include "./pwm.h"
#include "./buttons.h"
#include "./utility.h"

// duty cycle clamps
const uint8_t DUTY_CYCLE_MIN = 0;
const uint8_t DUTY_CYCLE_MAX = 255;

// Voltage at VREF (meassured by DMM)
const float VREF = 4.50;
float vin = 0.00;
float vout = 0.00;
volatile uint8_t duty_cycle = 0;
const int capacity = 48;
StaticJsonDocument<capacity> jsonDocument;
volatile bool button_pressed = false;
const String SPACER = "---------------------";

void display_setup(void);
void display_update(void);

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
	// adc_vin = adc_read(A0, VREF);
	vin = adc_read(A0, VREF);
	delay(10);
	// adc_vout = adc_read(A1, VREF);
	vout = adc_read(A1, VREF);

	// generate PWM
	pwm_set_duty_cycle(duty_cycle);

	// display stuff
	display_update();

	jsonDocument["ADC"]["vin"] = vin;
	jsonDocument["ADC"]["vout"] = vout;
	jsonDocument["PWM"]["dutyCycle"] = duty_cycle_to_percent(duty_cycle);

	serializeJson(jsonDocument, Serial);
	Serial.println();
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

void display_update(void)
{
	oled.clearDisplay();
	oled.setCursor(0, 0);

	oled.setTextSize(1);
	oled.print("Vin   ");
	oled.setTextSize(2);
	oled.println(vin);
	oled.setTextSize(1);
	oled.println(SPACER);

	oled.setTextSize(1);
	oled.print("Vout  ");
	oled.setTextSize(2);
	oled.println(vout);
	oled.setTextSize(1);
	oled.println(SPACER);

	oled.setTextSize(1);
	oled.print("Duty Cycle    ");
	oled.setTextSize(2);
	oled.print(duty_cycle_to_percent(duty_cycle));
	oled.println("%");

	oled.display();
}

// void buttons_handle() {
// 	// process buttons input
// 	if (digitalRead(PD2) == LOW)
// 	{
// 		if (duty_cycle > DUTY_CYCLE_MIN)
// 		{
// 			duty_cycle -= 1;
// 		}
// 	}
// 	if (digitalRead(PD3) == LOW)
// 	{
// 		if (duty_cycle < DUTY_CYCLE_MAX)
// 		{
// 			duty_cycle += 1;
// 		}
// 	}
// }
