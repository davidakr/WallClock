#include "Led.h"

void Led::Setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(255);
  pixels.show();
  Serial.println("Leds initialized");
}
