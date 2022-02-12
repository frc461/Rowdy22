#pragma once

#include <frc/Joystick.h>

#include "Maps/XboxMap.h"
#include "Maps/ThrustMastersMap.h"

class Control {
public:
    Control();
    ~Control();

    double LeftX();
    double LeftY();
    double RightX();
    double RightY();

    bool Shooter();
    bool ShooterHood();
    
    bool Intake();
    bool Conveyor();

    bool IntakeConveyor();
    bool IntakeConveyorR();
    
    bool ClimberExtend();
    bool ClimberRetract();
    bool ClimberTilt();
    bool ClimberGrab();



private:
    class PressOnce {
    public:
        PressOnce();
        bool Get(bool p);
    private:
        bool pressed;
    };
    
    PressOnce *hood;
    PressOnce *tilt, *grab;

    frc::Joystick *xbox, *left, *right;
};
