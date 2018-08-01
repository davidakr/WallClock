#include "PhotocellSensor.h"

int PhotocellSensor::readPhotocell() {
  int sum = 0;
  int sizeArray = sizeof(avgPhoto)/sizeof(int);
  //move up
  for (int i = sizeArray - 1; i > 0; i--) {    
    avgPhoto[i]  = avgPhoto[i - 1];   
  }
  avgPhoto[0] = analogRead(photocellPin);
  //get average
  for (int i = 0; i < sizeArray; i++) {      
     sum += avgPhoto[i];
  }
  return sum/sizeArray;
}
