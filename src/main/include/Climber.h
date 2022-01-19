#pragma once

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();
    
    void RunHang(double speed);
    void RunHook(double speed);
    void RunSwing(double speed);
    
    double GetHookEncoder();
    double GetHangEncoder();
    double GetSwingEncoder();
    
private:
    WPI_TalonSRX *hangMotor, *swingMotor, *hookMotor;
};
