// #include "positions.h"

// const char* ssid = my_ssid;
// const char* password = my_password;
// String apiKey = cta_train_key;
// String apiUrl = cta_train_key;
// String outputType = output_type;

// const int apiTimer = 60000;

// String url = "";

// String estimatedTime(float arrT, float tmst) {
//   int result = int(((arrT - tmst) / 60) + 0.5);
//   if (result <= 1) {
//     return "Due";
//   }
//   String eta = String(result);
//   eta.concat("min");
//   return eta;
// }

// JsonArray getTrainPositions() {
//   WiFiClientSecure client;
//   client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

//   url = apiUrl + "?key=" + apiKey + "&rt=Blue&outputType=JSON";

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
//   DynamicJsonDocument doc(4096);

//   // Deserialize the JSON document
//   DeserializationError error = deserializeJson(doc, payload);

//   if (error) {
//       Serial.print("Deserialization failed: ");
//       Serial.println(error.c_str());
//       DynamicJsonDocument emptyDoc(4096); // gnerate an emptyDoc variable
//       return emptyDoc.to<JsonArray>(); // return empty array
//   }

//   // Extract the array
//   JsonArray trainList = doc["ctatt"]["route"][0]["train"].as<JsonArray>();

//   const char* timestamp = doc["ctatt"]["timestamp"];
//   Serial.println("API Call at " + timestamp);

//   // const char* timestamp = doc["ctatt"]["tmst"];
//   // int errorCode = doc["ctatt"]["errCd"];
//   // const char* routeName = doc["ctatt"]["route"][0]["@name"];
//   // const char* trainNumber = doc["ctatt"]["route"][0]["train"][0]["rn"];
//   // const char* nextStationName = doc["ctatt"]["route"][0]["train"][0]["nextStaNm"];

//   // Serial.println(timestamp);
//   // Serial.println(errorCode);
//   // Serial.println(routeName);
//   // Serial.println(trainNumber);

//     return trainList;
// }

// int findIndexOfNextStaId(const char* nextStaId) {
//     for (int i = 0; i < sizeof(mapidList) / sizeof(mapidList[0]); i++) {
//         if (strcmp(mapidList[i].id, nextStaId) == 0) {
//             return i;
//         }
//     }
//     return -1; // Return -1 if not found
// }
