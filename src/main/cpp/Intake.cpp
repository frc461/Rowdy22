#include "Intake.h"

Intake::Intake() {
    motor = new WPI_TalonSRX(0);
    
    speedCap = 1.0;
}

void Intake::RunMotor(double speed) { motor->Set(speed * speedCap); }
