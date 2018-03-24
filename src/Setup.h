#ifndef Setup_h
#define Setup_h

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include "ESP8266mDNS.h"
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <Ticker.h>
#include <Wire.h>
#include <pgmspace.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <TimeLib.h>
#include <DHTesp.h>

/* Common private libraries */
#include <ntpLib.h>
#include <ledLib.h>
#include <wifiLib.h>
#include <spiffsLib.h>

/* globals.h contains defines and global variables */
#include "globals.h"
/* functions.h contains all function declarations */
#include "functions.h"

#endif
