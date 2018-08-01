#ifndef PhotoCellSensor_h
#define PhotoCellSensor_h

#include "Arduino.h"

class PhotocellSensor {
public:
  int readPhotocell();
private:
  int photocellPin = A0;     
  int avgPhoto[3]= {0, 0, 0};
};

#endif
