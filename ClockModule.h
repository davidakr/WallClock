#ifndef ClockModule_h
#define ClockeModule_h

#include "Wire.h"

class ClockModule {
public:
  int hour_;
  int minute_;
  int second_;
  int offset;
  void Setup();
};

#endif
