#pragma once

#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <frc/ADXRS450_Gyro.h>

#include <frc/Encoder.h>

#include <ctre/Phoenix.h>

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "PID.h"

#define ENC_PER_INCH 74.46

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
    void CalibrateGyro();

    bool MoveDistance(double distance, double cap, bool fast);
    void ResetMoveVars();
    
    bool Turn(double angle, bool fast);
    void ResetTurnVars();
    
    void MoveStraight(double power);

    void ToggleDriveMode();

    double GetLeftVelocity();
    double GetRightVelocity();

private:
    WPI_TalonFX *l1, *l2, *r1, *r2;
    frc::MotorControllerGroup *lSide, *rSide;
    frc::DifferentialDrive *driveTrain;

    frc::Encoder *leftEncoder, *rightEncoder;

    frc::ADXRS450_Gyro *gyro;

    PID *movePID, *turnPID;
    
    double max;
};
