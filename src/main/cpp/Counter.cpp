#include "Counter.h"

Counter::Counter() {
  timer = new frc::Timer();
  
  firstCall = false;
  initTime = 0.0;
}

void Counter::Start() { timer->Start(); }
void Counter::Stop() { timer->Stop(); }

bool Counter::SecondsPassed(double t) {
  if (!firstCall) {
    initTime = timer->Get();
    firstCall = true;
  }
  if (timer->HasPeriodPassed(initTime + t)) {
    firstCall = false;
    return true;
  }
  return false;
}
