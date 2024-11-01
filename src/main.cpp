#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <TimeLib.h>
#include <WiFiClientSecure.h>
#include "WiFi.h"
#include "creds.h"
#include "leds.h"
#include "positions.h"
#include "rss.h"


// static const char* train_arrival_url= "https://lapi.transitchicago.com/api/1.0/ttarrivals.aspx?";
// static const char* follow_train_url= "https://lapi.transitchicago.com/api/1.0/ttfollow.aspx";
// static const char* train_positions_url= "https://lapi.transitchicago.com/api/1.0/ttpositions.aspx";
// static const char* output_type= "&outputType=JSON";

const long trainInterval = 10000; // 10 seconds
unsigned long previousTrainMillis = 0;

const long rssInterval = 5000;  // 5 seconds
unsigned long previousRssMillis = 0;

const long rssArrayUpdateInterval = 60000; 
unsigned long previousRssArrayUpdateMillis = 0;

const char* ssid = my_ssid;
const char* password = my_password;



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
    setupTftLcd();
    updateRssData();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        unsigned long currentMillis = millis();

        // Update Train Positions every 
        if (currentMillis - previousTrainMillis >= trainInterval) {
            previousTrainMillis = currentMillis;
            Serial.println("Train Positions Updating");
            updateTrainPositions();
        }

        // Update RSS OLED display every 5 seconds and display next item of array
        if (currentMillis - previousRssMillis >= rssInterval) {
            previousRssMillis = currentMillis;
            Serial.println("Display Next RSS Feed");
            // for (JsonObject cta_alert : CTAAlerts["Alert"].as<JsonArray>()) {
            //     String data = sanitizeString(cta_alert["Headline"].as<String>());
            //     displayRssData(data);
            // }
            displayNextRssFeed();

        }

        // Update RSS OLED display every 5 seconds and display next item of array
        // if (currentMillis - previousRssArrayUpdateMillis >= rssArrayUpdateInterval) {
        //     previousRssArrayUpdateMillis = currentMillis;
        //     Serial.println("Update RSS Feed Array");
        //     CTAAlerts = getRssObject();
        // }

    };
}
