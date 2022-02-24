#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  bool t = frc::SmartDashboard::GetBoolean("Tank", true);
  bool ramp = frc::SmartDashboard::GetBoolean("Ramp",false);
  
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
    driveTrain->Arcade(control->LeftY(),control->RightX());
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
  shooter->RunShooter((control->Shooter()) ? (hoodState) ? frc::SmartDashboard::GetNumber("HighSpeed", SHOOTER_SPEED_TOP) : frc::SmartDashboard::GetNumber("LowSpeed", SHOOTER_SPEED_BOT) : 0.0);
  
  if (control->ShooterHood()) { 
    hoodState = (hoodState) ? false : true;
    climb = false;
  }
  shooter->RunHood((climb) ? true : hoodState);
}
//-----------------------------------------------------------------------------Climber--
void Robot::ClimberPeriodic() {
  double speed = 0.8;
  climber->RunLeft((control->ClimberExtend() && climber->GetBotLimit()) ? speed : (control->ClimberRetract() && climber->GetTopLimit()) ? -speed : 0.0);
  climber->RunRight((control->ClimberExtend() && climber->GetBotLimit()) ? -speed : (control->ClimberRetract() && climber->GetTopLimit()) ? speed : 0.0);
  climber->RunBrake(!((!control->ClimberExtend() && !control->ClimberRetract()) || (!climber->GetBotLimit() && !control->ClimberRetract()) || (!climber->GetTopLimit() && !control->ClimberExtend())));

  if (control->ClimberExtend() || control->ClimberRetract()) climb = true;

  frc::SmartDashboard::PutBoolean("t",climber->GetTopLimit());
  frc::SmartDashboard::PutBoolean("b",climber->GetBotLimit());

  if (control->ClimberTilt()) { climber->RunTilt((climber->GetTiltState()) ? false : true); }
  if (control->ClimberGrab()) { climber->RunGrab((climber->GetGrabState()) ? false : true); }
}
//--------------------------------------------------------------------------------Vision---------
void Robot::VisionPeriodic() {
  frc::SmartDashboard::PutNumber("gyro",driveTrain->GetAngle());
  std::cout << driveTrain->GetEncoderL() << " " << driveTrain->GetEncoderR() << std::endl;
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

  frc::SmartDashboard::PutBoolean("Tank", true);
  frc::SmartDashboard::PutBoolean("Ramp", false);
  frc::SmartDashboard::PutNumber("HighSpeed", SHOOTER_SPEED_TOP);
  frc::SmartDashboard::PutNumber("LowSpeed", SHOOTER_SPEED_BOT);
  frc::SmartDashboard::PutNumber("p", 0.0002);
}

void Robot::AutonomousInit() {
  counter = new Counter();
  counter->Start();

  driveTrain->ResetEncoder();
  driveTrain->ResetGyro();

  shoot1 = back1 = turn1 = back2 = turn2 = forward1 = shoot2 = false;
}
void Robot::Auto(int level){
  if (!shoot1) {
    shooter->RunShooter(SHOOTER_SPEED_BOT);
    shooter->RunHood(false);
    conveyor->RunMotor(0.5);
    conveyor->RunHold(true);
    if (counter->SecondsPassed(3.0)) {
      shooter->RunShooter(0.0);
      conveyor->RunMotor(0.0);
      conveyor->RunHold(false);
      shoot1 = true;
    }
  }
  else if (shoot1 && !back1) {
    if (level != 1) {
      intake->RunPush(true);
      intake->RunMotor(0.5);
    }
    if (driveTrain->MoveDistance((level==1) ? -50.0 : -24.0)) {
      back1 = true;
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
    }
  }
  else if (back1 && !turn1 && level != 1) {
    if (driveTrain->Turn(0)) {
      turn1 = true;
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
    }
  }
  else if (turn1 && !back2) {
    if (driveTrain->MoveDistance(0)) {
      back2 = true;
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
    }
  }
  else if (back2 && !turn2) {
    if (driveTrain->Turn(0)) {
      turn2 = true;
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
    }
  }
  else if (turn2 && !forward1) {
    if (driveTrain->MoveDistance(0)) {
      forward1 = true;
      intake->RunPush(false);
      intake->RunMotor(0.0);
    }
  }
  else if (forward1) {
    shoot1 = false;
  }
}
void Robot::AutonomousPeriodic() {
  Auto(1);
}

void Robot::TeleopInit() {
  
}

void Robot::TeleopPeriodic() {
  // DriveTrainPeriodic();
  // IntakeConveyorPeriodic();
  // ShooterPeriodic();
  // ClimberPeriodic();
  // VisionPeriodic();
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
