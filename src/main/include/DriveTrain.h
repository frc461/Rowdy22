#pragma once

#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

#include <frc/ADXRS450_Gyro.h>

#include <ctre/Phoenix.h>

#include "PID.h"

class DriveTrain {
public:
    DriveTrain();
    ~DriveTrain();

    void Tank(double l, double r, double min, double max);
    void Arcade(double v, double h, double min, double max);

    double GetEncoderL();
    double GetEncoderR();
    double GetAngle();
    
    void ResetEncoder();
    void ResetGyro();

    bool MoveDistance(int distance);
    bool Turn(double angle);
    void MoveStraight(double power);

private:
    WPI_TalonFX *l1, *l2, *r1, *r2;
    frc::MotorControllerGroup *lSide, *rSide;
    frc::DifferentialDrive *driveTrain;

    frc::ADXRS450_Gyro *gyro;

    PID *movePID, *turnPID;
};
