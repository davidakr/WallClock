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

//address for EEPROM
int addr_red = 0;
int addr_green = 2;
int addr_blue = 4;
int addr_STATE_STATUS = 6;
int addr_BRIGHTNESS_STATUS = 8;
int addr_brightness = 10;
int addr_timezone = 12;

//global variables
int RED_RGB;
int GREEN_RGB;
int BLUE_RGB;
int BRIGHTNESS_VALUE;
int BRIGHTNESS_STATUS;
int STATE_VALUE;
int STATE_STATUS;
int TIMEZONE;
int TEMPERATURE;

//update time
int updateHours = 4;
int updateMinutes = 0;
int updateSeconds = 0;

//timer variables
unsigned long previousMillis = 0;
const long intervalLED = 250;
unsigned long timestamp = 0;


void setup() {
  led.Setup();
  EEPROM.begin(512);
  Serial.begin(115200);
  Serial.println("WallClock");

  // get initial values from EEPROM
  STATE_STATUS = EEPROM.read(addr_STATE_STATUS);
  BRIGHTNESS_STATUS = EEPROM.read(addr_BRIGHTNESS_STATUS);
  BRIGHTNESS_VALUE = EEPROM.read(addr_brightness);
  RED_RGB = EEPROM.read(addr_red);
  GREEN_RGB = EEPROM.read(addr_green);
  BLUE_RGB = EEPROM.read(addr_blue);
  //TIMEZONE = EEPROM.read(addr_timezone);
  TIMEZONE = 1;

  //general setup
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
      if(diffValue > 5){
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
}
