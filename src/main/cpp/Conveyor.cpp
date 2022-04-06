#include "Conveyor.h"

Conveyor::Conveyor(){
    motor = new WPI_TalonSRX(19);
    hold = new frc::Solenoid(frc::PneumaticsModuleType::REVPH, 8);

    topSensor = new frc::DigitalInput(4);
    bottomSensor = new frc::DigitalInput(5);
    
    nBalls = 0;
    out = in = false;
    direction = 0;
}

void Conveyor::RunMotor(double speed) { motor->Set(speed); }
void Conveyor::RunHold(bool dir) { hold->Set(dir); }

bool Conveyor::GetBallSensorState(bool top) { return (top) ? !topSensor->Get() : !bottomSensor->Get(); }

int Conveyor::GetNumBalls() {
    if (!in && GetBallSensorState(false)) { if (motor->GetSelectedSensorVelocity() > 50) { nBalls++; } in = true; }
    else if (in && !GetBallSensorState(false)) { if (motor->GetSelectedSensorVelocity() < -50) { nBalls--; } in = false; }
    
    if (!out && GetBallSensorState(true)) { if (motor->GetSelectedSensorVelocity() < -50) { nBalls++; } out = true; }
    else if (out && !GetBallSensorState(true)) { if (motor->GetSelectedSensorVelocity() > 50) { nBalls--; } out = false; }

    return nBalls;
}