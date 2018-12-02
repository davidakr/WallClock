#include "PhotocellSensor.h"

int PhotocellSensor::readPhotocell() {
  int sum = 0;
  int sizeArray = sizeof(avgPhoto)/sizeof(int);
  for (int i = sizeArray - 1; i > 0; i--) {    
    avgPhoto[i]  = avgPhoto[i - 1];   
  }
  int analogValue = (analogRead(photocellPin)-5)/4;
  avgPhoto[0] = max(calculateValue(analogValue), minValue);
  for (int i = 0; i < sizeArray; i++) {      
     sum += avgPhoto[i];
  }
  return sum/sizeArray;
}

int PhotocellSensor::calculateValue (int number) {
  return number*number/255;
}

