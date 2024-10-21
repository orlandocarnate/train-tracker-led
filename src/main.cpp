#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>
#include <TimeLib.h>
#include <WiFiClientSecure.h>
// #include <FastLED.h>
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
    setupOled();
    updateRssData();
    // const char* CTAAlerts_TimeStamp = CTAAlerts["TimeStamp"]; // "2024-10-20T12:13:49"
    // Serial.println("Timestamp: " + String(CTAAlerts_TimeStamp));
    
    // Serial.println("CTAlerts Object: ");
    // if (CTAAlerts.containsKey("Alert")) {
    //     Serial.println(CTAAlerts["Alert"][0]["Headline"].as<String>());
    // } else {
    //     Serial.println("Alert key not found.");
    // }

}

// ********** LEDS **********
// void updateLEDs(const char* nextStaId, const char* isApp, const char* isDly) {
//     // clear all LEDs
//     Serial.println("updateLEDs param values: ");
//     Serial.println(nextStaId);
//     Serial.println(isApp);
//     Serial.println(isDly);

//     int index = findIndexOfNextStaId(nextStaId);

//     Serial.print("Index: ");
//     Serial.println(index);

//     if (index != -1) {
//         if (strcmp(isDly, "1") == 0) { // Compare strings properly
//             Serial.println("RED");
//             leds[index] = CRGB::Red;
//             leds[index].nscale8(24);
//         } else if (strcmp(isApp, "1") == 0) {
//             Serial.println("GREEN");
//             leds[index] = CRGB::Green;
//             leds[index].nscale8(32);
//         } else if (strcmp(isApp, "0") == 0) {
//             Serial.println("YELLOW");
//             leds[index] = CRGB::Yellow;
//             leds[index].nscale8(16);
//         }
//     }
    

// }

// ********** TRAIN **********
// JsonArray getTrainPositions() {
//   WiFiClientSecure client;
//   client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

//   url = apiUrl + "?key=" + apiKey + "&rt=Blue" + outputType;

//   HTTPClient https;
//   https.begin(client, url);

//   int httpResponseCode = https.GET();
//   String payload = "{}";

//   if (httpResponseCode > 0) {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     payload = https.getString();
//     // // Iterate through the array
//     // for (JsonObject obj : array) {
//     //     const char* id = obj["id"];
//     //     const char* value = obj["value"];
//     //     Serial.print("ID: ");
//     //     Serial.println(id);
//     //     Serial.print("Value: ");
//     //     Serial.println(value);
//     // }

//   } else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }

//   https.end();

  
//   // Create JSON document to hold the parsed data
//   JsonDocument doc;

//   // Deserialize the JSON document
//   DeserializationError error = deserializeJson(doc, payload);

//   if (error) {
//       Serial.print("Deserialization failed: ");
//       Serial.println(error.c_str());
//       JsonDocument emptyDoc; // gnerate an emptyDoc variable
//       return emptyDoc.to<JsonArray>(); // return empty array
//   }

//     // Extract the array
//     JsonObject ctatt = doc["ctatt"];
//     const char* ctatt_tmst = ctatt["tmst"]; // "2024-10-14T10:32:41"
//     const char* ctatt_errCd = ctatt["errCd"]; // "0"
//     // ctatt["errNm"] is null

//     const char* ctatt_route_0_name = ctatt["route"][0]["@name"]; // "blue"

//     clearLEDS();

//     for (JsonObject ctatt_route_0_train_item : ctatt["route"][0]["train"].as<JsonArray>()) {

//         const char* ctatt_route_0_train_item_nextStaId = ctatt_route_0_train_item["nextStaId"]; // "40180", ...
//         const char* ctatt_route_0_train_item_nextStpId = ctatt_route_0_train_item["nextStpId"]; // "30034", ...
//         const char* ctatt_route_0_train_item_arrT = ctatt_route_0_train_item["arrT"]; // "2024-10-14T10:33:26", ...
//         const char* ctatt_route_0_train_item_isApp = ctatt_route_0_train_item["isApp"]; // "1", "0", "0", "0", ...
//         const char* ctatt_route_0_train_item_isDly = ctatt_route_0_train_item["isDly"]; // "0", "0", "0", "0", ...

//         Serial.print("Next Station: ");
//         Serial.println(ctatt_route_0_train_item_nextStaId);
//         Serial.print("Next Stop: ");
//         Serial.println(ctatt_route_0_train_item_nextStpId);
//         Serial.print("Arrival Time: ");
//         Serial.println(ctatt_route_0_train_item_arrT);
//         Serial.print("Is Approaching: ");
//         Serial.println(ctatt_route_0_train_item_isApp);
//         Serial.print("Is Delayed: ");
//         Serial.println(ctatt_route_0_train_item_isDly);

//         updateLEDs(ctatt_route_0_train_item_nextStpId, ctatt_route_0_train_item_isApp, ctatt_route_0_train_item_isDly);

//     }

//     showLEDS();

//     return ctatt["route"][0]["train"].as<JsonArray>();
// }

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
