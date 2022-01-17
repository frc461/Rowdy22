#include "Control.h"

Control::Control() {
    xbox = new frc::Joystick(1);
    left = new frc::Joystick(2);
    right = new frc::Joystick(3);
}

double Control::LeftX() { return left->GetRawAxis(xAxisJS); }
double Control::LeftY() { return left->GetRawAxis(yAxisJS); }
double Control::RightX() { return right->GetRawAxis(xAxisJS); }
double Control::RightY() { return right->GetRawAxis(yAxisJS); }

//===========================================================================
Control::PressOnce::PressOnce() {
    pressed = false;
}
bool Control::PressOnce::Get(bool p) {
    if (p && !pressed) {
        pressed = true;
    }
    else if (p && pressed) {
        return false;
    }
    else if (!p && pressed) {
        pressed = false;
    }
    return pressed;
}
//===========================================================================