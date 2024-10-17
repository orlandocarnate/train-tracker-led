#include "rss.h"

// Set the LCD address to 0x27 for a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdSetup() {
    // Initialize LCD
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello, World!");
}

String getPayload() {
    WiFiClientSecure client;

    client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

    String url = rss_blue_line;

    HTTPClient https;
    https.begin(client, url);

    int httpResponseCode = https.GET();
    String payload = "{}";

    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = https.getString();
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    https.end();
    
    return payload;
}


void parseRss() {
    String payload = getPayload();

    // Create JSON document to hold the parsed data
    JsonDocument doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.print("Deserialization failed: ");
        Serial.println(error.c_str());
        JsonDocument emptyDoc; // gnerate an emptyDoc variable
        // return emptyDoc.to<JsonArray>(); // return empty array
        return;
    }

    // process data
    JsonObject CTAAlerts = doc["CTAAlerts"].to<JsonObject>();
    String timeStamp = CTAAlerts["TimeStamp"];
        // CTAAlerts["ErrorCode"] = "0";
        // CTAAlerts["ErrorMessage"] = nullptr;

    // Array
    JsonArray CTAAlerts_Alert = CTAAlerts["Alert"].to<JsonArray>();

    // iterate through JsonArray
    for (JsonObject alertItem : CTAAlerts_Alert) {
        // assign variables
        String headline = alertItem["Headline"];
        String shortDescription = alertItem["ShortDescription"];
    }
}