#include "Shooter.h"

Shooter::Shooter() {
  motor = new WPI_TalonSRX(0);
  hood = new WPI_TalonSRX(0);
}

void Shooter::RunShooter(double speed) { shooter->Set(speed); }
void Shooter::RunHood(double speed) { hood->Set(speed); }
