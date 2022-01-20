#pragma once

#include <frc/Solenoid.h>

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();

    void RunLeft(double speed);
    void RunRight(double speed);
    void RunGrab(bool dir);
    void RunTilt(bool dir);
    void RunBrake(bool dir);
    
private:
    WPI_TalonSRX *leftMotor, *rightMotor;

    frc::Solenoid *tilt, *grab, *brake;
};