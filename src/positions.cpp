#include "positions.h"

String apiKey = cta_train_key;
String apiUrl = train_positions_url;
String outputType = output_type;


JsonDocument positionDoc; // Create JSON document to hold the parsed data
JsonObject positionsObj;
JsonArray positionsArray;

const int apiTimer = 60000;

String url = "";

String estimatedTime(float arrT, float tmst) {
  int result = int(((arrT - tmst) / 60) + 0.5);
  if (result <= 1) {
    return "Due";
  }
  String eta = String(result);
  eta.concat("min");
  return eta;
}

void updateTrainPositions() {
  WiFiClientSecure client;
  client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

  url = apiUrl + "?key=" + apiKey + "&rt=Blue" + outputType;

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

  
  

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(positionDoc, payload);

  if (error) {
      Serial.print("Deserialization failed: ");
      Serial.println(error.c_str());
    //   DynamicJsonDocument emptyDoc(4096); // gnerate an emptyDoc variable
    //   return emptyDoc.to<JsonArray>(); // return empty array
    return;
  }

  // Extract the array
  positionsObj = positionDoc["ctatt"];
  const char* ctatt_tmst = positionsObj["tmst"]; // "2024-10-14T10:32:41"
  const char* ctatt_errCd = positionsObj["errCd"]; // "0"

  const char* timestamp = positionDoc["ctatt"]["timestamp"];
  Serial.println("API Call at " + String(timestamp));

  const char* ctatt_route_0_name = positionsObj["route"][0]["@name"]; // "blue"

  // Extract the array
  positionsArray = positionDoc["ctatt"]["route"][0]["train"].as<JsonArray>();

  clearLEDS();

  for (JsonObject item : positionsArray) {

        const char* nextStaId = item["nextStaId"]; // "40180", ...
        const char* nextStpId = item["nextStpId"]; // "30034", ...
        const char* arrT = item["arrT"]; // "2024-10-14T10:33:26", ...
        const char* isApp = item["isApp"]; // "1", "0", "0", "0", ...
        const char* isDly = item["isDly"]; // "0", "0", "0", "0", ...

        Serial.print("Next Station: ");
        Serial.println(nextStaId);
        Serial.print("Next Stop: ");
        Serial.println(nextStpId);
        Serial.print("Arrival Time: ");
        Serial.println(arrT);
        Serial.print("Is Approaching: ");
        Serial.println(isApp);
        Serial.print("Is Delayed: ");
        Serial.println(isDly);

        updateLEDs(nextStpId, isApp, isDly);

    }

    showLEDS();


}

int findIndexOfNextStaId(const char* nextStaId) {
    for (int i = 0; i < sizeof(stpidList) / sizeof(stpidList[0]); i++) {
        if (strcmp(stpidList[i].id, nextStaId) == 0) {
            return i;
        }
    }
    return -1; // Return -1 if not found
}
