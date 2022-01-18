#pragma once

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();
    
    MoveHangMotor(bool dir);
    MoveHookMotor(bool dir);
    MoveSwingMotor(bool dir);
    
private:
    WPI_TalonSRX *hangMotor, *swingMotor, *hookMotor;
};
