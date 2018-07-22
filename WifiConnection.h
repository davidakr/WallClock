#ifndef WifiConnection_h
#define WifiConnection_h

#include "WiFiManager.h"
#include "Arduino.h"
#include "ESP8266mDNS.h" 
#include "ESP8266WiFi.h"

 
class WifiConnection {
  public:
    int pinWifiLed = 16;
    WiFiManager wifiManager;
    void Start();
};

#endif
