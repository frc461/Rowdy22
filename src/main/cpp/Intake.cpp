#include "Intake.h"

Intake::Intake() {
    motor = new WPI_TalonSRX(13);
    push = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 0);
    
    speedCap = 1.0;
}

void Intake::RunMotor(double speed) { motor->Set(speed * speedCap); }
void Intake::RunPush(bool dir) { push->Set(dir); }