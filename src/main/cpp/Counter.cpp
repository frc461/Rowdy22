#include "Counter.h"

Counter::Counter() {
  timer = new frc::Timer();
  
  firstCall = false;
  initTime = 0.0;
}

void Counter::Start() { timer->Start(); }
void Counter::Stop() { timer->Stop(); }
void Counter::ResetAll() {
  timer->Reset();
  firstCall = false;
  initTime = 0.0;
}

bool Counter::SecondsPassed(double t) {
  if (!firstCall) {
    initTime = (double)timer->Get();
    firstCall = true;
  }
  if (timer->AdvanceIfElapsed((units::time::second_t)(initTime + t))) {
    firstCall = false;
    return true;
  }
  return false;
}