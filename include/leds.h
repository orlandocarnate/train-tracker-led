#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>
#include "positions.h"
// #include <JSONVar.h>

#define NUM_LEDS 66
#define DATA_PIN 5

// extern CRGB leds[NUM_LEDS];

// enum LedMode { OFF, ON, SOLID, BLINK };

// struct LedConfig {
//     int position;
//     // CRGB color;
//     LedMode mode;
//     int delayTime;
//     unsigned long lastUpdate;
//     bool state;
// };

// void controlLed(int position, LedMode mode, int delayTime);
void setupLeds();
// void animateLeds();

void updateLEDs(const char* nextStaId, const char* isApp, const char* isDly);
void clearLEDS();
void showLEDS();

#endif // LEDS_H
