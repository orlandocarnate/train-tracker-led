#include "leds.h"
#include "positions.h"

CRGB leds[NUM_LEDS];

void setupLeds() {
    Serial.println("Init LEDs");
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    
    // Test sequence: Light up each LED with a different color
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;   // Set LED to Red
        FastLED.show();
        delay(10);            // Wait for 100ms

        leds[i] = CRGB::Green; // Set LED to Green
        FastLED.show();
        delay(10);            // Wait for 100ms

        leds[i] = CRGB::Blue;  // Set LED to Blue
        FastLED.show();
        delay(10);            // Wait for 100ms

        leds[i] = CRGB::Black; // Turn off the LED
    }
    FastLED.show();
}

// void clearLEDs() {
//     for (int i = 0; i < NUM_LEDS; i++) {
//         leds[i] = CRGB::Black;
//     }
// }


void clearLEDS() {
    FastLED.clear();
}

void showLEDS() {
    FastLED.show();
}

// void updateLEDs(JsonArray trainList) {
//     // clear all LEDs
//     clearLEDs();

//     // loop through trainList
//     for (int i = 0; i < trainList.length(); i++) {
//         const char* nextStaId = trainList[i]["nextStaId"]; // next parent station
//         String trDr = trainList[i]["trDr"]; // direction
//         String prdt = trainList[i]["prdt"]; // time of prediction made
//         String arrT = trainList[i]["arrT"]; // predicted arrival time
//         String isApp = trainList[i]["isApp"]; // is approaching 1=true, 0=false
//         String isDly = trainList[i]["isDly"]; // is delayed 1=true, 0=false

//         int index = findIndexOfNextStaId(nextStaId);

//         if (index != -1) {
//             if (isApp == "1") {
//                 leds[index] = CRGB::Green;
//             }
//         }
//     }

//     FastLED.show();
// }

void updateLEDs(const char* nextStaId, const char* isApp, const char* isDly) {
    // clear all LEDs
    

    Serial.println("updateLEDs param values: ");
    Serial.println(nextStaId);
    Serial.println(isApp);
    Serial.println(isDly);

    int index = findIndexOfNextStaId(nextStaId);

    Serial.print("Index: ");
    Serial.println(index);

    if (index != -1) {
        if (strcmp(isDly, "1") == 0) { // Compare strings properly
            Serial.println("RED");
            leds[index] = CRGB::Red;
            leds[index].nscale8(24);
        } else if (strcmp(isApp, "1") == 0) {
            Serial.println("GREEN");
            leds[index] = CRGB::Green;
            leds[index].nscale8(32);
        } else if (strcmp(isApp, "0") == 0) {
            Serial.println("YELLOW");
            leds[index] = CRGB::Yellow;
            leds[index].nscale8(16);
        }
    }

    


    

}
