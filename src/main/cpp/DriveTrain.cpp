#include "DriveTrain.h"

DriveTrain::DriveTrain() {
    l1 = new WPI_TalonFX(11);
    l2 = new WPI_TalonFX(12);
    r1 = new WPI_TalonFX(13);
    r2 = new WPI_TalonFX(14);

    lSide = new frc::MotorControllerGroup(*l1, *l2);
    rSide = new frc::MotorControllerGroup(*r1, *r2);

    driveTrain = new frc::DifferentialDrive(*lSide, *rSide);

    leftEncoder = new frc::Encoder(0,1);
    rightEncoder = new frc::Encoder(2,3);
    
    l1->SetNeutralMode(NeutralMode::Coast);
    l2->SetNeutralMode(NeutralMode::Coast);
    r1->SetNeutralMode(NeutralMode::Coast);
    r2->SetNeutralMode(NeutralMode::Coast);

    gyro = new frc::ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0);

    movePID = new PID(0.0007, 0.0, 0.0, "move");
    turnPID = new PID(0.07, 0.0, 0.0, "turn");

    max = 1.0;
}

void DriveTrain::Tank(double l, double r) { driveTrain->TankDrive(l*max, r*max); }
void DriveTrain::Arcade(double v, double h) { driveTrain->ArcadeDrive(h*max, v*max); }

double DriveTrain::GetEncoderL() { return leftEncoder->GetRaw(); }
double DriveTrain::GetEncoderR() { return rightEncoder->GetRaw(); }
double DriveTrain::GetAngle() { return gyro->GetAngle(); }
double DriveTrain::GetLeftVelocity() { return l1->GetSelectedSensorVelocity(); }
double DriveTrain::GetRightVelocity() { return r1->GetSelectedSensorVelocity(); }

void DriveTrain::ResetEncoder() { leftEncoder->Reset(); rightEncoder->Reset(); }
void DriveTrain::ResetGyro() { gyro->Reset(); }
void DriveTrain::CalibrateGyro() { gyro->Calibrate(); }

void DriveTrain::MoveStraight(double power) {
    Arcade(power, -(GetAngle() / 6.0));
}

bool DriveTrain::MoveDistance(double distance, double cap, bool fast) {
    double power = std::min(movePID->Get(fabs(GetEncoderL()), fabs(distance * ENC_PER_INCH)), cap);
    power *= (distance < 0) ? -1 : 1;
    MoveStraight(power);

    return (fabs(GetEncoderL()) >= (fabs(distance * ENC_PER_INCH) / 4)) && ((fast) ? fabs(GetLeftVelocity())<100 : fabs(GetLeftVelocity())==0);
}
void DriveTrain::ResetMoveVars() { ResetEncoder(); movePID->Reset(); }

bool DriveTrain::Turn(double angle, bool fast) {
    double speed = std::min(turnPID->Get(fabs(GetAngle()), fabs(angle)), 0.6);
    speed *= (angle<0) ? -1 : 1;
    Tank(speed,speed);

    // ((fast) ? fabs(GetLeftVelocity())<50 : fabs(GetLeftVelocity())==0)
    return (fabs(GetAngle()) >= (fabs(angle)/4.0)) && fabs(GetLeftVelocity())==0;
}
void DriveTrain::ResetTurnVars() { ResetGyro(); turnPID->Reset(); }