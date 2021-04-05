#include <ArduinoJson.h>


void sendData(float vin, float vout, short int duty_cylce, String delimiter);
DynamicJsonDocument readData(void);