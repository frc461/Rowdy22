#include "Climber.h"

Climber::Climber() {
    hangMotor = new WPI_TalonSRX(0);
    hookMotor = new WPI_TalonSRX(0);
    swingMotor = new WPI_TalonSRX(0);
    
    speed = 0.75;
}

void Climber::MoveHangMotor(bool dir) { hangMotor->Set((dir) ? speed : -speed; }
void Climber::MoveHookMotor(bool dir) { hookMotor->Set((dir) ? speed : -speed; }
void Climber::MoveSwingMotor(bool dir) { swingMotor->Set((dir) ? speed : -speed; }

double GetHookEncoder() { return hookMotor->GetSelectedSensorPosition(); }
double GetHangEncoder() { return hangMotor->GetSelectedSensorPosition(); }
double GetSwingEncoder() { return swingMotor->GetSelectedSensorPosition(); }
