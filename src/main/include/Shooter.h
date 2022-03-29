#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>

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

  PID *speedPID;

  frc::Solenoid *hoodTall;
  frc::Solenoid *hoodShort;
};
