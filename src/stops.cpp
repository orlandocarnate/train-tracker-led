#include "stops.h"

const Stop stopList[] = {
    {"Racine", "40470"},
    {"UIC-Halsted (Blue)", "40350"},
};

String url = "";

setup() {
    // Allocate a temporary JsonDocument
  StaticJsonDocument<1024> 
}


String makeApiCall(const char* url) {
    HTTPClient http;
    http.begin(url); // Your API URL
    int httpCode = http.GET();

    String payload = "";
    if (httpCode > 0) {
        payload = http.getString();
    } else {
        Serial.println("Error on HTTP request");
    }

    http.end();
    return payload;
};

void parseData() {
    String response = makeApiCall(url);
    StaticJsonDocument<1024> doc;

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    const char* timestamp = doc["ctatt"]["tmst"];
    int errorCode = doc["ctatt"]["errCd"];
    const char* routeName = doc["ctatt"]["route"][0]["@name"];
    const char* trainNumber = doc["ctatt"]["route"][0]["train"][0]["rn"];
    const char* nextStationName = doc["ctatt"]["route"][0]["train"][0]["nextStaNm"];

    Serial.println(timestamp);
    Serial.println(errorCode);
    Serial.println(routeName);
    Serial.println(trainNumber);
    Serial.println
}


