#pragma once

#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <frc/Encoder.h>

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

    bool GetTopLimit(double enc);
    bool GetBotLimit(double enc);
    
    bool GetGrabState();
    bool GetTiltState();

    double GetEncoder();
    void ResetEncoder();
    
private:
    WPI_TalonSRX *leftMotor, *rightMotor;

    frc::Solenoid *tilt, *grab, *brake;

    frc::Encoder *encoder;
};
