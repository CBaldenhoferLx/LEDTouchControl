#include "LogicController.h"

#include <LogHelper.h>
#include <Adafruit_NeoPixel.h>

#include "TaskIDs.h"

LogicController::LogicController() : AbstractIntervalTask(10) {
}

void LogicController::init() {
  setPage(PAGE_DEFAULT);
}

void LogicController::update() {
  TouchController *tc = taskManager->getTask<TouchController*>(TOUCH_CONTROLLER);
  LedController* lc = taskManager->getTask<LedController*>(LED_CONTROLLER);

  if (pageChanged) {
    lc->setAll(CRGB::Black);    // clear
    pageChanged = false;
    lc->showStrip();
  }

  float tp = tc->getTouchPoint();
  int i = map(tp * 1000, 0, 1000 * (TP_COUNT_TOTAL-1), 0, LED_COUNT-1);
  uint8_t tp_led = tp!=NO_TOUCH ? i : 0;

  if (tp_old!=tp) {
    (this->*activeRenderMethod)(tc, lc, tp, tp_led);

    lc->showStrip();
    tp_old = tp;
  }

  // output led state
  /*
  for (uint8_t i=0;i<LED_COUNT;i++) {
    LOG_PRINT(map((lc->getPixel(i).r + lc->getPixel(i).g + lc->getPixel(i).b), 0, 255*3, 0, 9));
  }
  LOG_PRINTLN("");
  */
  
}

void LogicController::setClimaPalette(CRGBPalette16 *climaPalette) {
  this->climaPalette = climaPalette;
}

void LogicController::setPage(PAGE_ID page) {
  page = constrain(page, 0, PAGE_MAX);
  if (currentPage == page) return;
  
  currentPage = page;

  switch(currentPage) {
    case PAGE_HUD:
      activeRenderMethod = &LogicController::renderHUD;
      break;
    case PAGE_APPS:
      activeRenderMethod = &LogicController::renderApps;
      break;
    case PAGE_CLIMA:
      activeRenderMethod = &LogicController::renderClima;
      break;
    case PAGE_VOLUME:
      break;
  }

  pageChanged = true;
  updateNow();
}

void LogicController::setVolume(uint8_t volume) {
  this->volume = volume;
}

void LogicController::setClima(uint8_t clima) {
  this->clima = clima;
}

void LogicController::renderMarker(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led, CRGB markerColor, uint8_t markerWidth, uint8_t markerTailWidth) {
  if (tp==NO_TOUCH) return;

  LOG_PRINT(tp_led);
  LOG_PRINTLN("Render Marker");
  
  //lc->setPixel(tp_led, markerColor);

  CRGBPalette16 palette(markerColor, CRGB::Black);

  LOG_PRINTLN("Palette");

  int i = tp_led-((markerWidth/2)+markerTailWidth);
  int i2;
  int i3;

  // left tail
  i2 = min(255, i+markerTailWidth);
  i3 = 0;
  for (i;i<i2;i++) {
    if (i>=0) {
      LOG_PRINT("LT");
      LOG_PRINTLN(i);
      lc->setPixel(i, ColorFromPalette(palette, map(i3, 0, markerTailWidth, 255, 0)));
    }
    i3++;
  }

  return;

  LOG_PRINTLN(i);
  LOG_PRINTLN(min(255,i+markerWidth));

  //marker itself
  i2 = min(255,i+markerWidth);
  for (i;i<i2;i++) {
    if (i>=0) {
      LOG_PRINT("MARKER");
      LOG_PRINTLN(i);
      lc->setPixel(i, markerColor);
    }
  }
  
  LOG_PRINTLN(i);
  LOG_PRINTLN(min(255, i+markerTailWidth));

  // right tail
  i2 = min(255, i+markerTailWidth);
  i3 = 0;
  for (i;i<i2;i++) {
    if (i<255) {
      LOG_PRINT("RT");
      LOG_PRINTLN(i);
      lc->setPixel(i, ColorFromPalette(palette, map(i3, 0, markerTailWidth, 0, 255)));
    }
    i3++;
  }

}

void LogicController::renderNothing(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led) {
  // do nothing
  //LOG_PRINTLN(F("Render nothing"));
  lc->setAll(CRGB::White);
}

void LogicController::renderHUD(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led) {
  // just render marker
  lc->setAll(CRGB::Black);
  renderMarker(tc, lc, tp, tp_led, CRGB::Blue, TP_MARKER_WIDTH, TP_MARKER_TAIL_WIDTH);
}

void LogicController::renderApps(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led) {
  // check if markers were touched
  if (tp!=NO_TOUCH) {
    if (tp_led<=CLIMA_MARKER_WIDTH) {
      // clima touched
      setPage(PAGE_CLIMA);
      return;
    } else if (tp_led>=LED_COUNT-VOLUME_MARKER_WIDTH) {
      // volume touched
      setPage(PAGE_VOLUME);
      return;
    }
  }
    
  uint8_t i = 0;

  // render 2 icons on the left and right side
  // clima
  for (i;i<CLIMA_MARKER_WIDTH;i++) {
    lc->setPixel(i, CRGB::Green);     // or with clima color ?
  }
  
  if (tp==NO_TOUCH) {
    
  } else {
    
  }
  
  // Volume
  for (i=LED_COUNT-VOLUME_MARKER_WIDTH;i<LED_COUNT;i++) {
    lc->setPixel(i, CRGB::Purple);
  }
}

void LogicController::renderClima(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led) {

  if (tp==NO_TOUCH) {
    uint8_t mappedClima = map(clima, 0, TP_COUNT_TOTAL-1, 0, PALETTE_MAX);
    CRGB color = ColorFromPalette(*climaPalette, mappedClima);
    lc->setAll(color);
  } else {
    clima = tp;
    uint8_t mappedClima = map(clima, 0, TP_COUNT_TOTAL-1, 0, PALETTE_MAX);
    LOG_PRINTLN(clima);
    LOG_PRINTLN(mappedClima);
    CRGB color = ColorFromPalette(*climaPalette, mappedClima);
  
    LOG_PRINT(color.r);
    LOG_PRINT(" ");
    LOG_PRINT(color.g);
    LOG_PRINT(" ");
    LOG_PRINTLN(color.b);

    // left part
    uint8_t i = 0;
    uint8_t i2;
    
    for (i; i<max(0, tp_led - (TP_MARKER_SPACING + TP_MARKER_WIDTH)); i++) {
      lc->setPixel(i, color);
    }
    
    // spacing
    i2 = i+TP_MARKER_SPACING;
    for (i; i<i2; i++) {
      lc->setPixel(i, CRGB::Black);
    }
    
    // marker
    i2 = i+TP_MARKER_WIDTH;
    for (i; i<i2; i++) {
      lc->setPixel(i, CRGB::White);   // marker: white
    }
    
    // spacing
    i2 = i+TP_MARKER_SPACING;
    for (i; i<i2; i++) {
      lc->setPixel(i, CRGB::Black);
    }
    
    // right part
    for (i; i<LED_COUNT; i++) {
      lc->setPixel(i, color);
    }
  }
}

