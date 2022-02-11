#include "Climber.h"

Climber::Climber() {
    leftMotor = new WPI_TalonSRX(15);
    rightMotor = new WPI_TalonSRX(16);

    // tilt = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 0);
    // grab = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 0);
    // brake = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 0);
}

void Climber::RunLeft(double speed) { leftMotor->Set(speed); }
void Climber::RunRight(double speed) { rightMotor->Set(speed); }

void Climber::RunGrab(bool dir) { grab->Set(dir); }
void Climber::RunTilt(bool dir) { tilt->Set(dir); }
void Climber::RunBrake(bool dir) { brake->Set(dir); }
