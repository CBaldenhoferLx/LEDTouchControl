#include "TouchController.h"

#include <LogHelper.h>
#include <Adafruit_NeoPixel.h>

#include "TaskIDs.h"
#include "LedController.h"

TouchController::TouchController() : AbstractIntervalTask(100) {
}

void TouchController::init() {
  for (uint8_t i=0;i<TC_COUNT;i++) {
    // will hang here if no PU resistor
    if (!touchPoints[i].begin(TP_ADDRESS+i)) {
      LOG_PRINTLN("MPR121 not found !");
    } else {
      LOG_PRINTLN("MPR121 initialized");
    }
  }
  
  for (uint8_t i=0;i<TP_COUNT;i++) {
    touchPoint.init(i, NO_TOUCH);
    touchPoint.setOutputOnChange(true);
  }
}

void TouchController::update() {
  bool found = false;

  for (uint8_t o=0;o<TC_COUNT;o++) {
    uint16_t currtouched = touchPoints[o].touched();
    
  // TODO: optimize this
    for (uint8_t i=0;i<TP_COUNT;i++) {
      if (!found && (currtouched & _BV(i))) {
        touchPoint.setValue((TC_COUNT*o)+i);
        found = true;
        break;
      }
    }
  }

  if (!found) {
    touchPoint.setValue(NO_TOUCH);
  }
}

