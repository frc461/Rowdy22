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

    movePID = new PID(0.000575, 0.0, 0.0, "move");
    turnPID = new PID(0.01, 0.0, 0.0, "turn");

    max = 1.0;
    
    crossedMove = crossedTurn = false;
    sumMove = sumTurn = 0.0;
    nMove = nTurn = 0;
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

bool DriveTrain::MoveDistance(double distance) {
    //movePID->SetP(frc::SmartDashboard::GetNumber("p", 0.000575));
    double power = std::min(movePID->Get(fabs(GetEncoderL()), fabs(distance * ENC_PER_INCH)), 0.6);
    power *= (distance < 0) ? -1 : 1;
    
    Tank(power, -power);
    
    return (fabs(GetEncoderL() >= fabs(distance * ENC_PER_INCH) / 2) && (fabs(GetLeftVelocity()) <= 10);
    // if (fabs(GetEncoderL()) >= fabs(distance * ENC_PER_INCH) && !crossedMove) crossedMove = true;
    // if (crossedMove) {
    //     sumMove += fabs(GetEncoderL());
    //     nMove++;
    //     //frc::SmartDashboard::PutNumber("mov", fabs((sumMove / (double)nMove) - fabs(distance * ENC_PER_INCH)));
    //     if (fabs((sumMove / (double)nMove) - fabs(distance * ENC_PER_INCH)) < ENC_PER_INCH*3) return true; 
    // }
    // return false;
}
void DriveTrain::ResetMoveVars() {
    ResetEncoder();
    movePID->Reset();
    crossedMove = false;
    sumMove = 0.0;
    nMove = 0;
}

bool DriveTrain::Turn(double angle) {
    double speed = turnPID->Get(fabs(GetAngle()), fabs(angle));
    Tank(speed, -speed);
    
    if (fabs(GetAngle()) >= fabs(angle) && !crossedTurn) crossedTurn = true;
    if (crossedMove) {
        sumTurn += fabs(GetAngle());
        nTurn++;
        
        if (fabs((sumTurn / (double)nTurn) - fabs(angle)) < 4) return true;
    }
    return false;
}
void DriveTrain::ResetTurnVars() {
    ResetGyro();
    turnPID->Reset();
    crossedTurn = false;
    sumTurn = 0.0;
    nTurn = 0;
}

void DriveTrain::MoveStraight(double power) {
    Arcade(power, -(GetAngle() / 7.5));
}
