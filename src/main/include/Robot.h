#pragma once

#include <iostream>
#include <frc/TimedRobot.h>

#include "Control.h"
#include "DriveTrain.h"
#include "Climber.h"
#include "Intake.h"
#include "Shooter.h"
#include "Vision.h"
#include "Conveyor.h"

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
  
  void DriveTrainPeriodic();
  void IntakePeriodic();
  void ConveyorPeriodic();
  void ShooterPeriodic();
  void ClimberPeriodic();

private:
  Control *control;
  
  DriveTrain *driveTrain;
  
  Intake *intake;
  
  Climber *climber;
  bool tiltState, grabState;
  
  Shooter *shooter;
  
  Vision *vision;
  
  Conveyor *conveyor;
  
};
