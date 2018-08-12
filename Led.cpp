#include "Led.h"

void Led::Setup() {
  delay(2000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_VALUE);
  Serial.println("Leds initialized");
}

void Led::setLedPixel(int arrayInt[], int arraySize, int toAdd, int red, int green, int blue, int brightness) {   
  for (int i=0; i < arraySize; i++){
    leds[arrayInt[i] + toAdd].setRGB( RED_RGB, GREEN_RGB, BLUE_RGB);             
  }      
}

boolean Led::arrayIncludeElement(int arrayInt[], int element) {
  for (int i = 0; i < sizeof(arrayInt); i++) {
    if (arrayInt[i] == element) {
      return true;
    }
  }
  return false;
}

void Led::setLedTime(int Red, int Blue, int Green){
  int sekunde = 1;
  int minuten = 1;
  int stunde = 1;
  TEMPERATURE = 1;
  
  int einerSekunde = sekunde % 10;
  int zehnerSekunde = sekunde / 10;
  int einerMinute = minuten % 10;
  int zehnerMinute = minuten / 10;
  int einerStunde = stunde % 10;
  int zehnerStunde = stunde / 10;
  int ledBrightness = 0;

  FastLED.clear(); 
      
  switch (einerSekunde) {
    case 0: setLedPixel(zero,sizeof(zero)/sizeof(*zero), 0,Red,Green,Blue,ledBrightness); break;
    case 1: setLedPixel(one,sizeof(one)/sizeof(*one), 0,Red,Green,Blue,ledBrightness); break;
    case 2: setLedPixel(two,sizeof(two)/sizeof(*two), 0,Red,Green,Blue,ledBrightness); break; 
    case 3: setLedPixel(three,sizeof(three)/sizeof(*three), 0,Red,Green,Blue,ledBrightness); break; 
    case 4: setLedPixel(four,sizeof(four)/sizeof(*four), 0,Red,Green,Blue,ledBrightness); break; 
    case 5: setLedPixel(five,sizeof(five)/sizeof(*five), 0,Red,Green,Blue,ledBrightness); break; 
    case 6: setLedPixel(six,sizeof(six)/sizeof(*six), 0,Red,Green,Blue,ledBrightness); break; 
    case 7: setLedPixel(seven,sizeof(seven)/sizeof(*seven), 0,Red,Green,Blue,ledBrightness); break; 
    case 8: setLedPixel(eight,sizeof(eight)/sizeof(*eight), 0,Red,Green,Blue,ledBrightness); break;
    case 9: setLedPixel(nine,sizeof(nine)/sizeof(*nine), 0,Red,Green,Blue,ledBrightness); break;     
  }
   switch (zehnerSekunde) {
    case 0: setLedPixel(zero,sizeof(zero)/sizeof(*zero), 21,Red,Green,Blue,ledBrightness); break;
    case 1: setLedPixel(one ,sizeof(one)/sizeof(*one), 21,Red,Green,Blue,ledBrightness); break;
    case 2: setLedPixel(two ,sizeof(two)/sizeof(*two), 21,Red,Green,Blue,ledBrightness); break; 
    case 3: setLedPixel(three,sizeof(three)/sizeof(*three), 21,Red,Green,Blue,ledBrightness); break; 
    case 4: setLedPixel(four,sizeof(four)/sizeof(*four), 21,Red,Green,Blue,ledBrightness); break; 
    case 5: setLedPixel(five,sizeof(five)/sizeof(*five), 21,Red,Green,Blue,ledBrightness); break; 
    case 6: setLedPixel(six ,sizeof(six)/sizeof(*six), 21,Red,Green,Blue,ledBrightness); break; 
    case 7: setLedPixel(seven,sizeof(seven)/sizeof(*seven), 21,Red,Green,Blue,ledBrightness); break; 
    case 8: setLedPixel(eight,sizeof(eight)/sizeof(*eight), 21,Red,Green,Blue,ledBrightness); break;
    case 9: setLedPixel(nine,sizeof(nine)/sizeof(*nine), 21,Red,Green,Blue,ledBrightness); break;     
  }
  
  setLedPixel(dot,sizeof(dot)/sizeof(*dot), 42,Red,Green,Blue,ledBrightness);

  switch (einerMinute) {
    case 0: setLedPixel(zero,sizeof(zero)/sizeof(*zero), 44,Red,Green,Blue,ledBrightness); break;
    case 1: setLedPixel(one,sizeof(one)/sizeof(*one), 44,Red,Green,Blue,ledBrightness); break;
    case 2: setLedPixel(two,sizeof(two)/sizeof(*two), 44,Red,Green,Blue,ledBrightness); break; 
    case 3: setLedPixel(three,sizeof(three)/sizeof(*three), 44,Red,Green,Blue,ledBrightness); break; 
    case 4: setLedPixel(four,sizeof(four)/sizeof(*four), 44,Red,Green,Blue,ledBrightness); break; 
    case 5: setLedPixel(five,sizeof(five)/sizeof(*five), 44,Red,Green,Blue,ledBrightness); break; 
    case 6: setLedPixel(six,sizeof(six)/sizeof(*six), 44,Red,Green,Blue,ledBrightness); break; 
    case 7: setLedPixel(seven,sizeof(seven)/sizeof(*seven), 44,Red,Green,Blue,ledBrightness); break; 
    case 8: setLedPixel(eight,sizeof(eight)/sizeof(*eight), 44,Red,Green,Blue,ledBrightness); break;
    case 9: setLedPixel(nine,sizeof(nine)/sizeof(*nine), 44,Red,Green,Blue,ledBrightness); break;     
  }
   switch (zehnerMinute) {
    case 0: setLedPixel(zero,sizeof(zero)/sizeof(*zero), 65,Red,Green,Blue,ledBrightness); break;
    case 1: setLedPixel(one ,sizeof(one)/sizeof(*one), 65,Red,Green,Blue,ledBrightness); break;
    case 2: setLedPixel(two ,sizeof(two)/sizeof(*two), 65,Red,Green,Blue,ledBrightness); break; 
    case 3: setLedPixel(three,sizeof(three)/sizeof(*three), 65,Red,Green,Blue,ledBrightness); break; 
    case 4: setLedPixel(four,sizeof(four)/sizeof(*four), 65,Red,Green,Blue,ledBrightness); break; 
    case 5: setLedPixel(five,sizeof(five)/sizeof(*five), 65,Red,Green,Blue,ledBrightness); break; 
    case 6: setLedPixel(six ,sizeof(six)/sizeof(*six), 65,Red,Green,Blue,ledBrightness); break; 
    case 7: setLedPixel(seven,sizeof(seven)/sizeof(*seven), 65,Red,Green,Blue,ledBrightness); break; 
    case 8: setLedPixel(eight,sizeof(eight)/sizeof(*eight), 65,Red,Green,Blue,ledBrightness); break;
    case 9: setLedPixel(nine,sizeof(nine)/sizeof(*nine), 65,Red,Green,Blue,ledBrightness); break;     
  }

  setLedPixel(dot,sizeof(dot)/sizeof(*dot), 86,Red,Green,Blue,ledBrightness);

      switch (einerStunde) {
    case 0: setLedPixel(zero,sizeof(zero)/sizeof(*zero), 88,Red,Green,Blue,ledBrightness); break;
    case 1: setLedPixel(one,sizeof(one)/sizeof(*one), 88,Red,Green,Blue,ledBrightness); break;
    case 2: setLedPixel(two,sizeof(two)/sizeof(*two), 88,Red,Green,Blue,ledBrightness); break; 
    case 3: setLedPixel(three,sizeof(three)/sizeof(*three), 88,Red,Green,Blue,ledBrightness); break; 
    case 4: setLedPixel(four,sizeof(four)/sizeof(*four), 88,Red,Green,Blue,ledBrightness); break; 
    case 5: setLedPixel(five,sizeof(five)/sizeof(*five), 88,Red,Green,Blue,ledBrightness); break; 
    case 6: setLedPixel(six,sizeof(six)/sizeof(*six), 88,Red,Green,Blue,ledBrightness); break; 
    case 7: setLedPixel(seven,sizeof(seven)/sizeof(*seven), 88,Red,Green,Blue,ledBrightness); break; 
    case 8: setLedPixel(eight,sizeof(eight)/sizeof(*eight), 88,Red,Green,Blue,ledBrightness); break;
    case 9: setLedPixel(nine,sizeof(nine)/sizeof(*nine), 88,Red,Green,Blue,ledBrightness); break;     
  }
   switch (zehnerStunde) {
    case 0: setLedPixel(zero,sizeof(zero)/sizeof(*zero), 109,Red,Green,Blue,ledBrightness); break;
    case 1: setLedPixel(one ,sizeof(one)/sizeof(*one), 109,Red,Green,Blue,ledBrightness); break;
    case 2: setLedPixel(two ,sizeof(two)/sizeof(*two), 109,Red,Green,Blue,ledBrightness); break; 
    case 3: setLedPixel(three,sizeof(three)/sizeof(*three), 109,Red,Green,Blue,ledBrightness); break; 
    case 4: setLedPixel(four,sizeof(four)/sizeof(*four), 109,Red,Green,Blue,ledBrightness); break; 
    case 5: setLedPixel(five,sizeof(five)/sizeof(*five), 109,Red,Green,Blue,ledBrightness); break; 
    case 6: setLedPixel(six ,sizeof(six)/sizeof(*six), 109,Red,Green,Blue,ledBrightness); break; 
    case 7: setLedPixel(seven,sizeof(seven)/sizeof(*seven), 109,Red,Green,Blue,ledBrightness); break; 
    case 8: setLedPixel(eight,sizeof(eight)/sizeof(*eight), 109,Red,Green,Blue,ledBrightness); break;
    case 9: setLedPixel(nine,sizeof(nine)/sizeof(*nine), 109,Red,Green,Blue,ledBrightness); break;     
  }

  FastLED.setBrightness(BRIGHTNESS_VALUE);
  FastLED.show();
}
