#ifndef POSITIONS_H
#define POSITIONS_H

// #include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
// #include <TimeLib.h>
// #include <JSONVar.h>
// #include <JSON.h>

#include "creds.h"
#include "leds.h"

struct TrainDirection {
    int id;
    const char* name;
};

const TrainDirection directions[] = {
    {1, "O'Hare-bound"},
    {5, "Forest Park-bound"}
};

struct Station {
    const char* id;
    const char* name;
};
struct Stop {
    const char* id;
    const char* direction;
    const char* name;
};

// JsonArray getTrainPositions();

// for mapId Parent Stop
const Station mapidList[] = {
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
    {"30076", "E", "Forest Park"},
    {"30189", "E", "Harlem (Forest Park Branch)"},
    {"30034", "E", "Oak Park"},
    {"30001", "E", "Austin"},
    {"30187", "E", "Cicero"},
    {"30179", "E", "Pulaski"},
    {"30048", "E", "Kedzie-Homan"},
    {"30042", "E", "Western (Forest Park Branch)"},
    {"30157", "E", "Illinois Medical District"},
    {"30092", "E", "Racine"},
    {"30068", "E", "UIC-Halsted"},
    {"30084", "E", "Clinton"},
    {"30261", "E", "LaSalle"},
    {"30014", "N", "Jackson"},
    {"30153", "N", "Monroe"},
    {"30072", "N", "Washington"},
    {"30375", "N", "Clark/Lake"},
    {"30095", "N", "Grand"},
    {"30271", "N", "Chicago"},
    {"30062", "N", "Division"},
    {"30115", "N", "Damen"},
    {"30129", "N", "Western (O'Hare Branch)"},
    {"30111", "N", "California"},
    {"30197", "N", "Logan Square"},
    {"30012", "N", "Belmont"},
    {"30239", "N", "Addison"},
    {"30107", "N", "Irving Park"},
    {"30259", "N", "Montrose"},
    {"30247", "N", "Jefferson Park"},
    {"30145", "N", "Harlem (O'Hare Branch)"},
    {"30044", "N", "Cumberland"},
    {"30159", "N", "Rosemont"},
    {"30171", "N", "O'Hare"},

    {"30172", "S", "O'Hare"},
    {"30160", "S", "Rosemont"},
    {"30045", "S", "Cumberland"},
    {"30146", "S", "Harlem (O'Hare Branch)"},
    {"30248", "S", "Jefferson Park"},
    {"30260", "S", "Montrose"},
    {"30108", "S", "Irving Park"},
    {"30240", "S", "Addison"},
    {"30013", "S", "Belmont"},
    {"30198", "S", "Logan Square"},
    {"30112", "S", "California"},
    {"30130", "S", "Western (O'Hare Branch)"},
    {"30116", "S", "Damen"},
    {"30063", "S", "Division"},
    {"30272", "S", "Chicago"},
    {"30096", "S", "Grand"},
    {"30374", "S", "Clark/Lake"},
    {"30073", "S", "Washington"},
    {"30154", "S", "Monroe"},
    {"30015", "S", "Jackson"},
    {"30262", "W", "LaSalle"},
    {"30085", "W", "Clinton"},
    {"30069", "W", "UIC-Halsted"},
    {"30093", "W", "Racine"},
    {"30158", "W", "Illinois Medical District"},
    {"30043", "W", "Western (Forest Park Branch)"},
    {"30049", "W", "Kedzie-Homan"},
    {"30188", "W", "Cicero"},
    {"30002", "W", "Austin"},
    {"30035", "W", "Oak Park"},
    {"30190", "W", "Harlem (Forest Park Branch)"},
    {"30077", "W", "Forest Park"},

};

int findIndexOfNextStaId(const char* nextStaId);
void updateTrainPositions();

#endif