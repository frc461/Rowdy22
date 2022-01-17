#include "Vision.h"

Vision::Vision() {
    auto instance = nt::NetworkTableInstance::GetDefault();
    cam = instance.GetTable("limelight");
}

Vision::Values Vision::GetValues() {
    values = { cam->GetNumber("tx",0.0), cam->GetNumber("ty",0.0), cam->GetNumber("ta",0.0) };
    return values;
}

void Vision::SetCamState(bool state) {
    cam->PutNumber("ledMode", (state) ? 3 : 1);
    cam->PutNumber("camMode", (state) ? 0 : 1);
}