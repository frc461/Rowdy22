#pragma once

#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>

class Intake {
public:
    Intake();
    ~Intake();
    
    void RunMotor(double speed);
    void RunPush(bool dir);

private:
    WPI_VictorSPX *motor;
    frc::Solenoid *push;
    
    double speedCap;
};
