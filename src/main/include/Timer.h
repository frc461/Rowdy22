#pragma once

#include <frc/Timer.h>

class Timer {
public:
  Timer();
  ~Timer();
  
  void Start();
  void Stop();
  
  bool SecondsPassed(double t);
  
private:
  frc::Timer *timer;
  
  bool firstCall;
  double initTime;
};
