#include "Vision.h"

Vision::Vision() {
    auto instance = nt::NetworkTableInstance::GetDefault();
    limelight = instance.GetTable("limelight")->GetNumber("stream", 2);
    
    // backCam = frc::CameraServer::StartAutomaticCapture("backCam", 0);
    // backCam->SetResolution(320,240);
    // output = frc::CameraServer::PutVideo("backCam",320,240);
    // sink = new cs::CvSink("cvsink");
    // sink->SetSource(*backCam);
}

Vision::Values Vision::GetValues() {
    values = { limelight->GetNumber("tx",0.0), limelight->GetNumber("ty",0.0), limelight->GetNumber("ta",0.0) };
    return values;
}

void Vision::SetLimelightState(bool cam, bool light) {
    limelight->PutNumber("ledMode", (light) ? 3 : 1);
    limelight->PutNumber("camMode", (cam) ? 0 : 1);   
}

void Vision::SetBackCamState(bool state) {
    // if (state) {
    //     cvSink->GetFrame(frameData);
    //     if (!frameData.empty()) {
    //         output.PutFrame(frameData);
    //     }
    // }
}
