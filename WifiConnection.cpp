#include "WifiConnection.h"

WifiConnection::WifiConnection():server(80) {
  pinMode(pinWifiLed, OUTPUT);
}

void WifiConnection::Start() {
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

void WifiConnection::WifiTraffic() {
  setLED(); 
  WiFiClient client = server.available();
  if (client) {
    bool success = readRequest(client);
    if (success) {
      // Use https://bblanchon.github.io/ArduinoJson/assistant/ to
      // compute the right size for the buffer
      StaticJsonBuffer<450> jsonBuffer;      
      JsonObject& json = prepareResponse(jsonBuffer);
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Access-Control-Allow-Origin: *");
      client.println("Connection: close");
      client.println();
             
      BufferedPrint<450> bufferedPrint(client);
      json.printTo(bufferedPrint);
    }
    delay(1);   
  } else {
    client.stop();  
  }
}

JsonObject& WifiConnection::prepareResponse(JsonBuffer& jsonBuffer) {
  JsonObject& root = jsonBuffer.createObject();

  root["NAME"] = "WallClock";
  root["STATE_STATUS"] = STATE_STATUS;
  root["RED_RGB"] = RED_RGB;
  root["GREEN_RGB"] = GREEN_RGB;
  root["BLUE_RGB"] = BLUE_RGB;
  root["BRIGHTNESS_STATUS"] = BRIGHTNESS_STATUS;
  root["BRIGHTNESS_VALUE"] = BRIGHTNESS_VALUE;
  root["TIMEZONE"] = TIMEZONE;
  root["TEMPERATURE"] = TEMPERATURE;
//  root["HOUR"] = Clock.getHour(h12, PM);
//  root["MINUTE"] = Clock.getMinute();
//  root["SECOND"] =  Clock.getSecond();
     
  return root;
}
 
bool WifiConnection::readRequest(WiFiClient& client) { 
    char my_char;
    int htmlPtr = 0;
    int myIdx;
    int myIndex;
    unsigned long my_timeout;
    bool boolCommit = false;;
    // Check if a client has connected
    if (!client)  {
      return false;
    }
    my_timeout = millis() + 250L;
    while (!client.available() && (millis() < my_timeout) ) delay(10);
    delay(10);
    if (millis() > my_timeout)  {
      return false;     
    }
    //---------------------------------------------------------------------
    htmlPtr = 0;
    my_char = 0;
    while (client.available() && my_char != '\r') {
      my_char = client.read();
      HTML_String[htmlPtr++] = my_char;
    }
    client.flush();
    HTML_String[htmlPtr] = 0;
    #ifdef BGTDEBUG
      exhibit ("Request : ", HTML_String);
    #endif
    if (FindStart ("/?", HTML_String) < 0 && FindStart ("GET / HTTP", HTML_String) < 0 ) {
      sendNotFound();
      return false;
    }
    String HTML(HTML_String);

    if(HTML.indexOf("RED_RGB") > 0){
      RED_RGB = PickParameter("RED_RGB=", HTML_String);
      EEPROM.write(addr_red, RED_RGB);
      boolCommit = true;
    }
     if(HTML.indexOf("GREEN_RGB") > 0){
      GREEN_RGB = PickParameter("GREEN_RGB=", HTML_String);
      EEPROM.write(addr_green, GREEN_RGB);
      boolCommit = true;
    }
     if(HTML.indexOf("BLUE_RGB") > 0){
      BLUE_RGB = PickParameter("BLUE_RGB=", HTML_String);
      EEPROM.write(addr_blue, BLUE_RGB);
      boolCommit = true;
    }
    
    if(HTML.indexOf("STATE_STATUS") > 0){
      STATE_STATUS = PickParameter("STATE_STATUS=", HTML_String);
      EEPROM.write(addr_STATE_STATUS, STATE_STATUS);
      boolCommit = true;
    }
    if(HTML.indexOf("TIMEZONE") > 0){
      TIMEZONE = PickParameter("TIMEZONE=", HTML_String);
      EEPROM.write(addr_timezone, TIMEZONE);
      boolCommit = true;
    }
     if(HTML.indexOf("BRIGHTNESS_STATUS") > 0){
      BRIGHTNESS_STATUS = PickParameter("BRIGHTNESS_STATUS=", HTML_String);
      EEPROM.write(addr_BRIGHTNESS_STATUS, BRIGHTNESS_STATUS);
      boolCommit = true;
    }
     if(HTML.indexOf("BRIGHTNESS_VALUE") > 0){
      BRIGHTNESS_VALUE = PickParameter("BRIGHTNESS_VALUE=", HTML_String);      
      EEPROM.write(addr_brightness, BRIGHTNESS_VALUE);
      boolCommit = true;
    }


    if(boolCommit == true){
       EEPROM.commit();   
    }
    return true;
}

int WifiConnection::FindStart(const char * such, const char * str) {
  int tmp = -1;
  int ww = strlen(str) - strlen(such);
  int ll = strlen(such);

  for (int i = 0; i <= ww && tmp == -1; i++) {
    if (strncmp(such, &str[i], ll) == 0) tmp = i;
  }
  return tmp;
} 

void WifiConnection::sendNotFound() {
#ifdef BGTDEBUG
  Serial.println("Sende Not Found");
#endif
  client.print("HTTP/1.1 404 Not Found\r\n\r\n");
  delay(20);
  client.stop();
}

void WifiConnection::setLED() {
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(pinWifiLed, HIGH);
  } else {
    digitalWrite(pinWifiLed, LOW);
  }
}



int WifiConnection::PickParameter(const char * par, char * str) {
  int myIdx = FindEnd(par, str);

  if (myIdx >= 0) return  PickDec(str, myIdx);
  else return -1;
}

int WifiConnection::FindEnd(const char * such, const char * str) {
  int tmp = FindStart(such, str);
  if (tmp >= 0)tmp += strlen(such);
  return tmp;
}


int WifiConnection::PickDec(const char * tx, int idx ) {
  int tmp = 0;

  for (int p = idx; p < idx + 5 && (tx[p] >= '0' && tx[p] <= '9') ; p++) {
    tmp = 10 * tmp + tx[p] - '0';
  }
  return tmp;
}
