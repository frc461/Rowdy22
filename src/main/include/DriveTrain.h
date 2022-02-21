#pragma once

#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <frc/ADXRS450_Gyro.h>

#include <ctre/Phoenix.h>

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "PID.h"

#define ENC_PER_INCH 100

class DriveTrain {
public:
    DriveTrain();
    ~DriveTrain();

    void Tank(double l, double r);
    void Arcade(double v, double h);

    double GetEncoderL();
    double GetEncoderR();
    double GetAngle();
    
    void ResetEncoder();
    void ResetGyro();

    bool MoveDistance(double distance);
    void ResetMoveVars();
    
    bool Turn(double angle);
    void ResetTurnVars();
    
    void MoveStraight(double power);

    void ToggleDriveMode();

    double GetLeftVelocity();
    double GetRightVelocity();

private:
    WPI_TalonFX *l1, *l2, *r1, *r2;
    frc::MotorControllerGroup *lSide, *rSide;
    frc::DifferentialDrive *driveTrain;

    frc::ADXRS450_Gyro *gyro;

    PID *movePID, *turnPID;
    
    double max;
    
    bool crossedMove, crossedTurn;
    double sumMove, sumTurn;
    int nMove, nTurn;
};
