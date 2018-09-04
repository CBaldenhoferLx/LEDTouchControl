#include "LogicController.h"

#include <LogHelper.h>
#include <Adafruit_NeoPixel.h>

#include "TaskIDs.h"
#include "LedController.h"
#include "TouchController.h"

LogicController::LogicController() : AbstractIntervalTask(100) {
}

void LogicController::init() {
  TouchController *tc = taskManager->getTask<TouchController*>(TOUCH_CONTROLLER);
  
  for (uint8_t i=0;i<TP_COUNT;i++) {
    tc->tps[i].registerValueChangeListener(this);
  }

  //animationLogic.init();
}

void LogicController::update() {
  //animationLogic.update();
}

void LogicController::onPropertyValueChange(uint8_t id, bool newValue, bool oldValue) {
  LedController* lc = taskManager->getTask<LedController*>(LED_CONTROLLER);

  // TODO: impl logic
}

/*
LogicController::AnimationLogic::AnimationLogic() : AbstractTriggerTask() {
  
}

void LogicController::AnimationLogic::init() {
}

void LogicController::AnimationLogic::update() {
}

void LogicController::AnimationLogic::onPropertyValueChange(uint8_t id, float newValue, float oldValue) {
  
}
*/
