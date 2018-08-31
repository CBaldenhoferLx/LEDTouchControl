#include "LedController.h"

#include <LogHelper.h>

LedController::LedController() : AbstractTriggerTask() {
}

LedController::~LedController() {
  delete ledStrip;
}

void LedController::init() {
  ledStrip = new Adafruit_NeoPixel(LED_COUNT, PIN_LED, NEO_GRB + NEO_KHZ800);
}

void LedController::update() {
}

void LedController::setLed(uint8_t i, uint32_t color) {
  i = constrain(i, 0, LED_COUNT-1);
  ledStrip->setPixelColor(i, color);
  ledStrip->show();
}
