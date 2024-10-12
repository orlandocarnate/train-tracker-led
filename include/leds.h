#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>

#define NUM_LEDS 33
#define DATA_PIN 5

extern CRGB leds[NUM_LEDS];

enum LedMode { OFF, ON, SOLID, BLINK };

struct LedConfig {
    int position;
    CRGB color;
    LedMode mode;
    int delayTime;
    unsigned long lastUpdate;
    bool state;
};

void controlLed(int position, CRGB color, LedMode mode, int delayTime);
void setupLeds();
void animateLeds();

#endif // LEDS_H
