#include "Timer.h"

Timer::Timer() {
  timer = new Timer();
  
  firstCall = false;
  initTime = 0.0;
}

void Timer::Start() { timer->Start(); }

bool Timer::SecondsPassed(double t) {
  if (!firstCall) {
    initTime = timer->getFPGATimestamp();
    firstCall = true;
  }
  if (timer->HasPeriodPassed(initTime + t)) {
    firstCall = false;
    return true;
  }
  return false;
}
