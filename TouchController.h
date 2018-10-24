#ifndef TOUCHCONTROLLER_H
#define TOUCHCONTROLLER_H

#define SUPPORT_OUTPUT_ON_CHANGE
#define SUPPORT_PROPERTY_NAME

#include <AbstractIntervalTask.h>
#include <AnimatedProperty.h>
#include <Property.h>
#include <Wire.h>
#include <Adafruit_MPR121.h>

#define TP_ADDRESS 0x5A

#define TP_COUNT 10
#define TC_COUNT 1
#define TP_COUNT_TOTAL TP_COUNT * TC_COUNT

#define TP_ANIMATION_SPEED_MS 250

#define NO_TOUCH -1.0

class TouchController : public AbstractIntervalTask, public Property<int>::ValueChangeListener {
public:
  TouchController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, int newValue, int oldValue);

  float getTouchPoint();

private:
  Adafruit_MPR121 touchPoints[TC_COUNT];
  
  Property<int> touchPointReal;

  float oldTouchPoint;
  AnimatedProperty<float> touchPoint;
  
};


#endif    //TOUCHCONTROLLER_H
