#ifndef Led_h
#define Led_h

#include "Adafruit_NeoPixel.h"
 
class Led {
  public:
    int red;
    int blue;
    int green;
    int brightness;
    
    int pinLeds = 0;
    int numberLeds = 130;
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numberLeds, pinLeds, NEO_RGB + NEO_KHZ800);
    void Setup();
};

#endif
