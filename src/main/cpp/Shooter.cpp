#include "Shooter.h"

Shooter::Shooter() {
  shooter = new WPI_TalonFX(17);
  hoodTall = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 10);
  hoodShort = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 14);
  
  shooter->SetNeutralMode(NeutralMode::Coast);
  shooter->ConfigFactoryDefault();
  shooter->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0);
  shooter->Config_kF(0, 0.05);
  shooter->Config_kP(0, 0);
  shooter->Config_kI(0, 0);
  shooter->Config_kD(0, 0);
  
  frc::SmartDashboard::PutNumber("f",0.05);
  frc::SmartDashboard::PutNumber("p",0.0);
  frc::SmartDashboard::PutNumber("i",0.0);
  frc::SmartDashboard::PutNumber("d",0.0);
}

void Shooter::RunShooter(double speed) {
  shooter->Config_kF(0, frc::SmartDashboard::GetNumber("f",0.05));
  shooter->Config_kP(0, frc::SmartDashboard::GetNumber("p",0.0));
  shooter->Config_kI(0, frc::SmartDashboard::GetNumber("i",0.0));
  shooter->Config_kD(0, frc::SmartDashboard::GetNumber("d",0.0));
  
  shooter->Set(ControlMode::Velocity, speed);
}
void Shooter::RunHood(int dir) {
  hoodTall->Set((dir==1 || dir==2));
  hoodShort->Set((dir!=1));
}

bool Shooter::GetHoodState() { return hoodTall->Get(); }
double Shooter::GetShooterSpeed() { return shooter->GetSelectedSensorVelocity(); }
