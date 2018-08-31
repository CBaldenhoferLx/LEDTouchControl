#ifndef TOUCHCONTROLLER_H
#define TOUCHCONTROLLER_H

#define SUPPORT_OUTPUT_ON_CHANGE
#define SUPPORT_PROPERTY_NAME

#include <AbstractIntervalTask.h>
#include <Property.h>
#include <Wire.h>
#include <Adafruit_MPR121.h>

#define TP_COUNT 12
#define TP_ADDRESS 0x5A

class TouchController : public AbstractIntervalTask {
public:
  TouchController();
  ~TouchController();
  
  void init();

  void update();

  Property<bool> tps[TP_COUNT];

private:
  Adafruit_MPR121 *touchPoints;
  
};


#endif    //TOUCHCONTROLLER_H
