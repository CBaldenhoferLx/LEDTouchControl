#include "CommController.h"

#include <LogHelper.h>

CommController::CommController() : AbstractTask() {
  
}

void CommController::init() {
//  LOG_PRINTLN(F("Available commands:"));
//  LOG_PRINTLN(F("lon[0-9] -> LED n on"));
//  LOG_PRINTLN(F("loff[0-9] -> LED n off"));
}

void CommController::update() {
  if (Serial.available()>0) {
    String s = Serial.readStringUntil('\n');
    int param1 = s.substring(2).toInt();

/*
    if (s.startsWith("sl")) {
      taskManager->getTask<FanController*>(FAN_CONTROLLER)->setSpeedLevel(SPEED_LEFT, param1);
    } else if (s.startsWith("sr")) {
      taskManager->getTask<FanController*>(FAN_CONTROLLER)->setSpeedLevel(SPEED_RIGHT, param1);
    } else if (s.startsWith("sm")) {
      taskManager->getTask<SmellController*>(SMELL_CONTROLLER)->releaseSmell(param1);
    } else {
      LOG_PRINT(F("Unknown command: "));
      LOG_PRINTLN(s);
    }
  */
  }
}

