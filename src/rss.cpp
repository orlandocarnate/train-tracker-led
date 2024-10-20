#include "rss.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SSD1306_I2C_ADDRESS 0x3C
// #define SDA_PIN 21
// #define SCL_PIN 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

size_t arrayLength = 0;
size_t currentIndex = 0;
bool isDataNew = false;

JsonArray CTAAlerts_Alert;
JsonObject CTAAlerts;

String sanitizeString(String input) {
    input.replace("’", "'"); // Replace curly apostrophe with standard one
    return input;
}

void rssSetup() {
    Serial.begin(115200);
    Serial.println(F("OLED Setup Init"));
    display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Hello, World!");
    display.display();
}

String getPayload() {
    Serial.println("Get Payload");
    WiFiClientSecure client;

    client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

    String url = rss_blue_line;

    HTTPClient https;
    https.begin(client, url);

    int httpResponseCode = https.GET();
    String payload = "{}";

    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        payload = https.getString();
        // Serial.println(payload);
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    https.end();
    
    return payload;
}


void updateRssArray() {
    String payload = getPayload();

    // Create JSON document to hold the parsed data
    JsonDocument doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
    }

    // process data
    CTAAlerts = doc["CTAAlerts"];
    const char* CTAAlerts_TimeStamp = CTAAlerts["TimeStamp"]; // "2024-10-20T12:13:49"
    Serial.println("Timestamp: " + String(CTAAlerts_TimeStamp));

    for (JsonPair kv : doc.as<JsonObject>()) {
        Serial.println(kv.key().c_str());  
    }

    // Array
    CTAAlerts_Alert = doc["CTAAlerts"]["Alert"].as<JsonArray>();

    Serial.println("CTAAlerts_Alert[0] Keys: ");
    for (JsonPair kv : CTAAlerts_Alert[0].as<JsonObject>()) {
        Serial.println(kv.key().c_str());  
    }
    
    JsonObject obj = CTAAlerts_Alert[0].as<JsonObject>();
    
    String headline = sanitizeString(obj["Headline"].as<String>());

    Serial.println(headline);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(headline);
    display.display();



    arrayLength = CTAAlerts_Alert.size();
    Serial.print("Array Length: ");
    Serial.println(CTAAlerts_Alert.size());
    isDataNew = true;
    Serial.println("Rss Updated");
    Serial.println("isDataNew TRUE");
    // loopRssFeed(CTAAlerts_Alert);
}

void displayNextRssFeed() {

    for (JsonObject cta_alert : CTAAlerts_Alert) {
        const char* alertId = cta_alert["AlertId"];
        Serial.println("alertId:");
        Serial.println(alertId);

    }


}