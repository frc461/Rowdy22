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
    
    int DPadAngle();

    void VibrateDriver(double power);
    void VibrateOper(double power);

    bool Shooter();
    bool ShooterLP();
    bool ShooterHoodMid();
    bool ShooterHoodUpDown();

    bool IntakeConveyor();
    bool IntakeConveyorR();
    bool IntakePush();

    bool Conveyor();
    
    bool ClimberExtend();
    bool ClimberRetract();
    bool ClimberTilt();
    bool ClimberGrab();

    bool ClimberOverrideRetract();
    bool ClimberResetEncoder();

private:
    class PressOnce {
    public:
        PressOnce();
        bool Get(bool p);
    private:
        bool pressed;
    };
    
    PressOnce *hood, *hoodMid, *tilt, *grab, *push;

    frc::Joystick *oper, *driver;
};
