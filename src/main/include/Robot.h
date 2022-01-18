#pragma once

#include <iostream>
#include <frc/TimedRobot.h>

#include "Control.h"
#include "DriveTrain.h"

class Robot : public frc::TimedRobot {
public:
  //==================================================
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  //==================================================
  
  DriveTrainPeriodic();
  ClimberPeriodic();
  Intake();
  Shooter();

private:
  Control *control;
  DriveTrain *driveTrain;
};
