#include "Protocol.h"
#include <LogHelper.h>
#include <TaskManager.h>

#include "CommController.h"
#include "TouchController.h"
#include "LedController.h"
#include "LogicController.h"

TaskManager taskManager;

CommController commController;
TouchController touchController;
LedController ledController;
LogicController logicController;

void setup() {
  LOG_INIT();
  LOG_WAIT();

  LOG_PRINTLN(F("Init"));

  taskManager.registerTask(&commController);
  taskManager.registerTask(&touchController);
  taskManager.registerTask(&ledController);
  taskManager.registerTask(&logicController);
  
  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(10);
}
