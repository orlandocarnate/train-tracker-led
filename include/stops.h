#ifndef STOPS_H
#define STOPS_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "stops.h"

struct Stop {
    const char* name;
    const char* stopId;
};

extern const Stop stopList[];

#endif