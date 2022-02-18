#include "Vision.h"

Vision::Vision() {
    auto instance = nt::NetworkTableInstance::GetDefault();
    limelight = instance.GetTable("limelight");
    
    backCam = new cs::UsbCamera("backCam", 0);
    backCam->SetResolution(320,240);
    output = CameraServer::GetInstance()->PutVideo("backCam",320,240);
    sink = new cs::CvSink("cvsink");
    sink->SetSource(*backCam);
    frameData = NULL;
}

Vision::Values Vision::GetValues() {
    values = { limelight->GetNumber("tx",0.0), limelight->GetNumber("ty",0.0), limelight->GetNumber("ta",0.0) };
    return values;
}

void Vision::SetLimelightState(bool state) {
    limelight->PutNumber("ledMode", (state) ? 3 : 1);
    limelight->PutNumber("camMode", (state) ? 0 : 1);
}

void Vision::SetBackCamState(bool state) {
    if (state) {
        cvSink->GetFrame(frameData);
        if (!frameData.empty()) {
            output->PutFrame(frameData);
        }
    }
}
