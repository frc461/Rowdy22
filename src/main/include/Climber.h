#pragma once

#include <ctre/Phoenix.h>

class Climber {
public:
    Climber();
    ~Climber();
    
private:
    WPI_TalonSRX *hangMotor, *hookMotor;
};
