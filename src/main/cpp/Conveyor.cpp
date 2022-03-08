#include "Conveyor.h"

Conveyor::Conveyor(){
    motor = new WPI_TalonSRX(19);
    hold = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 8);

    topSensor = new frc::DigitalInput(4);
    bottomSensor = new frc::DigitalInput(5);
    
    nBalls = 0;
    out = in = false;
}

void Conveyor::RunMotor(double speed) { motor->Set(speed); }
void Conveyor::RunHold(bool dir) { hold->Set(dir); }

bool Conveyor::GetBallSensorState(bool top) { return (top) ? !topSensor->Get() : !bottomSensor->Get(); }

double Conveyor::GetNumBalls() {
    if (!in && GetBallSensorState(false)) { nBalls++; in = true; }
    else if (in && !GetBallSensorState(false)) { in = false; }
    
    if (!out && GetBallSensorState(true)) { out = true; }
    else if (out && !GetBallSensorState(true)) { nBalls--; out = false; }
}
