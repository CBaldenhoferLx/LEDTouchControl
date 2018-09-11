#include "Protocol.h"
#include <LogHelper.h>
#include <TaskManager.h>
#include <FastLED.h>

#include "CommController.h"
#include "TouchController.h"
#include "LedController.h"
#include "LogicController.h"

#include "TaskIDs.h"

TaskManager taskManager;

CommController commController;
TouchController touchController;
LedController ledController;
LogicController logicController;

DEFINE_GRADIENT_PALETTE( clima_gradient ) {
    0,   0,  0,  255,   //blue
  TP_COUNT_TOTAL, 255,  0,  0      //red
  };
 
CRGBPalette16 climaPalette = clima_gradient;

void setup() {
  LOG_INIT();
  LOG_WAIT();

  LOG_PRINTLN(F("Init"));

  taskManager.registerTask(&commController);
  taskManager.registerTask(&touchController);
  taskManager.registerTask(&ledController);
  taskManager.registerTask(&logicController);
  
  taskManager.init();

  taskManager.getTask<LogicController*>(LOGIC_CONTROLLER)->setClimaPalette(&climaPalette);
}

void loop() {
  taskManager.update();
  delay(10);
}
