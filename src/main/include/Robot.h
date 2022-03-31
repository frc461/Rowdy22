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
#define SHOOTER_RPM_TOP 13500 // 7000
#define SHOOTER_RPM_MID 19000 // 10000
#define SHOOTER_RPM_BOT 6700 // 6000

#define CLIMBER_TOP_ENC_1 75000
#define CLIMBER_TOP_ENC_2 85000
#define CLIMBER_BOT_ENC 500

#define CONVEYOR_SPEED 0.8
#define CLIMBER_SPEED 1.0
#define INTAKE_SPEED 0.8

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

  bool WiggleHood();
  
  void Auto(int level, int hood, double delay);

private:
  //------------------------------------------------
  Control *control;
  
  DriveTrain *driveTrain;
  double lSpeed,rSpeed;

  Intake *intake;

  Climber *climber;
  bool climb;
  
  Shooter *shooter;
  int hoodState;
  bool toMid;
  
  Vision *vision;
  PID *aimPID;
  bool aim;
  
  Conveyor *conveyor;
  int numBalls;
  //------------------------------------------------
  
  Counter *counter;
  
  //------------------------------------------------
  bool moveNow, shooterloaded, shot, loaded;
  bool delayed, shoot1, back1, turn1, back2, turn2, forward1, shoot2, shoot3;
  int nTimes;
};
