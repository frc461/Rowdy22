#pragma once

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();
    
    void MoveHangMotor(bool dir);
    void MoveHookMotor(bool dir);
    void MoveSwingMotor(bool dir);
    
    double GetHookEncoder();
    double GetHangEncoder();
    double GetSwingEncoder();
    
private:
    WPI_TalonSRX *hangMotor, *swingMotor, *hookMotor;
    
    double speed;
};
