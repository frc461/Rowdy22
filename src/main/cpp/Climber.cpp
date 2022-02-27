#include "Climber.h"

Climber::Climber() {
    leftMotor = new WPI_TalonSRX(15);
    rightMotor = new WPI_TalonSRX(16);

    tilt = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 12);
    grab = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 9);
    brake = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 11);

    topLimit = new frc::DigitalInput(6);
    botLimit = new frc::DigitalInput(7);

    encoder = new frc::Encoder(8,9);
}

void Climber::RunLeft(double speed) { leftMotor->Set(speed); }
void Climber::RunRight(double speed) { rightMotor->Set(speed); }

void Climber::RunGrab(bool dir) { grab->Set(dir); }
void Climber::RunTilt(bool dir) { tilt->Set(dir); }
void Climber::RunBrake(bool dir) { brake->Set(dir); }

bool Climber::GetTopLimit() { return topLimit->Get(); }
bool Climber::GetBotLimit() { return botLimit->Get(); }

bool Climber::GetGrabState() { return grab->Get(); }
bool Climber::GetTiltState() { return tilt->Get(); }

double Climber::GetEncoder() { return encoder->GetRaw(); }