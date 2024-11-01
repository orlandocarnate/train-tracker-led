#include "rss.h"

TFT_eSPI tft = TFT_eSPI(); 


size_t arrayLength = 0;
size_t currentIndex = 0;
bool isDataNew = false;

JsonDocument rssDoc;
JsonObject CTAAlerts;
JsonArray CTAAlerts_Array;

String sanitizeString(String input) {
    input.replace("’", "'"); // Replace curly apostrophe with standard one
    return input;
}

void setupTftLcd() {
    Serial.begin(115200);
    Serial.println(F("Init ST7789V Display"));

    tft.begin();  // initialize
    tft.setRotation(3);

    // Update Pins in Platformio.ini
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
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
    DeserializationError error = deserializeJson(rssDoc, payload);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        // JsonDocument emptyDoc; // gnerate an emptyDoc variable
        // return emptyDoc.to<JsonObject>();
        return;
    }

    // process data
    CTAAlerts = rssDoc["CTAAlerts"];
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

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(data, 10, 10, 2);
}

// Takes text and gets the length and compares it with the width and breaks
// text down to print on the next line if it exceeds the width
void displayWrappedText(String text, int x, int y, int width, int fontSize) {
  tft.setTextFont(fontSize); // Set the built-in font size
  int cursorX = x;
  int cursorY = y;
  int lineHeight = tft.fontHeight(fontSize);
  String currentLine = "";
  String word = "";
  
  for (int i = 0; i < text.length(); i++) {
    char c = text.charAt(i);

    if (c == ' ' || c == '\n' || i == text.length() - 1) {
      if (i == text.length() - 1 && c != ' ' && c != '\n') {
        word += c;
      }
      
      if (cursorX + tft.textWidth(currentLine + word, fontSize) > width) {
        // Draw the current line and move to the next
        tft.drawString(currentLine, cursorX, cursorY);
        cursorY += lineHeight;
        cursorX = x;
        currentLine = word + " ";
      } else {
        currentLine += word + " ";
      }
      word = "";
    } else {
      word += c;
    }
  }

  // Draw any remaining text
  if (currentLine.length() > 0) {
    tft.drawString(currentLine, cursorX, cursorY);
  }
}


void displayNextRssFeed() {
    String headline = sanitizeString(CTAAlerts_Array[currentIndex]["Headline"].as<String>());
    String shortDescription = sanitizeString(CTAAlerts_Array[currentIndex]["ShortDescription"].as<String>());
    Serial.println(headline);
    Serial.println(shortDescription);

    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 0, 320, 100, TFT_BLUE);
    tft.setTextColor(TFT_WHITE, TFT_BLUE);

    displayWrappedText(headline, 5, 5, 300, 4);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    displayWrappedText(shortDescription, 5, 110, 300, 2);

    currentIndex++;

    if (currentIndex >= arrayLength) {
        currentIndex = 0;
    }
}