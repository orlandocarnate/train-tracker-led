#ifndef POSITIONS_H
#define POSITIONS_H

#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// #include <Arduino.h>
// #include <TimeLib.h>
// #include <JSONVar.h>
// #include <JSON.h>

// #include "creds.h"
#define LCD1602_SDA 21
#define LCD1602_SCL 22

static const char* rss_blue_line = "https://www.transitchicago.com/api/1.0/alerts.aspx?routeid=blue&outputType=JSON";

#endif