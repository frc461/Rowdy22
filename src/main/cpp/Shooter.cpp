#include "Shooter.h"

Shooter::Shooter() {
  shooter = new WPI_TalonFX(17);
  shooter->SetNeutralMode(NeutralMode::Coast);
  hoodTall = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 10);
  hoodShort = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 14);

  speedPID = new PID(0.0004, 0.0, 0.0, "shoot");
}

void Shooter::RunShooter(double speed) {
  if (speed != 0) {
    double power = speedPID->Get(GetShooterSpeed(), speed);
    shooter->Set((power>=0.0) ? power : 0.0);
  }
  else {
    speedPID->Reset();
    shooter->Set(0.0);
  }
}
void Shooter::RunHood(int dir) {
  hoodTall->Set((dir==1 || dir==2));
  hoodShort->Set((dir!=1));
}

bool Shooter::GetHoodState() { return hoodTall->Get(); }

double Shooter::GetShooterSpeed() { return shooter->GetSelectedSensorVelocity(); }