#include "Climber.h"

Climber::Climber() {
    hangMotor = new WPI_TalonSRX(0);
    hookMotor = new WPI_TalonSRX(0);
}
