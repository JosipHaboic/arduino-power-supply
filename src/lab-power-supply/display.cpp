#include "OakOLED.h"
#include "utility.h"

OakOLED oled;

void display_setup(void)
{
	oled.begin();
	oled.setTextColor(1);
}

void display_update(float vin, float vout, short int duty_cycle)
{
	oled.clearDisplay();
	oled.setCursor(0, 0);

	oled.setTextSize(1);
	oled.print("Vin   ");
	oled.setTextSize(2);
	oled.println(vin);
	oled.setTextSize(1);
	oled.println();

	oled.setTextSize(1);
	oled.print("Vout  ");
	oled.setTextSize(2);
	oled.println(vout);
	oled.setTextSize(1);
	oled.println();

	oled.setTextSize(1);
	oled.print("Duty Cycle    ");
	oled.setTextSize(2);
	oled.print(duty_cycle_to_percent(duty_cycle));
	oled.println("%");

	oled.display();
}