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

JsonDocument doc;
JsonObject CTAAlerts;
JsonArray CTAAlerts_Array;

String sanitizeString(String input) {
    input.replace("’", "'"); // Replace curly apostrophe with standard one
    return input;
}

void setupOled() {
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


void updateRssData() {
    String payload = getPayload();

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        // JsonDocument emptyDoc; // gnerate an emptyDoc variable
        // return emptyDoc.to<JsonObject>();
        return;
    }

    // process data
    CTAAlerts = doc["CTAAlerts"];
    CTAAlerts_Array = CTAAlerts["Alert"].as<JsonArray>();
    const char* CTAAlerts_TimeStamp = CTAAlerts["TimeStamp"]; // "2024-10-20T12:13:49"
    Serial.println("Timestamp: " + String(CTAAlerts_TimeStamp));

    // update array length
    arrayLength = CTAAlerts_Array.size();
    // reset index
    currentIndex = 0;
}

void displayRssData(String data) {
    Serial.println(data);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(data);
    display.display();
}

void displayNextRssFeed() {

    // for (JsonObject cta_alert : CTAAlerts_Alert) {
    //     const char* alertId = cta_alert["AlertId"];
    //     Serial.println("alertId:");
    //     Serial.println(alertId);

    // }
    
    String headline = sanitizeString(CTAAlerts_Array[currentIndex]["Headline"].as<String>());
    String shortDescription = sanitizeString(CTAAlerts_Array[currentIndex]["ShortDescription"].as<String>());
    Serial.println(headline);
    Serial.println(shortDescription);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(headline);
    display.println(shortDescription);
    display.display();

    currentIndex++;

    if (currentIndex >= arrayLength) {
        currentIndex = 0;
    }
}