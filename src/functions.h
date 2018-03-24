#ifndef functions_h
#define functions_h

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//Function definitions

// Timer trigger functions
void triggerGetLDR();
void triggerHeartBeat();

// Sensor functions
boolean getLDR();
void pirTrigger();

// Actuator functions
void relayOff();

// Device status functions
void createStatus(JsonObject& root, boolean makeShort);
bool writeStatus();
bool readStatus();

// Communication functions
void sendAlarm(boolean makeShort);
void socketServer(WiFiClient tcpClient);
void sendLightStatus(boolean switchOn);
void triggerPic();
void triggerVid(int cameraNum);
void initOTA();
#endif
