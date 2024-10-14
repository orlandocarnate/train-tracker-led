#ifndef POSITIONS_H
#define POSITIONS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <TimeLib.h>
#include <JSONVar.h>
#include <JSON.h>

#include "creds.h"

struct TrainDirection {
    int id;
    const char* name;
};

extern const TrainDirection directions[] = {
    {1, "O'Hare-bound"},
    {5, "Forest Park-bound"}
};

struct Stop {
    const char* id;
    const char* name;
};

JSONVar getTrainPositions();

// for mapId Parent Stop
extern const Stop mapidList[] = {
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
extern const Stop stpidList[] = {
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

int findIndexOfNextStaId(const char* nextStaId);

#endif