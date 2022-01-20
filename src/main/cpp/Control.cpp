#include "Control.h"

Control::Control() {
    xbox = new frc::Joystick(1);
    left = new frc::Joystick(2);
    right = new frc::Joystick(3);
    
    hood = new PressOnce();
    tilt = new PressOnce();
    grab = new PressOnce();
}

double Control::LeftX() { return left->GetRawAxis(xAxisJS); }
double Control::LeftY() { return left->GetRawAxis(yAxisJS); }
double Control::RightX() { return right->GetRawAxis(xAxisJS); }
double Control::RightY() { return right->GetRawAxis(yAxisJS); }

bool Control::Shooter() { return xbox->GetRawAxis(XboxAxisRightTrigger)>0.1; }
bool Control::ShooterHood() { return hood->Get(true); } //-----------------------------------WIP

bool Control::Intake() { return xbox->GetRawButton(XboxButtonRightBumper); }
bool Control::Conveyor() { return xbox->GetRawAxis(XboxAxisLeftTrigger >0.1); }

bool Control::ClimberExtend() { return true; } //-----------------------------------WIP
bool Control::ClimberRetract() { return true; } //-----------------------------------WIP
bool Control::ClimberTilt() { return tilt->Get(true); } //-----------------------------------WIP
bool Control::ClimberGrab() { return grab->Get(true); } //-----------------------------------WIP

//===========================================================================
Control::PressOnce::PressOnce() {
    pressed = false;
}
bool Control::PressOnce::Get(bool p) {
    if (p && !pressed) pressed = true;
    else if (p && pressed) return false;
    else if (!p && pressed) pressed = false;
    return pressed;
}
//===========================================================================
