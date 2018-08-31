#include "CommController.h"

#include "Protocol.h"
#include <LogHelper.h>
#include "TaskIDs.h"

#include "LedController.h"

CommController::CommController() : AbstractTask() {  
}

void CommController::init() {
  LOG_PRINTLN(F("Interface ready"));
}

void CommController::update() {
  if (Serial.available()>0) {
    String s = Serial.readStringUntil('\n');
    if (s.endsWith("\r")) s.remove(s.length()-1);
    
    if (s.length()>=SP_MIN_DATAGRAM_SIZE) {
      uint8_t cmd = s.charAt(0);
      String param1 = s.substring(1);
  
      if (cmd == SP_COMMENT_PREFIX) {
        // comment
      } else if (cmd == SP_BRIGHTNESS) {
        taskManager->getTask<LedController*>(LED_CONTROLLER)->setBrightness(param1.toInt());
      } else {
        LOG_PRINT(F("Unknown command: "));
        LOG_PRINTLN(s);
      }
    } else {
        LOG_PRINTLN(F("Not enough data"));
    }
  }
}

void CommController::sendCmd(String &data) {
  Serial.println(data);
}
