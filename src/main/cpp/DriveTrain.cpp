#include "DriveTrain.h"

DriveTrain::DriveTrain() {
    l1 = new WPI_TalonFX(11);
    l2 = new WPI_TalonFX(12);
    r1 = new WPI_TalonFX(13);
    r2 = new WPI_TalonFX(14);

    lSide = new frc::MotorControllerGroup(*l1, *l2);
    rSide = new frc::MotorControllerGroup(*r1, *r2);

    driveTrain = new frc::DifferentialDrive(*lSide, *rSide);
    
    l1->SetNeutralMode(NeutralMode::Coast);
    l2->SetNeutralMode(NeutralMode::Coast);
    r1->SetNeutralMode(NeutralMode::Coast);
    r2->SetNeutralMode(NeutralMode::Coast);


    // gyro = new frc::ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0);

    movePID = new PID(0.5, 0.0, 0.0, "move");
    turnPID = new PID(0.5, 0.0, 0.0, "turn");
    

    max = 1.0;
    
    crossedMove = crossedTurn = false;
    sumMove = sumTurn = 0.0;
    nMove = nTurn = 0;
}

void DriveTrain::Tank(double l, double r) { driveTrain->TankDrive(l*max, r*max); }
void DriveTrain::Arcade(double v, double h) { driveTrain->ArcadeDrive(h*max, v*max); }

double DriveTrain::GetEncoderL() { return l1->GetSelectedSensorPosition(); }
double DriveTrain::GetEncoderR() { return r1->GetSelectedSensorPosition(); }
double DriveTrain::GetAngle() { return gyro->GetAngle(); }
double DriveTrain::GetLeftVelocity() { return l1->GetSelectedSensorVelocity(); }
double DriveTrain::GetRightVelocity() { return r1->GetSelectedSensorVelocity(); }


void DriveTrain::ResetEncoder() { l1->SetSelectedSensorPosition(0.0); r1->SetSelectedSensorPosition(0.0); }
void DriveTrain::ResetGyro() { gyro->Reset(); }

bool DriveTrain::MoveDistance(double distance) {
    double l = movePID->Get(GetEncoderL(), distance * ENC_PER_INCH);
    double r = movePID->Get(GetEncoderR(), -distance * ENC_PER_INCH);
    Tank(l, r);
    
    if (fabs(GetEncoderL()) >= fabs(distance * ENC_PER_INCH) && !crossedMove) crossedMove = true;
    if (crossedMove) {
        sumMove += fabs(GetEncoderL());
        nMove++;
        
        if ((sumMove / (double)nMove) - fabs(distance * ENC_PER_INCH) < 1.0) return true; 
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
    double speed = turnPID->Get(GetAngle(), angle);
    Tank(speed, -speed);
    
    if (fabs(GetAngle()) >= fabs(angle) && !crossedTurn) crossedTurn = true;
    if (crossedMove) {
        sumTurn += fabs(GetAngle());
        nTurn++;
        
        if ((sumTurn / (double)nTurn) - fabs(angle) < 0.25) return true;
    }
    return false;
}
void DriveTrain::ResetTurnVars() {
    ResetGyro();
    crossedTurn = false;
    sumTurn = 0.0;
    nTurn = 0;
}

void DriveTrain::MoveStraight(double power) {
    Arcade(power, -(GetAngle() / 7.5));
}
