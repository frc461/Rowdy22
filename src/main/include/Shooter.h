#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>

#include <Counter.h>

class Shooter {
public:
  Shooter();
  ~Shooter();

  Counter *hoodCounter;
  
  void RunShooter(double speed);
  void RunHood(int dir);
  
  bool GetHoodState();
  
  double GetShooterSpeed();
  
private:
  WPI_TalonFX *shooter;

  frc::Solenoid *hoodTall;
  frc::Solenoid *hoodShort;
};
