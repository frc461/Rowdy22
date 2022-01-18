#include <ctre/Phoenix.h>

class Shooter {
public:
  Shooter();
  ~Shooter();
  
  void MoveMotor(bool dir, double speed);
  void MoveHood(bool dir, double speed);
  
private:
  WPI_TalonSRX *motor, *hood;
};
