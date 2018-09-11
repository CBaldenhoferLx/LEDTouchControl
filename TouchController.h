#ifndef TOUCHCONTROLLER_H
#define TOUCHCONTROLLER_H

#define SUPPORT_OUTPUT_ON_CHANGE
#define SUPPORT_PROPERTY_NAME

#include <AbstractIntervalTask.h>
#include <Property.h>
#include <Wire.h>
#include <Adafruit_MPR121.h>

#define TP_ADDRESS 0x5A

#define TP_COUNT 12
#define TC_COUNT 2
#define TP_COUNT_TOTAL TP_COUNT * TC_COUNT

#define NO_TOUCH 0

class TouchController : public AbstractIntervalTask {
public:
  TouchController();
  
  void init();

  void update();

  Property<uint8_t> touchPoint;   // 0 = no touch, >0: 1..255 left <> right

private:
  Adafruit_MPR121 touchPoints[TC_COUNT];
  
};


#endif    //TOUCHCONTROLLER_H
