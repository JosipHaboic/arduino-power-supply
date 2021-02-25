#include "Wire.h"
#include "Adafruit_GFX.h"
#include "OakOLED.h"

OakOLED oled;

void display_setup(void);


void display_setup(void) {
	oled.begin();
	oled.setTextColor(1);
}