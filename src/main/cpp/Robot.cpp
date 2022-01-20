#include "Robot.h"

void Robot::DriveTrainPeriodic() {
  driveTrain->Tank(control->LeftX(), control->RightX(), 0.8);
}
void Robot::IntakePeriodic() {
  if (control->Intake()){
    intake->RunMotor(0.6);
    intake->RunPush(true);
  }else{
    intake->RunMotor(0);
    intake->RunPush(false);
  }
}
void Robot::ConveyorPeriodic() {
  if (control->Conveyor()){
    conveyor->RunHold(false);
    conveyor->RunMotor(0.66);
  }else{
    conveyor->RunHold(true);
  }

}
void Robot::ShooterPeriodic() {
  if(control->Shooter()){
    shooter->RunHood(true);
    shooter->RunShooter(0.66+0.03);
  }else{
    shooter->RunShooter(0.0);
  }

}
void Robot::ClimberPeriodic() {
  //nasty
}

//==================================================
void Robot::RobotInit() {
  control = new Control();
  
  driveTrain = new DriveTrain();
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
