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

    movePID = new PID(0.5, 0.0, 0.0, "move");
    turnPID = new PID(0.5, 0.0, 0.0, "turn");
    
    max = 1.0;
    
    crossedMove = false;
    sumMove = 0.0;
    nMove = 0;
}

void DriveTrain::Tank(double l, double r) { driveTrain->TankDrive(l*max, r*max); }
void DriveTrain::Arcade(double v, double h) { driveTrain->ArcadeDrive(v*max, h*max); }

double DriveTrain::GetEncoderL() { return l1->GetSelectedSensorPosition(); }
double DriveTrain::GetEncoderR() { return r1->GetSelectedSensorPosition(); }
double DriveTrain::GetAngle() { return gyro->GetAngle(); }

void DriveTrain::ResetEncoder() { l1->SetSelectedSensorPosition(0.0); r1->SetSelectedSensorPosition(0.0); }
void DriveTrain::ResetGyro() { gyro->Reset(); }

bool DriveTrain::MoveDistance(double distance) {
    double l = movePID->Get(GetEncoderL(), distance);
    double r = movePID->Get(GetEncoderR(), -distance);
    Tank(l, r);
    
    if (fabs(GetEncoderL()) >= fabs(distance) && !crossedMove) crossedMove = true;
    if (crossedMove) {
        sumMove += fabs(GetEncoderL());
        nMove++;
        
        if (fabs(GetEncoderL()) - (sumMove / (double)nMove) < 1.0) return true; 
    }
    return false;
}
void DriveTrain::ResetMoveVars() {
    ResetEncoder();
    crossedMove = false;
    sumMove = 0.0;
    nMove = 0;
}

bool DriveTrain::Turn(double angle) {
    double speed = turnPID->Get(GetAngle(), GetAngle() + angle);
    Tank(speed, -speed);
    return false;
}
void DriveTrain::MoveStraight(double power) {
    Arcade(power, -(GetAngle() / 7.5));
}
