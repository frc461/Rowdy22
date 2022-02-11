#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  bool t = frc::SmartDashboard::GetBoolean("Tank",true);
  
  if (t) {
    lSpeed += (control->LeftY()==0) ? -lSpeed : (control->LeftY()>0) ? 0.05 : (control->LeftY()<0) ? -0.05 : 0.0;
    rSpeed += (control->RightY()==0) ? -rSpeed : (control->RightY()>0) ? 0.05 : (control->RightY()<0) ? -0.05 : 0.0;
    driveTrain->Tank(lSpeed, rSpeed);
  }
  else {
    driveTrain->Arcade(-control->LeftY(),control->RightX());
  }
}
//-------------------------------------------------------------------------Intake-----
void Robot::IntakePeriodic() {
  //intake->RunPush(control->Intake());
  intake->RunMotor((control->Intake()) ? 0.5 : 0.0);
}
//--------------------------------------------------------------------------Conveyor----
void Robot::ConveyorPeriodic() {
  //conveyor->RunHold(!control->Conveyor());
  conveyor->RunMotor((control->Conveyor()) ? 0.5 : 0.0);
}
//--------------------------------------------------------------------------Shooter-----
void Robot::ShooterPeriodic() {
  shooter->RunShooter((control->Shooter()) ? 0.5 : 0.0);
  
  // if (control->ShooterHood()) { hoodState = (hoodState) ? false : true; }
  // shooter->RunHood(hoodState);
}
//-----------------------------------------------------------------------------Climber--
void Robot::ClimberPeriodic() {
  climber->RunLeft((control->ClimberExtend()) ? 0.5 : (control->ClimberRetract()) ? -0.5 : 0.0);
  climber->RunRight((control->ClimberExtend()) ? -0.5 : (control->ClimberRetract()) ? 0.5 : 0.0);
  //climber->RunBrake(!control->ClimberExtend() && !control->ClimberRetract());
  
  // if (control->ClimberTilt()) { tiltState = (tiltState) ? false : true; }
  // climber->RunTilt(tiltState);
  
  // if (control->ClimberGrab()) { grabState = (grabState) ? false : true; }
  // climber->RunGrab(grabState);
}
//--------------------------------------------------------------------------------------


//==================================================
void Robot::RobotInit() {
  control = new Control();
  
  driveTrain = new DriveTrain();
  shooter = new Shooter();
  intake = new Intake();
  climber = new Climber();
  conveyor = new Conveyor();
  // vision = new Vision();
  
  lSpeed = rSpeed = 0.0;
  
  tiltState = grabState = false;
  hoodState = false;

  frc::SmartDashboard::PutBoolean("Tank", true);
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
  IntakePeriodic();
  //ConveyorPeriodic();
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
