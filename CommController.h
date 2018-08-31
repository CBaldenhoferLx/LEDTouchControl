#ifndef COMMCONTROLLER_H
#define COMMCONTROLLER_H

#include <AbstractTask.h>

class CommController : public AbstractTask {
public:
  CommController();

  void init();

  void update();

  void sendCmd(String &data);
  
};


#endif // COMMCONTROLLER_H
