#include "Led.h"

void Led::Setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(0);
  pixels.show();
  Serial.println("Leds initialized");
}

void Led::setLedPixel(int arrayInt[], int arraySize, int toAdd) {
  for (int i = 0 + toAdd; i < 21 + toAdd; i++) {
    if (!arrayIncludeElement(arrayInt, i)) {
      if (pixels.getPixelColor(i) != pixels.Color(0, 0, 0)) {
        pixels.setPixelColor(i, 0, 0, 0);
      }
    }
  }
  if (PARTY_STATUS) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= TIMER_VALUE) {
      previousMillis = currentMillis;
      for (int i = 0; i < sizeof PARTY_BUFFER / sizeof PARTY_BUFFER[0]; i++) {
        PARTY_BUFFER[i][0] = byte(random(0, 255));
        PARTY_BUFFER[i][1] = byte(random(0, 255));
        PARTY_BUFFER[i][2] = byte(random(0, 255));
      }
    }
    if(toAdd > 87){
      Serial.print(PARTY_BUFFER[toAdd][0]);
      Serial.print("-");
      Serial.print(PARTY_BUFFER[toAdd][1]);
      Serial.print("-");
      Serial.println(PARTY_BUFFER[toAdd][2]);
    }
    for (int i = 0; i < arraySize; i++) {
      pixels.setPixelColor(arrayInt[i] + toAdd, PARTY_BUFFER[arrayInt[i] + toAdd][1], PARTY_BUFFER[arrayInt[i] + toAdd][0], PARTY_BUFFER[arrayInt[i] + toAdd][2]);
    }
  } else {
    for (int i = 0; i < arraySize; i++) {
      pixels.setPixelColor(arrayInt[i] + toAdd, GREEN_RGB, RED_RGB, BLUE_RGB);
    }
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

void Led::setLedTime(int hours, int minutes, int seconds) {

  int einerSekunde = seconds % 10;
  int zehnerSekunde = seconds / 10;
  int einerMinute = minutes % 10;
  int zehnerMinute = minutes / 10;
  int einerStunde = hours % 10;
  int zehnerStunde = hours / 10;

  switch (einerSekunde) {
    case 0: setLedPixel(zero, sizeof(zero) / sizeof(*zero), 0); break;
    case 1: setLedPixel(one, sizeof(one) / sizeof(*one), 0); break;
    case 2: setLedPixel(two, sizeof(two) / sizeof(*two), 0); break;
    case 3: setLedPixel(three, sizeof(three) / sizeof(*three), 0); break;
    case 4: setLedPixel(four, sizeof(four) / sizeof(*four), 0); break;
    case 5: setLedPixel(five, sizeof(five) / sizeof(*five), 0); break;
    case 6: setLedPixel(six, sizeof(six) / sizeof(*six), 0); break;
    case 7: setLedPixel(seven, sizeof(seven) / sizeof(*seven), 0); break;
    case 8: setLedPixel(eight, sizeof(eight) / sizeof(*eight), 0); break;
    case 9: setLedPixel(nine, sizeof(nine) / sizeof(*nine), 0); break;
  }
  switch (zehnerSekunde) {
    case 0: setLedPixel(zero, sizeof(zero) / sizeof(*zero), 21); break;
    case 1: setLedPixel(one , sizeof(one) / sizeof(*one), 21); break;
    case 2: setLedPixel(two , sizeof(two) / sizeof(*two), 21); break;
    case 3: setLedPixel(three, sizeof(three) / sizeof(*three), 21); break;
    case 4: setLedPixel(four, sizeof(four) / sizeof(*four), 21); break;
    case 5: setLedPixel(five, sizeof(five) / sizeof(*five), 21); break;
    case 6: setLedPixel(six , sizeof(six) / sizeof(*six), 21); break;
    case 7: setLedPixel(seven, sizeof(seven) / sizeof(*seven), 21); break;
    case 8: setLedPixel(eight, sizeof(eight) / sizeof(*eight), 21); break;
    case 9: setLedPixel(nine, sizeof(nine) / sizeof(*nine), 21); break;
  }

  setLedPixel(dot, sizeof(dot) / sizeof(*dot), 42);

  switch (einerMinute) {
    case 0: setLedPixel(zero, sizeof(zero) / sizeof(*zero), 44); break;
    case 1: setLedPixel(one, sizeof(one) / sizeof(*one), 44); break;
    case 2: setLedPixel(two, sizeof(two) / sizeof(*two), 44); break;
    case 3: setLedPixel(three, sizeof(three) / sizeof(*three), 44); break;
    case 4: setLedPixel(four, sizeof(four) / sizeof(*four), 44); break;
    case 5: setLedPixel(five, sizeof(five) / sizeof(*five), 44); break;
    case 6: setLedPixel(six, sizeof(six) / sizeof(*six), 44); break;
    case 7: setLedPixel(seven, sizeof(seven) / sizeof(*seven), 44); break;
    case 8: setLedPixel(eight, sizeof(eight) / sizeof(*eight), 44); break;
    case 9: setLedPixel(nine, sizeof(nine) / sizeof(*nine), 44); break;
  }
  switch (zehnerMinute) {
    case 0: setLedPixel(zero, sizeof(zero) / sizeof(*zero), 65); break;
    case 1: setLedPixel(one , sizeof(one) / sizeof(*one), 65); break;
    case 2: setLedPixel(two , sizeof(two) / sizeof(*two), 65); break;
    case 3: setLedPixel(three, sizeof(three) / sizeof(*three), 65); break;
    case 4: setLedPixel(four, sizeof(four) / sizeof(*four), 65); break;
    case 5: setLedPixel(five, sizeof(five) / sizeof(*five), 65); break;
    case 6: setLedPixel(six , sizeof(six) / sizeof(*six), 65); break;
    case 7: setLedPixel(seven, sizeof(seven) / sizeof(*seven), 65); break;
    case 8: setLedPixel(eight, sizeof(eight) / sizeof(*eight), 65); break;
    case 9: setLedPixel(nine, sizeof(nine) / sizeof(*nine), 65); break;
  }

  setLedPixel(dot, sizeof(dot) / sizeof(*dot), 86);

  switch (einerStunde) {
    case 0: setLedPixel(zero, sizeof(zero) / sizeof(*zero), 88); break;
    case 1: setLedPixel(one, sizeof(one) / sizeof(*one), 88); break;
    case 2: setLedPixel(two, sizeof(two) / sizeof(*two), 88); break;
    case 3: setLedPixel(three, sizeof(three) / sizeof(*three), 88); break;
    case 4: setLedPixel(four, sizeof(four) / sizeof(*four), 88); break;
    case 5: setLedPixel(five, sizeof(five) / sizeof(*five), 88); break;
    case 6: setLedPixel(six, sizeof(six) / sizeof(*six), 88); break;
    case 7: setLedPixel(seven, sizeof(seven) / sizeof(*seven), 88); break;
    case 8: setLedPixel(eight, sizeof(eight) / sizeof(*eight), 88); break;
    case 9: setLedPixel(nine, sizeof(nine) / sizeof(*nine), 88); break;
  }
  switch (zehnerStunde) {
    case 0: setLedPixel(zero, sizeof(zero) / sizeof(*zero), 109); break;
    case 1: setLedPixel(one , sizeof(one) / sizeof(*one), 109); break;
    case 2: setLedPixel(two , sizeof(two) / sizeof(*two), 109); break;
    case 3: setLedPixel(three, sizeof(three) / sizeof(*three), 109); break;
    case 4: setLedPixel(four, sizeof(four) / sizeof(*four), 109); break;
    case 5: setLedPixel(five, sizeof(five) / sizeof(*five), 109); break;
    case 6: setLedPixel(six , sizeof(six) / sizeof(*six), 109); break;
    case 7: setLedPixel(seven, sizeof(seven) / sizeof(*seven), 109); break;
    case 8: setLedPixel(eight, sizeof(eight) / sizeof(*eight), 109); break;
    case 9: setLedPixel(nine, sizeof(nine) / sizeof(*nine), 109); break;
  }

  if (STATE_STATUS) {
    pixels.setBrightness(max(int(BRIGHTNESS_VALUE), 3));
  } else {
    pixels.setBrightness(0);
  }

  //pixels.setBrightness(100);
  pixels.show();
}
