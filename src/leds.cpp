// #include "leds.h"
// #include "positions.h"

// CRGB leds[NUM_LEDS];

// void setupLeds() {
//     FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
//     FastLED.clear();
//     FastLED.show();
// }

// void clearLEDs() {
//     for (int i = 0; i < NUM_LEDS; i++) {
//         leds[i] = CRGB::Black;
//     }
// }

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