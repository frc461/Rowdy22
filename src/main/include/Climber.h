#pragma once

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();
    
    void RunHangMotor(double speed);
    void RunHookMotor(double speed);
    void RunSwingMotor(double speed);
    
    double GetHookEncoder();
    double GetHangEncoder();
    double GetSwingEncoder();
    
private:
    WPI_TalonSRX *hangMotor, *swingMotor, *hookMotor;
};
