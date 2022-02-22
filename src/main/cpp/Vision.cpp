#include "Vision.h"

Vision::Vision() {
    auto instance = nt::NetworkTableInstance::GetDefault();
    limelight = instance.GetTable("limelight");
}

Vision::Values Vision::GetValues() {
    values = { limelight->GetNumber("tx",0.0), limelight->GetNumber("ty",0.0), limelight->GetNumber("ta",0.0) };
    return values;
}

void Vision::SetLimelightState(bool cam, bool light) {
    limelight->PutNumber("ledMode", (light) ? 3 : 1);
    limelight->PutNumber("camMode", (cam) ? 0 : 1);

    
}