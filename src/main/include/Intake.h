#pragma once

#include <ctre/Phoenix.h>

class Intake {
public:
    Intake();
    ~Intake();
    
    void RunMotor(double speed);

private:
    WPI_TalonSRX *motor;
    
    double speedCap;
};
