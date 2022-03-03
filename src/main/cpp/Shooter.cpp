#include "Shooter.h"

Shooter::Shooter() {
  shooter = new WPI_TalonFX(17);
  shooter->SetNeutralMode(NeutralMode::Coast);
  hood = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 10);
}

void Shooter::RunShooter(double speed) { shooter->Set(speed); }
void Shooter::RunHood(bool dir) { hood->Set(dir); }

bool Shooter::GetHoodState() { return hood->Get(); }

double Shooter::GetShooterSpeed() { return shooter->GetSelectedSensorVelocity(); }