//---------------------------------------------------------------------
// WallClock accesible via clock.local/ or local IP
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

//timer variables
unsigned long previousMillis = 0;        
const long intervalLED = 250; 


void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  Serial.println("WallClock");

  led.Setup();
  wifiConnection.Start();
  clockModule.Setup();
  clockModule.setClockModule();

  // get initial values from EEPROM
  STATE_STATUS = EEPROM.read(addr_STATE_STATUS);
  BRIGHTNESS_STATUS = EEPROM.read(addr_BRIGHTNESS_STATUS);
  BRIGHTNESS_VALUE = EEPROM.read(addr_brightness);
  TIMEZONE = EEPROM.read(addr_timezone);
  RED_RGB = EEPROM.read(addr_red);
  GREEN_RGB = EEPROM.read(addr_green);
  BLUE_RGB = EEPROM.read(addr_blue);
}

void loop() {
   wifiConnection.WifiTraffic();

   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= intervalLED){
      previousMillis = currentMillis;
      if(BRIGHTNESS_STATUS == 1){ 
        BRIGHTNESS_VALUE = photocellSensor.readPhotocell();       
      }else{      
         
      }
   }
   //need to request time in the night

   
}



