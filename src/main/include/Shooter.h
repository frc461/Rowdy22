#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>

class Shooter {
public:
  Shooter();
  ~Shooter();
  
  void RunShooter(double speed);
  void RunHood(bool dir);
  
  bool GetHoodState();
  
private:
  WPI_TalonFX *shooter;

  frc::Solenoid *hood;
};
