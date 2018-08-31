#include "LedController.h"

#include <LogHelper.h>

LedController::LedController() : AbstractTriggerTask() {
}

LedController::~LedController() {
  delete ledStrip;
}

void LedController::init() {
  ledStrip = new Adafruit_NeoPixel(LED_COUNT, PIN_LED, NEO_GRB + NEO_KHZ800);

  ledStrip->begin();
}

void LedController::update() {
}

void LedController::setLed(uint8_t i, uint32_t color) {
  i = constrain(i, 0, LED_COUNT-1);
  ledStrip->setPixelColor(i, color);
  ledStrip->show();
}

void LedController::setBrightness(uint8_t brightness) {
  LOG_PRINT(F("Setting brightness to "));
  LOG_PRINTLN(brightness);
  
  ledStrip->setBrightness(brightness);
}

