#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <AbstractTriggerTask.h>
#include <Property.h>
#include <AnimatedProperty.h>

#include "LedController.h"
#include "TouchController.h"

#define CLIMA_MARKER_WIDTH 5
#define VOLUME_MARKER_WIDTH 5

#define TP_MARKER_SPACING_TOTAL TP_MARKER_SPACING * 2
#define TP_MARKER_WIDTH_TOTAL TP_MARKER_WIDTH * 2

#define TP_MARKER_SPACING 2
#define TP_MARKER_WIDTH 1
#define TP_MARKER_TAIL_WIDTH 3

#define PALETTE_MAX 240   // hmm, why ?

class LogicController : public AbstractIntervalTask {
public:
  typedef void(LogicController::*renderMethod)(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led);
  
  enum PAGE_ID {
    PAGE_INVALID = -1,
    PAGE_HUD,
    PAGE_APPS,
    PAGE_CLIMA,
    PAGE_VOLUME,

    PAGE_DEFAULT = PAGE_CLIMA,
    PAGE_MAX = PAGE_VOLUME
  };
  
  LogicController();
  
  void init();

  void update();

  void setClimaPalette(CRGBPalette16 *climaPalette);

  void setPage(PAGE_ID page);

  void setVolume(uint8_t volume);

  void setClima(uint8_t clima);

protected:
  void renderNothing(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led);

  void renderHUD(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led);

  void renderApps(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led);

  void renderClima(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led);

private:
  PAGE_ID currentPage = PAGE_INVALID;
  CRGBPalette16 *climaPalette;
  
  LogicController::renderMethod activeRenderMethod;

  uint8_t volume = 0;     // unit: TP_COUNT_TOTAL
  uint8_t clima = 0;      // unit: TP_COUNT_TOTAL

  int8_t tp_old = 0;

  bool pageChanged = false;

  void renderMarker(TouchController *tc, LedController* lc, int8_t tp, uint8_t tp_led, CRGB markerColor, uint8_t markerWidth, uint8_t markerTailWidth);

};


#endif    //LOGICCONTROLLER_H
