//---------------------------------------------------------------------
//WallClock
//---------------------------------------------------------------------
#include "Led.h"
#include "ClockModule.h"
#include "ColorProperties.h"
#include "PhotocellSensor.h"
#include "WifiConnection.h"

Led led;
ClockModule clockModule;
ColorProperties colorProperties;
WifiConnection wifiConnection;

void setup() {
  Serial.begin(115200);
  Serial.println("WallClock");
  
  led.Setup();
  clockModule.Setup();
  wifiConnection.Start();
}

void loop() {
  
}

