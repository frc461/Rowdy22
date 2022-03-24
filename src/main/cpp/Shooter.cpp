#include "Shooter.h"

Shooter::Shooter() {
  shooter = new WPI_TalonFX(17);
  shooter->SetNeutralMode(NeutralMode::Coast);
  hoodTall = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 10);
  hoodShort = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 14);
}

void Shooter::RunShooter(double speed) { shooter->Set(speed); }
void Shooter::RunHood(int dir) { 
  if(dir == 0) {
    hoodTall->Set(1);
    hoodShort->Set(0);
  } else if (dir == 1) {
    hoodTall->Set(0);
    hoodShort->Set(1);
  } else if (dir == 2) {
    hoodTall->Set(1);
    hoodShort->Set(1);
  } else {
    hoodTall->Set(0);
    hoodShort->Set(1);
  }
   
}

bool Shooter::GetHoodState() { return hoodTall->Get(); }

double Shooter::GetShooterSpeed() { return shooter->GetSelectedSensorVelocity(); }