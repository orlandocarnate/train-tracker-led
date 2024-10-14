#include "positions.h"

const char* ssid = my_ssid;
const char* password = my_password;
String apiKey = cta_train_key;
String apiUrl = cta_train_key;
String outputType = output_type;

// for mapId Parent Stop
const Stop mapidList[] = {
    {"40390", "Forest Park"},
    {"40980", "Harlem (Forest Park Branch)"},
    {"40180", "Oak Park"},
    {"40010", "Austin"},
    {"40970", "Cicero"},
    {"40920", "Pulaski"},
    {"40250", "Kedzie-Homan"},
    {"40220", "Western (Forest Park Branch)"},
    {"40810", "Illinois Medical District"},
    {"40470", "Racine"},
    {"40350", "UIC-Halsted"},
    {"40430", "Clinton"},
    {"41340", "LaSalle"},
    {"40070", "Jackson"},
    {"40790", "Monroe"},
    {"40370", "Washington"},
    {"40380", "Clark/Lake"},
    {"40490", "Grand"},
    {"41410", "Chicago"},
    {"40320", "Division"},
    {"40590", "Damen"},
    {"40670", "Western (O'Hare Branch)"},
    {"40570", "California"},
    {"41020", "Logan Square"},
    {"40060", "Belmont"},
    {"41240", "Addison"},
    {"40550", "Irving Park"},
    {"41330", "Montrose"},
    {"41280", "Jefferson Park"},
    {"40750", "Harlem (O'Hare Branch)"},
    {"40230", "Cumberland"},
    {"40820", "Rosemont"},
    {"40890", "O'Hare"},
};


// for individual stops
const Stop stpidList[] = {
    {"40390", "Forest Park"},

    {"40980", "Harlem (Forest Park Branch)"},
    {"40180", "Oak Park"},
    {"40010", "Austin"},
    {"40970", "Cicero"},
    {"40920", "Pulaski"},
    {"40250", "Kedzie-Homan"},
    {"40220", "Western (Forest Park Branch)"},
    {"40810", "Illinois Medical District"},
    {"40470", "Racine"},
    {"30092", "UIC-Halsted"},
    {"30093", "UIC-Halsted"},
    {"40430", "Clinton"},
    {"41340", "LaSalle"},
    {"40070", "Jackson"},
    {"40790", "Monroe"},
    {"40370", "Washington"},
    {"40380", "Clark/Lake"},
    {"40490", "Grand"},
    {"41410", "Chicago"},
    {"40320", "Division"},
    {"40590", "Damen"},
    {"40670", "Western (O'Hare Branch)"},
    {"40570", "California"},
    {"41020", "Logan Square"},
    {"40060", "Belmont"},
    {"41240", "Addison"},
    {"40550", "Irving Park"},
    {"41330", "Montrose"},
    {"41280", "Jefferson Park"},
    {"40750", "Harlem (O'Hare Branch)"},
    {"40230", "Cumberland"},
    {"40820", "Rosemont"},
    {"40890", "O'Hare"},
};

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

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

String readResponse(WiFiClientSecure& client) {
  String response = "";
  while (client.connected() || client.available()) {
    if (client.available()) {
      response += client.readString();
    }
  }
  return response;
}


JSONVar jsonParser(String apiPath) {
  // Serial.println(apiPath);
  Serial.println("Initiated API Call to " + apiPath);
  String jsonBuffer = httpGETRequest(apiPath.c_str());
  // Serial.println(jsonBuffer);

  return JSON.parse(jsonBuffer);
}

JSONVar getTrainPositions() {
  WiFiClientSecure client;
  client.setInsecure(); // Use this for testing purposes only. For production, you should use proper certificate validation.

  url = apiUrl + "?key=" + apiKey + "&rt=Blue&outputType=JSON";

  JSONVar dataObject = jsonParser(url);

  if (JSON.typeof(url) == "undefined") {
    Serial.println("Parsing Input " + url + " failed!");
    return JSONVar(); // return empty object
  }

  const char* timestamp = dataObject["ctatt"]["timestamp"];
  JSONVar trainList = dataObject["ctatt"]["route"][0]["train"];

  // const char* timestamp = doc["ctatt"]["tmst"];
  // int errorCode = doc["ctatt"]["errCd"];
  // const char* routeName = doc["ctatt"]["route"][0]["@name"];
  // const char* trainNumber = doc["ctatt"]["route"][0]["train"][0]["rn"];
  // const char* nextStationName = doc["ctatt"]["route"][0]["train"][0]["nextStaNm"];

  // Serial.println(timestamp);
  // Serial.println(errorCode);
  // Serial.println(routeName);
  // Serial.println(trainNumber);

    return trainList;
}


