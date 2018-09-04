#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <AbstractTriggerTask.h>
#include <Property.h>
#include <AnimatedProperty.h>

#include "LedController.h"

class LogicController : public AbstractIntervalTask, public Property<bool>::ValueChangeListener {
public:
  LogicController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);

private:
/*
  class AnimationLogic : public AbstractTriggerTask, public Property<float>::ValueChangeListener {
    public:
      AnimationLogic();

      void init();

      void update();
      
      void onPropertyValueChange(uint8_t id, float newValue, float oldValue);
      
    private:
      AnimatedProperty<float> ledAni[LED_COUNT];
  };

  AnimationLogic animationLogic;
  */
};


#endif    //LOGICCONTROLLER_H
