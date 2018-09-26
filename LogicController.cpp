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
  }

  int8_t tp = tc->getTouchPoint();
  uint8_t tp_led = tp!=NO_TOUCH ? map(tp, 0, TP_COUNT_TOTAL-1, 0, LED_COUNT-1) : 0;

  (this->*activeRenderMethod)(tc, lc, tp, tp_led);
  
  lc->showStrip();

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
  
  lc->setPixel(tp_led, markerColor);

  CRGBPalette16 palette(markerColor, CRGB::Black);

  LOG_PRINTLN("Palette");

  uint8_t i = tp_led-((markerWidth/2)+markerTailWidth);

  // left tail
  for (i;i<i+markerTailWidth;i++) {
    LOG_PRINTLN(map(i, 0, markerTailWidth, 0, 255));
    lc->setPixel(i, ColorFromPalette(palette, map(i, 0, markerTailWidth, 255, 0)));
  }

  //marker itself
  for (i;i<i+markerWidth;i++) {
    lc->setPixel(i, markerColor);
  }
  
  LOG_PRINTLN(i);

  // right tail
  for (i;i<i+markerTailWidth;i++) {
    lc->setPixel(i, ColorFromPalette(palette, map(i, 0, markerTailWidth, 0, 255)));
  }

  LOG_PRINTLN(i);

}

void LogicController::renderNothing(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led) {
  // do nothing
  //LOG_PRINTLN(F("Render nothing"));
  lc->setAll(CRGB::White);
}

void LogicController::renderHUD(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led) {
  // just render marker
  lc->setAll(CRGB::Black);
  //renderMarker(tc, lc, tp, tp_led, CRGB::Blue, TP_MARKER_WIDTH, TP_MARKER_TAIL_WIDTH);
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
    CRGB color = ColorFromPalette(*climaPalette, clima);
    lc->setAll(color);
  } else {
    clima = tp;
    CRGB color = ColorFromPalette(*climaPalette, clima);
  
    // left part
    uint8_t i = 0;
    
    for (i; i<max(0, tp_led - (TP_MARKER_SPACING + TP_MARKER_WIDTH)); i++) {
      lc->setPixel(i, color);
    }
    // spacing
    for (i; i<i+TP_MARKER_SPACING; i++) {
      lc->setPixel(i, CRGB::Black);
    }
    // marker
    for (i; i<i+TP_MARKER_WIDTH; i++) {
      lc->setPixel(i, CRGB::White);   // marker: white
    }
    // spacing
    for (i; i<i+TP_MARKER_SPACING; i++) {
      lc->setPixel(i, CRGB::Black);
    }
    // right part
    for (i; i<LED_COUNT; i++) {
      lc->setPixel(i, color);
    }
  }
}

