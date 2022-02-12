#pragma once

#include <iostream>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Control.h"
#include "DriveTrain.h"
#include "Climber.h"
#include "Intake.h"
#include "Shooter.h"
#include "Vision.h"
#include "Conveyor.h"
#include "Timer.h"

using namespace::std;

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
  void IntakeConveyorPeriodic();
  void ShooterPeriodic();
  void ClimberPeriodic();
  void AutoOne();

private:
  //------------------------------------------------
  Control *control;
  
  DriveTrain *driveTrain;
  double lSpeed,rSpeed;
  bool ramp;

  Intake *intake;

  
  Climber *climber;
  bool tiltState, grabState;
  
  Shooter *shooter;
  bool hoodState;
  
  Vision *vision;
  
  Conveyor *conveyor;
  //------------------------------------------------
  
  Timer *timer;
  
  //------------------------------------------------
  
  bool shoot1, back1, turn1, back2, turn2, forward1, shoot2;
};
