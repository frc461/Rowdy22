#include "DriveTrain.h"

DriveTrain::DriveTrain() {
    l1 = new WPI_TalonFX(0);
    l2 = new WPI_TalonFX(0);
    r1 = new WPI_TalonFX(0);
    r2 = new WPI_TalonFX(0);

    lSide = new frc::MotorControllerGroup(*l1, *l2);
    rSide = new frc::MotorControllerGroup(*r1, *r2);

    driveTrain = new frc::DifferentialDrive(*lSide, *rSide);

    gyro = new frc::ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0);

    movePID = new PID(0.0, 0.0, 0.0, "move");
}

void DriveTrain::Tank(double l, double r, double speedCap) { driveTrain->TankDrive(l*speedCap, r*speedCap); }
void DriveTrain::Arcade(double v, double h, double speedCap) { driveTrain->ArcadeDrive(v*speedCap, h*speedCap); }

double DriveTrain::GetEncoderL() { return l1->GetSelectedSensorPosition(); }
double DriveTrain::GetEncoderR() { return r1->GetSelectedSensorPosition(); }
double DriveTrain::GetAngle() { return gyro->GetAngle(); }

bool DriveTrain::MoveDistance(bool dir, int distance) {
    double l = movePID->Get(fabs(GetEncoderL()), fabs(GetEncoderL()) + (double)distance);
    double r = movePID->Get(fabs(GetEncoderR()), fabs(GetEncoderR()) + (double)distance);
    Tank(l, -r, 1.0);
    return true;
}
void DriveTrain::MoveStraight(bool dir, double power) {
    
}
void DriveTrain::Turn(bool dir, double angle) {
    
}