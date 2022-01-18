#include "Robot.h"

DriveTrainPeriodic() {
  driveTrain->Tank(control->LeftX(), control->RightX, 0.8);
}
ClimberPeriodic() {
  
}
Intake() {
  
}
Shooter() {
  
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

}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
//==================================================
