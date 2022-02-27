#include "Conveyor.h"

Conveyor::Conveyor(){
    motor = new WPI_TalonSRX(19);
    hold = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 8);

    topSensor = new frc::DigitalInput(4);
    bottomSensor = new frc::DigitalInput(5);
}

void Conveyor::RunMotor(double speed) { motor->Set(speed); }
void Conveyor::RunHold(bool dir) { hold->Set(dir); }

bool Conveyor::GetBallSensorState(bool top) { return (top) ? !topSensor->Get() : !bottomSensor->Get(); }