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

    void Tank(double l, double r, double speedCap);
    void Arcade(double v, double h, double speedCap);

    double GetEncoderL();
    double GetEncoderR();
    double GetAngle();

    bool MoveDistance(bool dir, int distance);
    void MoveStraight(bool dir, double power);
    void Turn(bool dir, double angle);

private:
    WPI_TalonFX *l1, *l2, *r1, *r2;
    frc::MotorControllerGroup *lSide, *rSide;
    frc::DifferentialDrive *driveTrain;

    frc::ADXRS450_Gyro *gyro;

    PID *movePID;
};
