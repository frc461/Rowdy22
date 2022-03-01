#include "Control.h"

Control::Control() {
    oper = new frc::Joystick(1);
    driver = new frc::Joystick(2);
    
    hood = new PressOnce();
    tilt = new PressOnce();
    grab = new PressOnce();
    push = new PressOnce();
}

double Control::LeftX() { return driver->GetRawAxis(XboxAxisLeftStickX); }
double Control::LeftY() { return driver->GetRawAxis(XboxAxisLeftStickY); }
double Control::RightX() { return driver->GetRawAxis(XboxAxisRightStickX); }
double Control::RightY() { return driver->GetRawAxis(XboxAxisRightStickY); }
void Control::VibrateDriver(double power) { driver->SetRumble(frc::GenericHID::RumbleType::kLeftRumble,power); driver->SetRumble(frc::GenericHID::RumbleType::kRightRumble,power); }
void Control::VibrateOper(double power) { oper->SetRumble(frc::GenericHID::RumbleType::kLeftRumble,power); driver->SetRumble(frc::GenericHID::RumbleType::kRightRumble,power); }

bool Control::Shooter() { return oper->GetRawAxis(XboxAxisRightTrigger)>0.1; }
bool Control::ShooterHood() { return hood->Get(oper->GetRawButton(XboxButtonA)); }

bool Control::IntakeConveyor() { return oper->GetRawButton(XboxButtonRightBumper); }
bool Control::IntakeConveyorR() { return oper->GetRawButton(XboxButtonLeftBumper); }
bool Control::Conveyor() { return oper->GetRawAxis(XboxAxisLeftTrigger)>0.1; }
bool Control::IntakePush() { return push->Get(oper->GetRawButton(XboxButtonB)); }

bool Control::ClimberExtend() { return driver->GetRawButton(XboxButtonRightBumper); }
bool Control::ClimberRetract() { return driver->GetRawButton(XboxButtonLeftBumper); }
bool Control::ClimberTilt() { return tilt->Get(driver->GetRawAxis(XboxAxisLeftTrigger)>0.1); }
bool Control::ClimberGrab() { return grab->Get(driver->GetRawAxis(XboxAxisRightTrigger)>0.1); }

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