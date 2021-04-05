#include "json.h"
#include "utility.h"


void sendData(float vin, float vout, short int duty_cycle, String delimiter)
{
	StaticJsonDocument<48> jsonDocument;
	jsonDocument["ADC"]["vin"] = vin;
	jsonDocument["ADC"]["vout"] = vout;
	jsonDocument["PWM"]["dutyCycle"] = duty_cycle_to_percent(duty_cycle);

	serializeJson(jsonDocument, Serial);
	Serial.println(delimiter);
}

DynamicJsonDocument readData(void)
{
	DynamicJsonDocument doc(128);
	DeserializationError err = deserializeJson(doc, Serial.readString());
	return doc;
}