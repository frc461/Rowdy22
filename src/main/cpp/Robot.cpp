#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  driveTrain->Tank(control->LeftX(), control->RightX(), 0.0, 1.0);
}
//-------------------------------------------------------------------------Intake-----
void Robot::IntakePeriodic() {
  intake->RunPush(control->Intake());
  intake->RunMotor((control->Intake()) ? 0.5 : 0.0);
}
//--------------------------------------------------------------------------Conveyor----
void Robot::ConveyorPeriodic() {
  conveyor->RunHold(!control->Conveyor());
  conveyor->RunMotor((control->Conveyor()) ? 0.5 : 0.0);
}
//--------------------------------------------------------------------------Shooter-----
void Robot::ShooterPeriodic() {
  shooter->RunShooter((control->Shooter()) ? 0.5 : 0.0);
  
  if (control->ShooterHood()) { hoodState = (hoodState) ? false : true; }
  shooter->RunHood(hoodState);
}
//-----------------------------------------------------------------------------Climber--
void Robot::ClimberPeriodic() {
  climber->RunLeft((control->ClimberExtend()) ? 0.5 : (control->ClimberRetract()) ? -0.5 : 0.0);
  climber->RunRight((control->ClimberExtend()) ? 0.5 : (control->ClimberRetract()) ? -0.5 : 0.0);
  climber->RunBrake(!control->ClimberExtend() && !control->ClimberRetract());
  
  if (control->ClimberTilt()) { tiltState = (tiltState) ? false : true; }
  climber->RunTilt(tiltState);
  
  if (control->ClimberGrab()) { grabState = (grabState) ? false : true; }
  climber->RunGrab(grabState);
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
  vision = new Vision();
  
  tiltState = grabState = false;
  hoodState = false;

  frc::SmartDashboard::PutBoolean("Tank", true);
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
int main() { return frc::StartRobot<Robot>(); }
#endif
//==================================================
