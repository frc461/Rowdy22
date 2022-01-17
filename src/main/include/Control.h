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

private:
    class PressOnce {
    public:
        PressOnce();
        bool Get(bool p);
    private:
        bool pressed;
    };

    frc::Joystick *xbox, *left, *right;
};