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

#include "Counter.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SHOOTER_SPEED_TOP 0.7
#define SHOOTER_SPEED_BOT 0.35

#define SHOOTER_SPEED_TOP_AUTO 0.7
#define SHOOTER_SPEED_BOT_AUTO 0.35

#define CLIMBER_TOP_ENC 500
#define CLIMBER_BOT_ENC 0

#define PUT_BOOL(name,val) frc::SmartDashboard::PutBoolean(name,val)
#define GET_BOOL(name,val) frc::SmartDashboard::GetBoolean(name,val)
#define PUT_NUM(name,val) frc::SmartDashboard::PutNumber(name,val)
#define GET_NUM(name,val) frc::SmartDashboard::GetNumber(name,val)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
  void VisionPeriodic();
  
  void Auto(int level, bool high);

private:
  //------------------------------------------------
  Control *control;
  
  DriveTrain *driveTrain;
  double lSpeed,rSpeed;

  Intake *intake;

  Climber *climber;
  bool climb;
  
  Shooter *shooter;
  bool hoodState;
  bool loaded;
  double distanceToMove;
  
  Vision *vision;
  
  Conveyor *conveyor;
  //------------------------------------------------
  
  Counter *counter;
  
  //------------------------------------------------
  
  bool done;
  bool moveNow;
  bool shooterloaded;
  bool shot;
  bool shoot1, back1, turn1, back2, turn2, forward1, shoot2;
};
