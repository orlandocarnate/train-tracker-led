#include <Arduino.h>
#include "leds.h"
#include "WiFi.h"
#include "creds.h"
#include "positions.h"
// #define LED_PIN 2

const char* ssid = my_ssid;
const char* password = my_password;

JSONVar trainList;

void setup() {
    Serial.begin(115200);

    // Wifi Setup
    WiFi.begin(ssid, password);

    int x = 10;
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
        x = x + 10;
    }
    Serial.println("");
    Serial.println("Connected to WiFi.");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP().toString());

    // pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
    setupLeds();
}

void loop() {
    // TODO: Get Train Update every 10 seconds
    trainList = getTrainPositions();
    // int numLeds = getStopLength(mapidList);

    updateLEDs(trainList);

    delay(30000);
}
