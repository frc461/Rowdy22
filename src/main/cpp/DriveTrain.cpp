#include "DriveTrain.h"

DriveTrain::DriveTrain() {
    l1 = new WPI_TalonSRX(0);
    l2 = new WPI_TalonSRX(0);
    r1 = new WPI_TalonSRX(0);
    r2 = new WPI_TalonSRX(0);

    lSide = new frc::MotorControllerGroup(*l1, *l2);
    rSide = new frc::MotorControllerGroup(*r1, *r2);

    driveTrain = new frc::DifferentialDrive(*lSide, *rSide);

    movePID = new PID(0.0, 0.0, 0.0, "move");
}

void DriveTrain::Tank(double l, double r) { driveTrain->TankDrive(l, r); }
void DriveTrain::Arcade(double v, double h) { driveTrain->ArcadeDrive(v, h); }

double DriveTrain::GetEncoderL() { return l1->GetSelectedSensorPosition(); }
double DriveTrain::GetEncoderR() { return r1->GetSelectedSensorPosition(); }

bool DriveTrain::MoveDistance(bool dir, int distance) {
    /*double l = movePID->Get(fabs(GetEncoderL()), fabs(GetEncoderL()) + (double)distance);
    double r = movePID->Get(fabs(GetEncoderR()), fabs(GetEncoderR()) + (double)distance);
    Tank(l, -r);*/
    return true;
}
void DriveTrain::MoveStraight(bool dir, double power) {
    
}
void DriveTrain::Turn(bool dir, double angle) {
    
}