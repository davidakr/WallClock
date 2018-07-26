#ifndef WifiConnection_h
#define WifiConnection_h

#include "WiFiManager.h"
#include "Arduino.h"
#include "ESP8266mDNS.h" 
#include "ArduinoJson.h"
#include "BufferedPrint.h"
#include "GlobalProperties.h"
 
class WifiConnection {
  public:
    WifiConnection();
    int pinWifiLed = 16;
    int STATE_BRIGHTNESS = 1;
    int STATE_STATUS = 1;
    char HTML_String[5000];
    WiFiManager wifiManager;
    WiFiServer server;
    WiFiClient client;
    void beginWifi();
    void Start();
    void WifiTraffic();
    JsonObject& prepareResponse(JsonBuffer& jsonBuffer);
    bool readRequest(WiFiClient& client);
    int FindStart(const char * such, const char * str);
    int FindEnd(const char * such, const char * str);
    int PickDec(const char * tx, int idx );
    int PickParameter(const char * par, char * str);
    void sendNotFound();
};

#endif
