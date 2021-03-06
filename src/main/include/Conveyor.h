#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>

#include <frc/DigitalInput.h>

#include <iostream>

class Conveyor{
public:
    Conveyor();
    ~Conveyor();

    void RunMotor(double speed);
    void RunHold(bool dir);

    bool GetBallSensorState(bool top);
    
    int GetNumBalls();

private:
    WPI_TalonSRX *motor;
    frc::Solenoid *hold;

    frc::DigitalInput *topSensor, *bottomSensor;
    
    int nBalls;
    bool out, in;
    int direction;
};
