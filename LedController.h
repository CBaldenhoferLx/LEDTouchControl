#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#define SUPPORT_OUTPUT_ON_CHANGE
#define SUPPORT_PROPERTY_NAME

#include <Adafruit_NeoPixel.h>
#include <AbstractTriggerTask.h>
#include "Pins.h"

#define LED_COUNT 144

class LedController : public AbstractTriggerTask {
public:
  LedController();
  ~LedController();
  
  void init();

  void update();

  void setLed(uint8_t i, uint32_t color);

private:
  Adafruit_NeoPixel *ledStrip;
  
};


#endif    //LEDCONTROLLER_H
