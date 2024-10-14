#include "leds.h"
#include "positions.h"

CRGB leds[NUM_LEDS];

void setupLeds() {
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
}

// void animateLeds() {
//     for (int i = 0; i < NUM_LEDS; i++) {
//         leds[i] = CRGB::White;
//         FastLED.show();
//         delay(1000);
//         leds[i] = CRGB::Black;
//     }

//     for (int i = NUM_LEDS - 1; i >= 0; i--) {
//         leds[i] = CRGB::White;
//         FastLED.show();
//         delay(1000);
//         leds[i] = CRGB::Black;
//     }
// }

// void controlLed(LedConfig config) {
//     unsigned long currentMillis = millis();

//     switch(config.mode) {
//         case OFF:
//             leds[config.position] = CRGB::Black;
//             break;
//         case ON:
//             leds[config.position] = config.color;
//             break;
//         case SOLID:
//             leds[config.position] = config.color;
//             FastLED.show();
//             delay(config.delayTime);
//             break; 
//         case BLINK:
//             if (currentMillis - config.lastUpdate >= config.delayTime) {
//                 config.lastUpdate = currentMillis;
//                 config.state = !config.state;
//                 leds[config.position] = config.state ? config.color : CRGB::Black;
//             }
//             break;
//     }
//     FastLED.show();
// }

// void controlMultipleLeds(const LedConfig configs[], int numConfigs) {
//     for (int i = 0; i < numConfigs; ++i) {
//         controlLed(configs[i].position, configs[i].color, configs[i].mode, configs[i].delayTime);
//     }
// }

void clearLEDs() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}

void updateLEDs(JSONVar trainList) {
    // clear all LEDs
    clearLEDs();

    // loop through trainList
    for (int i = 0; i < trainList.length(); i++) {
        const char* nextStaId = trainList[i]["nextStaId"]; // next parent station
        String trDr = trainList[i]["trDr"]; // direction
        String prdt = trainList[i]["prdt"]; // time of prediction made
        String arrT = trainList[i]["arrT"]; // predicted arrival time
        String isApp = trainList[i]["isApp"]; // is approaching 1=true, 0=false
        String isDly = trainList[i]["isDly"]; // is delayed 1=true, 0=false

        int index = findIndexOfNextStaId(nextStaId);

        if (index != -1) {
            if (isApp == "1") {
                leds[index] = CRGB::Green;
            }
        }
    }

    FastLED.show();
}