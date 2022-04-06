#include "Intake.h"

Intake::Intake() {
    motor = new WPI_VictorSPX(18);
    push = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, PUSH_SOLENOID_CHANNEL);
    
    speedCap = 1.0;
}

void Intake::RunMotor(double speed) { motor->Set(speed * speedCap); }
void Intake::RunPush(bool dir) { push->Set(dir); }

bool Intake::GetPushState() { return push->Get(); }
