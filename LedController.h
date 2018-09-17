#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <FastLED.h>
#include <AbstractIntervalTask.h>

#define LED_COUNT 144

class LedController : public AbstractIntervalTask {
public:
  LedController();
  
  void init();

  void update();

  void showStrip();

  void setPixel(uint8_t pixel, CRGB color);

  void setPixel(uint8_t pixel, byte red, byte green, byte blue);

  void setAll(CRGB color);

  void setAll(byte red, byte green, byte blue);

  void setBrightness(uint8_t brightness);

  uint8_t middleIndex();

  CRGB getPixel(uint8_t pixel);

private:
  CRGB leds[LED_COUNT];
  
};


#endif    //LEDCONTROLLER_H
