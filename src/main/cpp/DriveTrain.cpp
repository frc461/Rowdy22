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
    turnPID = new PID(0.0, 0.0, 0.0, "turn");
}

void DriveTrain::Tank(double l, double r, double min, double max) { driveTrain->TankDrive(l*max, r*max); }
void DriveTrain::Arcade(double v, double h, double min, double max) { driveTrain->ArcadeDrive(v*max, h*max); }

double DriveTrain::GetEncoderL() { return l1->GetSelectedSensorPosition(); }
double DriveTrain::GetEncoderR() { return r1->GetSelectedSensorPosition(); }
double DriveTrain::GetAngle() { return gyro->GetAngle(); }

void DriveTrain::ResetEncoder() {  }
void DriveTrain::ResetGyro() {  }

bool DriveTrain::MoveDistance(int distance) {
    double l = movePID->Get(fabs(GetEncoderL()), fabs(GetEncoderL()) + (double)distance);
    double r = movePID->Get(fabs(GetEncoderR()), fabs(GetEncoderR()) + (double)distance);
    Tank(l, -r, 0.0, 1.0);
    return true;
}
bool DriveTrain::Turn(double angle) {
    double speed = turnPID->Get(GetAngle(), GetAngle() + angle);
    Tank(speed, -speed, 0.0, 1.0);
    return true;
}
void DriveTrain::MoveStraight(double power) {
    Arcade(power, -(GetAngle() / 7.5), 0.0, 1.0);
}
