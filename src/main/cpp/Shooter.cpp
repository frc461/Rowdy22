#include "Shooter.h"

Shooter::Shooter() {
  motor = new WPI_TalonSRX(0);
  hood = new WPI_TalonSRX(0);
}

void Shooter::MoveMotor(bool dir, double speed) { motor->Set((dir) ? speed : -speed)); }
void Shooter::MoveHood(bool dir, double speed) { hood->Set((dir) ? speed : -speed)); }
