#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <TimeLib.h>
#include <WiFiClientSecure.h>
#include <FastLED.h>
#include "WiFi.h"
#include "creds.h"
#include "positions.h"


#define NUM_LEDS 33
#define DATA_PIN 5
static const char* train_arrival_url= "https://lapi.transitchicago.com/api/1.0/ttarrivals.aspx?";
static const char* follow_train_url= "https://lapi.transitchicago.com/api/1.0/ttfollow.aspx";
static const char* train_positions_url= "https://lapi.transitchicago.com/api/1.0/ttpositions.aspx";
static const char* output_type= "&outputType=JSON";

const char* ssid = my_ssid;
const char* password = my_password;
String apiKey = cta_train_key;
String apiUrl = train_positions_url;
String outputType = output_type;

String url = "";

CRGB leds[NUM_LEDS];

void setupLeds() {
    Serial.println("Init LEDs");
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    
    // Test sequence: Light up each LED with a different color
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;   // Set LED to Red
        FastLED.show();
        delay(100);            // Wait for 100ms

        leds[i] = CRGB::Green; // Set LED to Green
        FastLED.show();
        delay(100);            // Wait for 100ms

        leds[i] = CRGB::Blue;  // Set LED to Blue
        FastLED.show();
        delay(100);            // Wait for 100ms

        leds[i] = CRGB::Black; // Turn off the LED
    }
    FastLED.show();
}

void clearLEDs() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
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

int findIndexOfNextStaId(const char* nextStaId) {
    for (int i = 0; i < sizeof(mapidList) / sizeof(mapidList[0]); i++) {
        if (strcmp(mapidList[i].id, nextStaId) == 0) {
            return i;
        }
    }
    return -1; // Return -1 if not found
}

// ********** LEDS **********
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

// ********** TRAIN **********
JsonArray getTrainPositions() {
  WiFiClientSecure client;
  client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

  url = apiUrl + "?key=" + apiKey + "&rt=Blue&outputType=JSON";

  HTTPClient https;
  https.begin(client, url);

  int httpResponseCode = https.GET();
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = https.getString();
    // // Iterate through the array
    // for (JsonObject obj : array) {
    //     const char* id = obj["id"];
    //     const char* value = obj["value"];
    //     Serial.print("ID: ");
    //     Serial.println(id);
    //     Serial.print("Value: ");
    //     Serial.println(value);
    // }

  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  https.end();

  
  // Create JSON document to hold the parsed data
  JsonDocument doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
      Serial.print("Deserialization failed: ");
      Serial.println(error.c_str());
      JsonDocument emptyDoc; // gnerate an emptyDoc variable
      return emptyDoc.to<JsonArray>(); // return empty array
  }

    // Extract the array
    JsonObject ctatt = doc["ctatt"];
    const char* ctatt_tmst = ctatt["tmst"]; // "2024-10-14T10:32:41"
    const char* ctatt_errCd = ctatt["errCd"]; // "0"
    // ctatt["errNm"] is null

    const char* ctatt_route_0_name = ctatt["route"][0]["@name"]; // "blue"

    FastLED.clear();

    for (JsonObject ctatt_route_0_train_item : ctatt["route"][0]["train"].as<JsonArray>()) {

        const char* ctatt_route_0_train_item_rn = ctatt_route_0_train_item["rn"]; // "101", "103", "104", "107", ...
        const char* ctatt_route_0_train_item_destSt = ctatt_route_0_train_item["destSt"]; // "30171", "30171", ...
        const char* ctatt_route_0_train_item_destNm = ctatt_route_0_train_item["destNm"]; // "O'Hare", "O'Hare", ...
        const char* ctatt_route_0_train_item_trDr = ctatt_route_0_train_item["trDr"]; // "1", "1", "1", "5", ...
        const char* ctatt_route_0_train_item_nextStaId = ctatt_route_0_train_item["nextStaId"]; // "40180", ...
        const char* ctatt_route_0_train_item_nextStpId = ctatt_route_0_train_item["nextStpId"]; // "30034", ...
        const char* ctatt_route_0_train_item_nextStaNm = ctatt_route_0_train_item["nextStaNm"]; // "Oak Park", ...
        const char* ctatt_route_0_train_item_prdt = ctatt_route_0_train_item["prdt"]; // "2024-10-14T10:32:26", ...
        const char* ctatt_route_0_train_item_arrT = ctatt_route_0_train_item["arrT"]; // "2024-10-14T10:33:26", ...
        const char* ctatt_route_0_train_item_isApp = ctatt_route_0_train_item["isApp"]; // "1", "0", "0", "0", ...
        const char* ctatt_route_0_train_item_isDly = ctatt_route_0_train_item["isDly"]; // "0", "0", "0", "0", ...
        // ctatt_route_0_train_item["flags"] is null
        const char* ctatt_route_0_train_item_lat = ctatt_route_0_train_item["lat"]; // "41.87242", "41.88573", ...
        const char* ctatt_route_0_train_item_lon = ctatt_route_0_train_item["lon"]; // "-87.79533", "-87.63293", ...
        const char* ctatt_route_0_train_item_heading = ctatt_route_0_train_item["heading"]; // "94", "269", ...

        Serial.print("Next Station: ");
        Serial.println(ctatt_route_0_train_item_nextStaId);
        Serial.print("Arrival Time: ");
        Serial.println(ctatt_route_0_train_item_arrT);
        Serial.print("Is Approaching: ");
        Serial.println(ctatt_route_0_train_item_isApp);
        Serial.print("Is Delayed: ");
        Serial.println(ctatt_route_0_train_item_isDly);

        updateLEDs(ctatt_route_0_train_item_nextStaId, ctatt_route_0_train_item_isApp, ctatt_route_0_train_item_isDly);

    }

    FastLED.show();

    return ctatt["route"][0]["train"].as<JsonArray>();
}

void loop() {
    // TODO: Get Train Update every 10 seconds
    if (WiFi.status() == WL_CONNECTED) {
        JsonArray trainList = getTrainPositions();

    };

    delay(10000);
}
