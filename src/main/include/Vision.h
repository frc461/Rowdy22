#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include "cameraserver/CameraServer.h"
#include <opencv2/core/core.hpp>

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

private:
    std::shared_ptr<nt::NetworkTable> limelight;
    Values values;
};
