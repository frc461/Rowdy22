#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

class Vision {
public:
    Vision();
    ~Vision();

    struct Values {
        double x,y,a;
    };
    Vision::Values GetValues();

    void SetCamState(bool state);

private:
    std::shared_ptr<nt::NetworkTable> cam;
    Values values;
};