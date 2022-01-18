#pragma once

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();
    
    MoveHangMotor(bool dir);
    MoveHookMotor(bool dir);
    MoveSwingMotor(bool dir);
    
    double GetHookEncoder();
    double GetHangEncoder();
    double GetSwingEncoder();
    
private:
    WPI_TalonSRX *hangMotor, *swingMotor, *hookMotor;
    
    double speed;
};
