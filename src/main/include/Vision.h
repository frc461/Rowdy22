#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include "cameraserver/CameraServer.h"
#include <opencv2/core/core.hpp>

#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/DigitalOutput.h>

#include <iostream>

class Vision {
public:
    Vision();
    ~Vision();

    struct Values {
        double x,y,a;
    };
    Vision::Values GetValues();

    void SetLimelightState(bool cam, bool light);
    void SetBackCamState(bool state);

    void SetIndicator(bool state);

private:
    std::shared_ptr<nt::NetworkTable> limelight;
    Values values;
    
    frc::DigitalOutput *lightIndicator;
    // cs::UsbCamera *backCam;
    // cs::CvSink *sink;
    // cs::CvSource output;
    // cv::Mat frameData;
};
