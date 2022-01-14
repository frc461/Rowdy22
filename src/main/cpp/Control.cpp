#include "Control.h"

Control::Control() {
    xbox = new frc::Joystick(1);
    left = new frc::Joystick(2);
    right = new frc::Joystick(3);
}

double Control::LeftX() { left->GetRawAxis(0); }
double Control::LeftY() { left->GetRawAxis(0); }
double Control::RightX() { right->GetRawAxis(0); }
double Control::RightY() { right->GetRawAxis(0); }


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