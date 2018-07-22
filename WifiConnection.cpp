#include "WifiConnection.h"

void WifiConnection::Start() {
  pinMode(pinWifiLed, OUTPUT);
  WiFiServer server(80);
  wifiManager.setBreakAfterConfig(true);
 
  if (!wifiManager.autoConnect("WallClock", "")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("Local IP address: ");
  Serial.println(WiFi.localIP());
  
  if (!MDNS.begin("clock")) {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000); 
    }
  }
  Serial.println("mDNS responder started");
  server.begin();
  Serial.println("Server started");
  MDNS.addService("http", "tcp", 80);
}
