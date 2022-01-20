#include "Shooter.h"

Shooter::Shooter() {
  shooter = new WPI_TalonFX(0);
  hood = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 0);
}

void Shooter::RunShooter(double speed) { shooter->Set(speed); }
void Shooter::RunHood(bool dir) { hood->Set(dir); }