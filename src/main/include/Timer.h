#pragma once

#include <frc/Timer.h>

class Timer {
public:
  Timer();
  ~Timer();
  
private:
  frc::Timer *timer;
};
