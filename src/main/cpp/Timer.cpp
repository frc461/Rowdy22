#include "Timer.h"

Timer::Timer() {
  timer = new Timer();
  
  firstCall = false;
  initTime = 0.0;
}

void Timer::Start() { timer->Start(); }

bool Timer::SecondsPassed(double t) {
  if (!firstCall) {
    
  }
}
