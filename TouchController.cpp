#include "TouchController.h"

#include <LogHelper.h>
#include <Adafruit_NeoPixel.h>

#include "TaskIDs.h"
#include "LedController.h"

TouchController::TouchController() : AbstractIntervalTask(100) {
}

TouchController::~TouchController() {
  delete touchPoints;
}

void TouchController::init() {
  touchPoints = new Adafruit_MPR121();

  if (!touchPoints->begin(0x5A)) {
    LOG_PRINTLN("MPR121 not found !");
  }
  
  for (uint8_t i=0;i<TP_COUNT;i++) {
    tps[i].init(i, false);
    tps[i].setOutputOnChange(true);
  }
}

void TouchController::update() {
  uint16_t currtouched = touchPoints->touched();
  
  for (uint8_t i=0;i<TP_COUNT;i++) {
    tps[i].setValue( currtouched & _BV(i) );
  }
}

