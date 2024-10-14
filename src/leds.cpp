#include "leds.h"

CRGB* leds;

void setupLeds(int numLeds) {
    leds = new CRGB[numLeds];
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, numLeds);
    FastLED.clear();
    FastLED.show();
}

void animateLeds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
        FastLED.show();
        delay(1000);
        leds[i] = CRGB::Black;
    }

    for (int i = NUM_LEDS - 1; i >= 0; i--) {
        leds[i] = CRGB::White;
        FastLED.show();
        delay(1000);
        leds[i] = CRGB::Black;
    }
}

void controlLed(LedConfig config) {
    unsigned long currentMillis = millis();

    switch(config.mode) {
        case OFF:
            leds[config.position] = CRGB::Black;
            break;
        case ON:
            leds[config.position] = config.color;
            break;
        case SOLID:
            leds[config.position] = config.color;
            FastLED.show();
            delay(config.delayTime);
            break; 
        case BLINK:
            if (currentMillis - config.lastUpdate >= config.delayTime) {
                config.lastUpdate = currentMillis;
                config.state = !config.state;
                leds[config.position] = config.state ? config.color : CRGB::Black;
            }
            break;
    }
    FastLED.show();
}

void controlMultipleLeds(const LedConfig configs[], int numConfigs) {
    for (int i = 0; i < numConfigs; ++i) {
        controlLed(configs[i].position, configs[i].color, configs[i].mode, configs[i].delayTime);
    }
}