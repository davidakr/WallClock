#include "WifiConnection.h"

WifiConnection::WifiConnection(): server(80) {
  pinMode(pinWifiLed, OUTPUT);
}

void WifiConnection::Start() {
  WiFi.mode(WIFI_STA);
  wifiManager.setConfigPortalBlocking(false);
  wifiManager.setConfigPortalTimeout(120);
  //wifiManager.setBreakAfterConfig(true);

  if (wifiManager.autoConnect("LedClock")) {
    Serial.println("Connected via autoConnect");
  } 
  else {
    wifiManager.startConfigPortal();
    Serial.println("Configportal running");
    //ESP.restart();
  }
  Serial.println("Local IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
}

void WifiConnection::WifiTraffic() {
  wifiManager.process();
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
  root["FADE_STATUS"] = FADE_STATUS;
  root["PARTY_STATUS"] = PARTY_STATUS;
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
    client.stop();
    return false;
  }
  //---------------------------------------------------------------------
  htmlPtr = 0;
  my_char = 0;
  char HTML_String[1000];
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

  if (strstr (HTML_String, "RED_RGB")) {
    RED_RGB = PickParameter("RED_RGB=", HTML_String);
    EEPROM.write(addr_red, RED_RGB);
    boolCommit = true;
  }
  if (strstr (HTML_String, "GREEN_RGB")) {
    GREEN_RGB = PickParameter("GREEN_RGB=", HTML_String);
    EEPROM.write(addr_green, GREEN_RGB);
    boolCommit = true;
  }
  if (strstr (HTML_String, "BLUE_RGB")) {
    BLUE_RGB = PickParameter("BLUE_RGB=", HTML_String);
    EEPROM.write(addr_blue, BLUE_RGB);
    boolCommit = true;
  }

  if (strstr (HTML_String, "STATE_STATUS")) {
    STATE_STATUS = PickParameter("STATE_STATUS=", HTML_String);
    EEPROM.write(addr_state_status, STATE_STATUS);
    boolCommit = true;
  }
  if (strstr (HTML_String, "TIMEZONE")) {
    TIMEZONE = PickParameter("TIMEZONE=", HTML_String);
    EEPROM.write(addr_timezone, TIMEZONE);
    boolCommit = true;
  }
  if (strstr (HTML_String, "BRIGHTNESS_STATUS")) {
    BRIGHTNESS_STATUS = PickParameter("BRIGHTNESS_STATUS=", HTML_String);
    EEPROM.write(addr_brightness_status, BRIGHTNESS_STATUS);
    boolCommit = true;
  }
  if (strstr (HTML_String, "BRIGHTNESS_VALUE")) {
    BRIGHTNESS_VALUE = PickParameter("BRIGHTNESS_VALUE=", HTML_String);
    EEPROM.write(addr_brightness, BRIGHTNESS_VALUE);
    boolCommit = true;
  }
  if (strstr (HTML_String, "FADE_STATUS")) {
    FADE_STATUS = PickParameter("FADE_STATUS=", HTML_String);
    EEPROM.write(addr_fade_status, FADE_STATUS);
    boolCommit = true;
  }
  if (strstr (HTML_String, "PARTY_STATUS")) {
    PARTY_STATUS = PickParameter("PARTY_STATUS=", HTML_String);
    EEPROM.write(addr_party_status, PARTY_STATUS);
    boolCommit = true;
  }

  if (boolCommit == true) {
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
  if (WiFi.status() == WL_CONNECTED) {
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
