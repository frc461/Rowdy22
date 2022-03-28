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
#define SHOOTER_SPEED_TOP 0.65
#define SHOOTER_SPEED_BOT 0.35
#define SHOOTER_SPEED_MID 1.00

#define SHOOTER_RPM_TOP 13500
#define SHOOTER_RPM_BOT 6700

#define SHOOTER_SPEED_TOP_AUTO 0.69
#define SHOOTER_SPEED_BOT_AUTO 0.35

#define CLIMBER_TOP_ENC_1 75000
#define CLIMBER_TOP_ENC_2 85000//60000
#define CLIMBER_BOT_ENC 500

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
  bool climberMoveDown;
  bool climberDelay;
  
  Shooter *shooter;
  int hoodState;
  bool loaded;
  bool toMid;
  
  Vision *vision;
  PID *aimPID;
  bool aim;
  
  Conveyor *conveyor;
  int numBalls;
  //------------------------------------------------
  
  Counter *counter;
  
  //------------------------------------------------
  
  bool delayed;
  bool moveNow;
  bool shooterloaded;
  bool shot;
  bool shoot1, back1, turn1, back2, turn2, forward1, shoot2, shoot3;
  int nTimes;
  bool thirdPickedUp;
};
