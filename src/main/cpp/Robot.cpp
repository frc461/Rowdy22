#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  bool t = frc::SmartDashboard::GetBoolean("Tank",true);
  bool ramp = frc::SmartDashboard::GetBoolean("Ramp",true);
  
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
  }
  else {
    driveTrain->Arcade(-control->LeftY(),control->RightX());
  }
}
//-------------------------------------------------------------------------Intake-----
void Robot::IntakeConveyorPeriodic()  {
  double speed = 0.8;
  intake->RunMotor((control->IntakeConveyor()) ? speed : (control->IntakeConveyorR()) ? -speed : 0.0);
  conveyor->RunMotor((control->IntakeConveyor()) ? speed : (control->IntakeConveyorR()) ? -speed : 0.0);

  if(control->IntakeOut()) intake->RunPush(0); else if(control->IntakeIn()) intake->RunPush(1);

  if(control->Hold()){
    fingerstate = (fingerstate) ? false: true;
    conveyor->RunHold(fingerstate);
  }
}
//--------------------------------------------------------------------------Shooter-----
void Robot::ShooterPeriodic() {
  shooter->RunShooter((control->Shooter()) ? frc::SmartDashboard::GetNumber("ShootaSPeed", 0.7) : 0.0);
  
  if (control->ShooterHood()) { hoodState = (hoodState) ? false : true; }
  shooter->RunHood(hoodState);
}
//-----------------------------------------------------------------------------Climber--
void Robot::ClimberPeriodic() {
  double speed = 0.8;
  climber->RunLeft((control->ClimberExtend()) ? speed : (control->ClimberRetract()) ? -speed : 0.0);
  climber->RunRight((control->ClimberExtend()) ? -speed : (control->ClimberRetract()) ? speed : 0.0);
  climber->RunBrake(!control->ClimberExtend() && !control->ClimberRetract());
  
  if (control->ClimberTilt()) { tiltState = (tiltState) ? false : true; }
  climber->RunTilt(tiltState);
  
  if (control->ClimberGrab()) { grabState = (grabState) ? false : true; }
  climber->RunGrab(grabState);
}
//------------------------------------------
//==================================================
void Robot::RobotInit() {
  control = new Control();
  
  driveTrain = new DriveTrain();
  shooter = new Shooter();
  intake = new Intake();
  climber = new Climber();
  conveyor = new Conveyor();
  // vision = new Vision();

  driveTrain->ResetEncoder();
  lSpeed = rSpeed = 0.0;
  
  tiltState = grabState = false;
  hoodState = false;

  frc::SmartDashboard::PutBoolean("Tank", true);
  frc::SmartDashboard::PutBoolean("Ramp", true);
  frc::SmartDashboard::PutNumber("ShootaSPeed", 0.7);
}

void Robot::AutonomousInit() {
  //timer = new Timer();
  //timer->Start();
  shoot1 = back1 = turn1 = back2 = turn2 = forward1 = shoot2 = false;
}
void Robot::AutoOne(){
  // if (!shoot1) {
  //   shooter->RunShooter(0.5);
  //   shooter->RunHood(false);
  //   conveyor->RunMotor(0.5);
  //   if (timer->SecondsPassed(1.0)) shoot1 = true;
  // }
  // else if (shoot1 && !back1) {
  //   shooter->RunHood(0.0);
  //   conveyor->RunMotor(0.0);
  //   intake->RunPush(true);
  //   intake->RunMotor(0.5);
  //   if (driveTrain->MoveDistance(/* */)) back1 = true;
  // }
  // else if (back1 && !turn1) {
  //   if (driveTrain->Turn(/* */)) turn1 = true;
  // }
  // else if (turn1 && !back2) {
  //   if (driveTrain->MoveDistance(/* */)) back2 = true;
  // }
  // else if (back1 && turn2) {
  //   if (driveTrain->Turn(/* */)) turn2 = true;
  // }
  // else if (turn2 && !forward1) {
  //   if (driveTrain->MoveDistance(/* */)) forward1 = true;
  // }
  // else if (forward1) {
  //   shoot1 = false;
  // }
}
void Robot::AutonomousPeriodic() {
  AutoOne();
}

void Robot::TeleopInit() {
  
}

void Robot::TeleopPeriodic() {
  DriveTrainPeriodic();
  IntakeConveyorPeriodic();
  ShooterPeriodic();
  ClimberPeriodic();
}

void Robot::RobotPeriodic() {}
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
//==================================================
