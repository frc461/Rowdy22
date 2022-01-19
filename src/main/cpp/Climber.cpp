#include "Climber.h"

Climber::Climber() {
    hangMotor = new WPI_TalonSRX(0);
    hookMotor = new WPI_TalonSRX(0);
    swingMotor = new WPI_TalonSRX(0);
}

void RunHook(double speed) { hookMotor->Set(speed); }
void RunHang(double speed) { hangMotor->Set(speed); }
void RunSwing(double speed) { swingMotor->Set(speed); }

double GetHookEncoder() { return hookMotor->GetSelectedSensorPosition(); }
double GetHangEncoder() { return hangMotor->GetSelectedSensorPosition(); }
double GetSwingEncoder() { return swingMotor->GetSelectedSensorPosition(); }
