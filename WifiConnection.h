#ifndef WifiConnection_h
#define WifiConnection_h


#include "WiFiManager.h"
#include "Arduino.h"
#include "ArduinoJson.h"
#include "BufferedPrint.h"
#include "GlobalProperties.h"
#include "EEPROM.h"
#include "ESP8266WebServer.h"
#include "ESP8266WiFi.h"

class WifiConnection {
  public:
    WifiConnection();
    void beginWifi();
    void Start();
    void WifiTraffic();
    void setLED();

  private:
    int pinWifiLed = 16;
    char HTML_String[5000];
    WiFiManager wifiManager;
    WiFiServer server;
    WiFiClient client;
    JsonObject& prepareResponse(JsonBuffer& jsonBuffer);
    bool readRequest(WiFiClient& client);
    int FindStart(const char * such, const char * str);
    int FindEnd(const char * such, const char * str);
    int PickDec(const char * tx, int idx );
    int PickParameter(const char * par, char * str);
    void sendNotFound();
};

#endif
