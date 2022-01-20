#pragma once

#include <ctre/Phoenix.h>

#include <frc/Solenoid.h>

class Conveyor{
public:
    Conveyor();
    ~Conveyor();

    void RunMotor(double speed);
    void RunHold(bool dir);

private:
    WPI_TalonSRX *motor;
    frc::Solenoid *hold;
};