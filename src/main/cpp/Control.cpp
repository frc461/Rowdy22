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
bool Control::ShooterHood() { return hood->Get(xbox->GetRawButton(XboxButtonA)); }

bool Control::Intake() { return false; }
bool Control::Conveyor() { return false;}
bool Control::IntakeConveyor() { return xbox->GetRawButton(XboxButtonRightBumper); }
bool Control::IntakeConveyorR() { return xbox->GetRawButton(XboxButtonLeftBumper); }

bool Control::ClimberExtend() { return left->GetRawButton(thumbSwitch); }
bool Control::ClimberRetract() { return right->GetRawButton(thumbSwitch); }
bool Control::ClimberTilt() { return tilt->Get(left->GetRawButton(trigger)); }
bool Control::ClimberGrab() { return grab->Get(right->GetRawButton(trigger)); }

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