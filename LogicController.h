#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <Property.h>

class LogicController : public AbstractIntervalTask, public Property<bool>::ValueChangeListener {
public:
  LogicController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);
  
private:
  
};


#endif    //LOGICCONTROLLER_H
