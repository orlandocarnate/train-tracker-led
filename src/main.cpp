#include <Arduino.h>
#include "leds.h"
#include "WiFi.h"
#include "creds.h"
#include "positions.h"
// #define LED_PIN 2

const char* ssid = my_ssid;
const char* password = my_password;

JSONVar trainList;

size_t getStopLength(const Stop* list) {
    return sizeof(mapidList) / sizeof(mapidList[0])
}

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

    for (int i = 0; i < trainList.length(); i++) {
        String nextStaId = trainList[i]["nextStaId"]; // next parent station
        String trDr = trainList[i]["trDr"]; // direction
        String prdt = trainList[i]["prdt"]; // time of prediction made
        String arrT = trainList[i]["arrT"]; // predicted arrival time
        String isApp = trainList[i]["isApp"]; // is approaching 1=true, 0=false
        String isDly = trainList[i]["isDly"]; // is delayed 1=true, 0=false
    }
}
