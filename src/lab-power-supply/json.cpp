#include "json.h"
#include "utility.h"

const int capacity = 48;
StaticJsonDocument<capacity> jsonDocument;

void sendData(float vin, float vout, short int duty_cycle, String delimiter)
{
	jsonDocument["ADC"]["vin"] = vin;
	jsonDocument["ADC"]["vout"] = vout;
	jsonDocument["PWM"]["dutyCycle"] = duty_cycle_to_percent(duty_cycle);

	serializeJson(jsonDocument, Serial);
	Serial.println(delimiter);
}