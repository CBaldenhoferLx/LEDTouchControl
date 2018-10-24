#include "LedController.h"

#include <LogHelper.h>

#include "Pins.h"

LedController::LedController() : AbstractIntervalTask(10) {
}

void LedController::init() {
  FastLED.addLeds<WS2811, PIN_LED, GRB>(leds, LED_COUNT);//.setCorrection( TypicalLEDStrip );
}

void LedController::update() {
}

void LedController::showStrip() {
   FastLED.show();
}

void LedController::setPixel(uint8_t pixel, CRGB color) {
  pixel = constrain(pixel, 0, LED_COUNT-1);
  leds[pixel] = color;
}

void LedController::setPixel(uint8_t pixel, byte red, byte green, byte blue) {
  pixel = constrain(pixel, 0, LED_COUNT-1);
  leds[pixel].r = red;
  leds[pixel].g = green;
  leds[pixel].b = blue;
}

CRGB LedController::getPixel(uint8_t pixel) {
  return leds[pixel];
}

void LedController::setAll(CRGB color) {
  for(int i = 0; i < LED_COUNT; i++ ) {
    setPixel(i, color); 
  }
  showStrip();
}

void LedController::setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < LED_COUNT; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void LedController::setBrightness(uint8_t brightness) {
  LOG_PRINT(F("Setting brightness to "));
  LOG_PRINTLN(brightness);
  
//  ledStrip->setBrightness(brightness);
}

uint8_t LedController::middleIndex() {
  return LED_COUNT / 2;
}

