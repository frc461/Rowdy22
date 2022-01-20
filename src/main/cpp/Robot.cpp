#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  driveTrain->Tank(control->LeftX(), control->RightX(), 1.0);
}
//-------------------------------------------------------------------------Intake-----
void Robot::IntakePeriodic() {
  if (control->Intake()){
    intake->RunMotor(0.5);
    intake->RunPush(true);
  }
  else{
    intake->RunMotor(0);
    intake->RunPush(false);
  }
}
//--------------------------------------------------------------------------Conveyor----
void Robot::ConveyorPeriodic() {
  if (control->Conveyor()){
    conveyor->RunHold(false);
    conveyor->RunMotor(0.5);
  }
  else{
    conveyor->RunHold(true);
    conveyor->RunMotor(0.0);
  }
}
//--------------------------------------------------------------------------Shooter-----
void Robot::ShooterPeriodic() {
  if(control->Shooter()){
    shooter->RunHood(true);
    shooter->RunShooter(0.5);
  }
  else{
    shooter->RunShooter(0.0);
  }
}
//-----------------------------------------------------------------------------Climber-
void Robot::ClimberPeriodic() {
  if (control->ClimberExtend()) {
    climber->RunLeft(0.5);
    climber->RunRight(0.5);
    climber->RunBrake(false);
  }
  else if (control->ClimberRetract()) {
    climber->RunLeft(-0.5);
    climber->RunRight(-0.5);
    climber->RunBrake(false);
  }
  else {
    climber->RunBrake(true);
  }
  
  if (control->ClimberTilt()) {
    if (!tiltState) tiltState = true;
    else tiltState = false;
  }
  climber->RunTilt(tiltState);
  
  if (control->ClimberGrab()) {
    if (!grabState) grabState = true;
    else grabState = false;
  }
  climber->RunGrab(grabState);
}
//--------------------------------------------------------------------------------------


//==================================================
void Robot::RobotInit() {
  control = new Control();
  
  driveTrain = new DriveTrain();
  
  tiltState = false;
}

void Robot::AutonomousInit() {

}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
  
}

void Robot::TeleopPeriodic() {
  DriveTrainPeriodic();
  IntakePeriodic();
  ConveyorPeriodic();
  ShooterPeriodic();
  ClimberPeriodic();
}

void Robot::RobotPeriodic() {}
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
//==================================================
