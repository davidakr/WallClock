#ifndef Led_h
#define Led_h

#include "Adafruit_NeoPixel.h"
#include "GlobalProperties.h"
 
class Led {
  public:
    void Setup();
  private:    
    int pinLeds = 0;
    int numberLeds = 130;
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numberLeds, pinLeds, NEO_RGB + NEO_KHZ800);
    void setLedPixel(int arrayInt[], int arraySize, int toAdd, int red, int green, int blue, int brightness);
    boolean arrayIncludeElement(int arrayInt[], int element);
    void setLedTime(int Red, int Blue, int Green);

    //Numbers for Led Display
    int all[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int zero [18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    int one[9] = { 0, 1, 2, 0, 1, 2, 15, 16, 17};
    int two[15] = { 0, 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 18, 19, 20};
    int three[15] = { 0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int four[12] = { 0, 1, 2, 6, 7, 8, 15, 16, 17, 18, 19, 20};
    int five[15] = {3, 4, 5, 6, 7, 8, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int six[18] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int seven[9] = { 0, 1, 2, 3, 4, 5, 15, 16, 17};
    int eight[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int nine[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int dot[2] = {0,1};
};

#endif
