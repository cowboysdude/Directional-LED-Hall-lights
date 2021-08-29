#include "FastLED.h"

#define NUM_LEDS 180
#define LED_DATA_PIN 9
#define LEDS_PER_STAIR 20           // Number of Leds per stair.
CRGB leds[NUM_LEDS];
int onTime = 20*1000;               // 20 seconds
int MOTION_LEFT = 10;
int MOTION_RIGHT = 11;
int fadeTimeDiff = 20;


void setup() {
  FastLED.addLeds<WS2812, LED_DATA_PIN, BRG>(leds, NUM_LEDS);
  pinMode(MOTION_LEFT, INPUT);
  pinMode(MOTION_RIGHT, INPUT);
  startupLEDsTest();
}

void loop() {
  if (digitalRead(MOTION_LEFT) == HIGH) {
    fadeInLeft();
    delay(onTime);
    fadeOut();
  } else {
    if (digitalRead(MOTION_RIGHT) == HIGH) {
    fadeInRight();
    delay(onTime);
    fadeOut();
  }
   }
}
void fadeInRight() {
  for (int stair = 0; stair < NUM_LEDS; stair += LEDS_PER_STAIR) {
    for (int b = 0; b < 175; b += 10) {
      for (int led = stair ; led < stair + LEDS_PER_STAIR; led++) {
        leds[led] = CHSV(0,0,b);
      }
      FastLED.show();
      delay(fadeTimeDiff);
    }
  }
}

void fadeInLeft() {
 for (int stair = NUM_LEDS - LEDS_PER_STAIR; stair >= 0; stair -= LEDS_PER_STAIR) {
    for (int b = 0; b < 175; b += 10) {
      for (int led = stair ; led < stair + LEDS_PER_STAIR; led++) {
        leds[led] = CHSV(0,0,b);
      }
      FastLED.show();
      delay(fadeTimeDiff);
    }
  }
}

void startupLEDsTest() {
  // startup blink test to confirm LEDs are working.
  FastLED.setBrightness(100);
  fill_solid(leds, NUM_LEDS, CHSV(161,99,99));  
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CHSV(161,57,99));   
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CHSV(161,12,99));   
  FastLED.show();
  delay(1000);
  FastLED.clear();
  FastLED.show();
}

void fadeOut() {
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CHSV(0,0,0);
  }
  for (int b = 255; b > 0; b -= 40) {
    FastLED.setBrightness(b);
    FastLED.show();
    delay(fadeTimeDiff);
  }
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CHSV(0,0,0);
  }
  FastLED.show();
}
