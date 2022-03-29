#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>
#include <frc/SmartDashboard/SmartDashboard.h>

#include "PID.h"

class Shooter {
public:
  Shooter();
  ~Shooter();
  
  void RunShooter(double speed);
  void RunHood(int dir);
  
  bool GetHoodState();
  
  double GetShooterSpeed();
  
private:
  WPI_TalonFX *shooter;

  frc::Solenoid *hoodTall;
  frc::Solenoid *hoodShort;
};
