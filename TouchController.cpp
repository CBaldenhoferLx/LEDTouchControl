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

  touchPointReal.init(0, NO_TOUCH);
  //touchPointReal.setOutputOnChange(true);
  touchPointReal.registerValueChangeListener(this);
  
  touchPoint.init(1, NO_TOUCH, TP_ANIMATION_SPEED_MS, 0);
  touchPoint.setOutputOnChange(true);
}

void TouchController::update() {
  bool found = false;

  for (uint8_t o=0;o<TC_COUNT;o++) {
    uint16_t currtouched = touchPoints[o].touched();

    // TODO: optimize this
    for (uint8_t i=0;i<TP_COUNT;i++) {
      if (!found && (currtouched & _BV(i))) {
        touchPointReal.setValue((TC_COUNT*o)+i);
        found = true;
        o = TC_COUNT;
        break;
      }
    }
  }

  if (!found) {
    touchPointReal.setValue(NO_TOUCH);
  }

  touchPoint.update();
}

void TouchController::onPropertyValueChange(uint8_t id, int8_t newValue, int8_t oldValue) {
  if (newValue==NO_TOUCH) {
    oldTouchPoint = newValue;
    touchPoint.setValueDirect(newValue);
  } else if (oldValue==NO_TOUCH) {
    touchPoint.setValueDirect(newValue);
  } else {
    touchPoint.setValue(newValue);
  }
}

uint8_t TouchController::getTouchPoint() {
  return touchPointReal.getValue();
}

