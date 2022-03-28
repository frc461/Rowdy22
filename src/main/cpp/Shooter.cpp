#include "Shooter.h"

Shooter::Shooter() {
  shooter = new WPI_TalonFX(17);
  shooter->SetNeutralMode(NeutralMode::Coast);
  hoodTall = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 10);
  hoodShort = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 14);
  hoodCounter = new Counter();
}

void Shooter::RunShooter(double speed) { shooter->Set(speed); }
void Shooter::RunHood(int dir) {
  hoodCounter->ResetAll();
  
  hoodTall->Set((dir==1 || dir==2));
  hoodShort->Set((dir!=1));
}

bool Shooter::GetHoodState() { return hoodTall->Get(); }

double Shooter::GetShooterSpeed() { return shooter->GetSelectedSensorVelocity(); }