#include <Arduino.h>

#include "de_DE.h"

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

void Grid_de_DE::setTime(int hour, int minute) {
  if(hour == -1 || minute == -1) {
	return;
  }

  if(DND::active(hour, minute)) {
	for(int i = 0; i < NUM_LEDS; i++) {
	  Led::ids[i].setRGB(0, 0, 0);
	}

	FastLED.show();

	return;
  }
  
  int singleMinute = minute % 5;
  int hourLimit = 6;

  minute = (minute - (minute % 5));

  if(minute >= 25) {
	hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  for(int i = 0; i < NUM_LEDS; i++) {
	Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
  }

  for(int i = 0; i < 5; i++) {
	Led::ids[Led::getLedId(Grid_de_DE::time_it_is[i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
  }

  for(int m = 0; m < 12; m++) {
	if(Grid_de_DE::time_minutes[minute][m] >= 0) {
	  Led::ids[Led::getLedId(Grid_de_DE::time_minutes[minute][m])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }

  if(hour == 1 && minute == 0) {
	hourLimit = 3;
  }

  for(int h = 0; h < hourLimit; h++) {
	if(Grid_de_DE::time_hours[hour][h] >= 0) {
	  Led::ids[Led::getLedId(Grid_de_DE::time_hours[hour][h])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }

  for(int sm = 0; sm < singleMinute; sm++) {
	if(Grid_de_DE::time_single_minutes[sm] >= 0) {
	  Led::ids[Led::getLedId(Grid_de_DE::time_single_minutes[sm])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }

  FastLED.setBrightness(Config::brightness * 255);
  FastLED.show();
}

int Grid_de_DE::time_it_is[5] = {14, 15, 17, 18, 19}; // es ist

int Grid_de_DE::time_minutes[12][12] = {
  {139, 140, 141,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  { 21,  22,  23,  24,  55,  56,  57,  58,  -1,  -1,  -1,  -1}, // fünf nach
  { 27,  28,  29,  30,  55,  56,  57,  58,  -1,  -1,  -1,  -1}, // zehn nach
  { 44,  45,  46,  47,  48,  49,  50,  55,  56,  57,  58,  -1}, // viertel nach
  { 31,  32,  33,  34,  35,  36,  37,  55,  56,  57,  58,  -1}, // zwanzig nach
  { 21,  22,  23,  24,  59,  60,  61,  66,  67,  68,  69,  -1}, // fünf vor halb
  { 66,  67,  68,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  { 21,  22,  23,  24,  55,  56,  57,  58,  66,  67,  68,  69}, // fünf nach halb
  { 31,  32,  33,  34,  35,  36,  37,  59,  60,  61,  -1,  -1}, // zwanzig vor
  { 44,  45,  46,  47,  48,  49,  50,  59,  60,  61,  -1,  -1}, // viertel vor
  { 27,  28,  29,  30,  59,  60,  61,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  { 21,  22,  23,  24,  59,  60,  61,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int Grid_de_DE::time_hours[12][6] = {
  { 71,  72,  73,  74,  75,  -1}, // zwölf
  { 81,  82,  83,  84,  -1,  -1}, // eins
  { 79,  80,  81,  82,  -1,  -1}, // zwei
  { 93,  94,  95,  96,  -1,  -1}, // drei
  {112, 113, 114, 115,  -1,  -1}, // vier
  { 99, 100, 101, 102,  -1,  -1}, // fünf
  {132, 133, 134, 135, 136,  -1}, // sechs
  { 84,  85,  86,  87,  88,  89}, // sieben
  {119, 120, 121, 122,  -1,  -1}, // acht
  {108, 109, 110, 111,  -1,  -1}, // neun
  {123, 124, 125, 126,  -1,  -1}, // zehn
  {105, 106, 107,  -1,  -1,  -1}  // elf
};

int Grid_de_DE::time_single_minutes[4] = {156, 0, 12, 168};