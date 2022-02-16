#include "Conveyor.h"

Conveyor::Conveyor(){
    motor = new WPI_TalonSRX(19);
    hold = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 8);
}

void Conveyor::RunMotor(double speed) { motor->Set(speed); }
void Conveyor::RunHold(bool dir) { hold->Set(dir); }
