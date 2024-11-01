#ifndef RSS_H
#define RSS_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include "Free_Fonts.h"


static const char* rss_blue_line = "https://www.transitchicago.com/api/1.0/alerts.aspx?routeid=blue&outputType=JSON";

void setupTftLcd();
void updateRssData();
void displayNextRssFeed();

#endif