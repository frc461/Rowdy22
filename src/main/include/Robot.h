#pragma once

#include <iostream>
#include <vector>
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
#define SHOOTER_RPM_TOP 8400 // 13500
#define SHOOTER_RPM_MID 10000 // (10000 tarmac) (11500 launchpad)
#define SHOOTER_RPM_BOT 6000

#define SHOOTER_RPM_TOP 8400 // 13500
#define SHOOTER_RPM_MID 10000 // bacc tarmac 
#define SHOOTER_RPM_BOT 6000

#define CLIMBER_TOP_ENC_1 75000
#define CLIMBER_TOP_ENC_2 85000
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
  
  bool AutoShoot( double time,      double midSpeed,  bool dummy,   int hood);
  bool AutoMove(  double distance,  double cap,       bool fast,    int dummy);
  bool AutoTurn(  double angle,     double cap,       bool fast,    int dummy);
  
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
  struct Values { double d1,double d2, bool b, int i; };
  typedef bool (Robot::*Moves)(double,double,bool,int);
  std::vector<Moves> moves;
  std::vector<Values> values;
  int index;
  bool bDummy; int iDummy;
  
  bool shooterloaded, loaded, shot, moveNow;
};
