#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  bool t = GET_BOOL("Tank", true);
  bool ramp = GET_BOOL("Ramp",false);
  
  if (t) {
    if (driveTrain->GetLeftVelocity() > 7500 || !ramp) {
      driveTrain->Tank(-control->LeftY(), control->RightY());
    }
    else if (driveTrain->GetLeftVelocity() < 7500 && ramp) {
      double increment = .015;
      lSpeed = (control->LeftY()>0) ? std::min(lSpeed+increment, control->LeftY()) : (control->LeftY()<0) ? std::max(lSpeed-increment, control->LeftY()) : 0.0;
      rSpeed = (control->RightY()>0) ? std::min(rSpeed+increment, control->RightY()) : (control->RightY()<0) ? std::max(rSpeed-increment, control->RightY()) : 0.0;
      driveTrain->Tank(-lSpeed, rSpeed);
    }
    driveTrain->Tank(-control->LeftY(),control->RightY());
  }
  else {
    driveTrain->Arcade(-control->LeftY(),control->RightX());
  }
}
//-------------------------------------------------------------------------Intake-----
void Robot::IntakeConveyorPeriodic()  {
  double speed = 0.8;
  intake->RunMotor((control->IntakeConveyor()) ? speed : (control->IntakeConveyorR()) ? -speed : 0.0);
  conveyor->RunMotor((control->IntakeConveyor() || control->Conveyor()) ? speed : (control->IntakeConveyorR()) ? -speed : 0.0);

  conveyor->RunHold(control->Conveyor() && control->Shooter());

  if (control->IntakePush()) { intake->RunPush((intake->GetPushState()) ? false : true); }
}
//--------------------------------------------------------------------------Shooter-----
void Robot::ShooterPeriodic() {
  shooter->RunShooter((control->Shooter()) ? (hoodState) ? GET_NUM("HighSpeed", SHOOTER_SPEED_TOP) : GET_NUM("LowSpeed", SHOOTER_SPEED_BOT) : 0.0);
  
  if (control->ShooterHood()) { 
    hoodState = (hoodState) ? false : true;
    climb = false;
  }
  shooter->RunHood((climb) ? true : hoodState);
}
//-----------------------------------------------------------------------------Climber--
void Robot::ClimberPeriodic() {
  double speed = 1.0;
  climber->RunLeft((control->ClimberExtend() && climber->GetBotLimit()) ? speed : (control->ClimberRetract() && climber->GetTopLimit()) ? -speed : 0.0);
  climber->RunRight((control->ClimberExtend() && climber->GetBotLimit()) ? -speed : (control->ClimberRetract() && climber->GetTopLimit()) ? speed : 0.0);
  climber->RunBrake(!((!control->ClimberExtend() && !control->ClimberRetract()) || (!climber->GetBotLimit() && !control->ClimberRetract()) || (!climber->GetTopLimit() && !control->ClimberExtend())));

  if (control->ClimberExtend() || control->ClimberRetract()) climb = true;

  PUT_BOOL("t",climber->GetTopLimit());
  PUT_BOOL("b",climber->GetTopLimit());

  if (control->ClimberTilt()) { climber->RunTilt((climber->GetTiltState()) ? false : true); climb = true; }
  if (control->ClimberGrab()) { climber->RunGrab((climber->GetGrabState()) ? false : true); climb = true; }
}
//--------------------------------------------------------------------------------Vision---------
void Robot::VisionPeriodic() {
  PUT_NUM("Gyro",driveTrain->GetAngle());
  PUT_NUM("topSensor",conveyor->GetBallSensorState(true));
  PUT_NUM("bottomSensor",conveyor->GetBallSensorState(false));
  PUT_NUM("CLIMBER",climber->GetEncoder());
}
//-----------------------------------------------------------------------------------------
//====================================================================================================================================================
void Robot::RobotInit() {
  control = new Control();
  
  driveTrain = new DriveTrain();
  shooter = new Shooter();
  intake = new Intake();
  climber = new Climber();
  conveyor = new Conveyor();
  //vision = new Vision();

  driveTrain->CalibrateGyro();

  lSpeed = rSpeed = 0.0;

  climb = false;
  hoodState = false;

  PUT_BOOL("Tank", true);
  PUT_BOOL("Ramp", false);
  PUT_NUM("HighSpeed", SHOOTER_SPEED_TOP);
  PUT_NUM("LowSpeed", SHOOTER_SPEED_BOT);
  PUT_NUM("Auto", 2);
  PUT_NUM("p", 0.0007);
}

void Robot::AutonomousInit() {
  counter = new Counter();
  counter->Start();

  driveTrain->ResetEncoder();
  driveTrain->ResetGyro();

  loaded = true;

  done = shoot1 = back1 = forward1 = shoot2 = false; // CURRENT AUTO ORDER
  turn1 = back2 = turn2 = false;
}
void Robot::Auto(int level, bool high) {
  if (!shoot1) {
    shooter->RunHood(high);   shooter->RunShooter((high) ? SHOOTER_SPEED_TOP : SHOOTER_SPEED_BOT);
    conveyor->RunHold(true);  conveyor->RunMotor(0.8);
    if (loaded && !conveyor->GetBallSensorState(true)) {
      //std::cout << shoot2 << std::endl;
      loaded = false;
      shooter->RunShooter(0.0);
      conveyor->RunMotor(0.0); conveyor->RunHold(false);
      shoot1 = true;
    }
  }
  else if (shoot1 && !back1) {
    //(level==1) ? driveTrain->MoveDistance(-110.0) : driveTrain->Arcade(-0.6, 0.0);
    if (level != 1) {
      intake->RunPush(true);
      intake->RunMotor(0.8);
      conveyor->RunMotor(0.8);
    }
    if (driveTrain->MoveDistance((level==1) ? -110.0 : -110.0)) {
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      intake->RunPush(false); intake->RunMotor(0.0);
      back1 = true;
    }
  }
  else if (back1 && !forward1 && level != 1) {
    loaded = conveyor->GetBallSensorState(true);
    conveyor->RunMotor((!loaded) ? 0.8 : 0.0);
    if (driveTrain->MoveDistance(110.0)) { // distanceToMove
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      forward1 = true;
    }
  }
  else if (forward1 && !shoot2) {
    counter->ResetAll();
    shoot1 = shoot2 = true;
  }
}
void Robot::AutonomousPeriodic() {
  Auto(GET_NUM("Auto", 2), true);
}

void Robot::TeleopInit() {
  
}

void Robot::TeleopPeriodic() {
  DriveTrainPeriodic();
  IntakeConveyorPeriodic();
  ShooterPeriodic();
  ClimberPeriodic();
  VisionPeriodic();
  // if (control->Shooter()) std::cout << driveTrain->MoveDistance(-40) << std::endl;
  // if (control->IntakeConveyor()) driveTrain->ResetEncoder();
}

void Robot::RobotPeriodic() {}
void Robot::DisabledInit() {
  climber->RunBrake(true);
}
void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
//====================================================================================================================================================
