#ifndef STOPS_H
#define STOPS_H

struct Stop {
    const char* name;
    const char* stopId;
};

extern const Stop stopList[];

#endif