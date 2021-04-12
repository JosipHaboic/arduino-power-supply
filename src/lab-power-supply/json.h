#include <ArduinoJson.h>

void sendData(float vin, float vout, short int voltage_duty_cylce, short int current_duty_cylce, String delimiter);
StaticJsonDocument<48> deserialize(String data);