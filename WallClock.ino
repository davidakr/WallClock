//---------------------------------------------------------------------
// WallClock accesible local IP
//---------------------------------------------------------------------
#include "Led.h"
#include "ClockModule.h"
#include "GlobalProperties.h"
#include "PhotocellSensor.h"
#include "WifiConnection.h"
#include "EEPROM.h"

Led led;
ClockModule clockModule;
WifiConnection wifiConnection;
PhotocellSensor photocellSensor;

//global variables
byte STATE_STATUS;
byte BRIGHTNESS_STATUS;
byte BRIGHTNESS_VALUE;
byte RED_RGB;
byte GREEN_RGB;
byte BLUE_RGB;
byte TEMPERATURE;
byte FADE_STATUS;
byte PARTY_STATUS;
byte TIMEZONE;
byte TIMER_VALUE = 300;

//address space for EEPROM
int addr_red = 0;
int addr_green = 2;
int addr_blue = 4;
int addr_state_status = 6;
int addr_brightness_status = 8;
int addr_brightness = 10;
int addr_timezone = 12;
int addr_fade_status = 14;
int addr_party_status = 16;

//update time
int updateHours = 4;
int updateMinutes = 0;
int updateSeconds = 0;

//timer variables
unsigned long previousMillis = 0;
const long intervalLED = 250;
unsigned long timestamp = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("WallClock");
  EEPROM.begin(512);

  // get initial values from EEPROM
  byte STATE_STATUS = EEPROM.read(addr_state_status);
  byte BRIGHTNESS_STATUS = EEPROM.read(addr_brightness_status);
  byte BRIGHTNESS_VALUE = EEPROM.read(addr_brightness);
  byte RED_RGB = EEPROM.read(addr_red);
  byte GREEN_RGB = EEPROM.read(addr_green);
  byte BLUE_RGB = EEPROM.read(addr_blue);
  byte FADE_STATUS = EEPROM.read(addr_fade_status);
  byte PARTY_STATUS = EEPROM.read(addr_party_status);
  //TIMEZONE = EEPROM.read(addr_timezone);
  byte TIMEZONE = 1;

  //general setup
  led.Setup();
  wifiConnection.Start();
  clockModule.Setup();
  clockModule.getNTP();
}

void loop() {
  wifiConnection.WifiTraffic();
  yield();
  if (!BRIGHTNESS_STATUS) {
    int newValue = photocellSensor.readPhotocell();
    if (millis() - timestamp > 500) {
      timestamp = millis();
      int diffValue = abs(newValue - BRIGHTNESS_VALUE);
      if (diffValue > 5) {
        BRIGHTNESS_VALUE = newValue;
      }
    }
  }
  yield();
  led.setLedTime(clockModule.getSeconds(), clockModule.getMinutes(), clockModule.getHours());
  yield();
  //update time from ntp
  if (clockModule.getHours() == updateHours && clockModule.getMinutes() == updateMinutes && clockModule.getSeconds() == updateSeconds) {
    int bufferHour = clockModule.getHours();
    int lowerBound = bufferHour - 2;
    int upperBound = bufferHour + 2;
    clockModule.getNTP();
    while (clockModule.getHours() < lowerBound && clockModule.getHours() > upperBound) {
      clockModule.getNTP();
    }
  }
  yield();
  //Serial.println(ESP.getFreeHeap(), DEC);
}
