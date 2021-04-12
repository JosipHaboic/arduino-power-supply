#include "json.h"
#include "utility.h"

void sendData(float vin, float vout, short int voltage_duty_cycle, short int current_duty_cycle, String delimiter)
{
	StaticJsonDocument<48> jsonDocument;
	jsonDocument["ADC"]["vin"] = vin;
	jsonDocument["ADC"]["vout"] = vout;
	jsonDocument["PWM"]["dutyCycle"]["voltage"] = duty_cycle_to_percent(voltage_duty_cycle);
	jsonDocument["PWM"]["dutyCycle"]["current"] = duty_cycle_to_percent(current_duty_cycle);

	serializeJson(jsonDocument, Serial);
	Serial.println(delimiter);
}

StaticJsonDocument<48> deserialize(String data)
{
	StaticJsonDocument<48> jsonDocument;
	DeserializationError err = deserializeJson(jsonDocument, data);

	if (err == DeserializationError::IncompleteInput) {
		jsonDocument["error"] = "IncompleteInput";
	}
	if (err == DeserializationError::InvalidInput)
	{
		jsonDocument["error"] = "InvalidInput";
	}
	if (err == DeserializationError::NoMemory)
	{
		jsonDocument["error"] = "NoMemory";
	}
	if (err == DeserializationError::NotSupported)
	{
		jsonDocument["error"] = "NotSupported";
	}
	if (err == DeserializationError::TooDeep)
	{
		jsonDocument["error"] = "TooDeep";
	}

	return jsonDocument;
}