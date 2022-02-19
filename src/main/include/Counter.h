#pragma once

#include <frc/Timer.h>

class Counter {
public:
  Counter();
  ~Counter();
  
  void Start();
  void Stop();
  
  bool SecondsPassed(double sec);
  
private:
  frc::Timer *timer;
  
  bool firstCall;
  double initTime;
};
