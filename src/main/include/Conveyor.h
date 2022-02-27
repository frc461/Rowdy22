#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>

#include <frc/DigitalInput.h>

class Conveyor{
public:
    Conveyor();
    ~Conveyor();

    void RunMotor(double speed);
    void RunHold(bool dir);

    bool GetBallSensorState(bool top);

private:
    WPI_TalonSRX *motor;
    frc::Solenoid *hold;

    frc::DigitalInput *topSensor, *bottomSensor;
};